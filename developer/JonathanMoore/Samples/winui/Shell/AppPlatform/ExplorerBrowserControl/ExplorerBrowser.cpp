#define STRICT_TYPED_ITEMIDS
#include <windows.h>
#include <windowsx.h>
#include <shlobj.h>
#include <shellapi.h>
#include <shlwapi.h>
#include <propkey.h>
#include "resource.h"

#pragma comment(lib, "shell32.lib")
#pragma comment(lib, "shlwapi.lib")
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")

HINSTANCE g_hinst = 0;

#define KFD_SELCHANGE     WM_USER

class CFillResultsOnBackgroundThread;

class CExplorerBrowserHostDialog : public IServiceProvider, public ICommDlgBrowser
{
public:
    CExplorerBrowserHostDialog() : _cRef(1), _hdlg(NULL), _peb(NULL), _fEnumerated(FALSE), _prf(NULL)
    {
    }

    HRESULT DoModal(HWND hwnd)
    {
        DialogBoxParam(g_hinst, MAKEINTRESOURCE(IDD_DIALOG1), hwnd, s_DlgProc, (LPARAM)this);
        return S_OK;
    }
    
    // IUnknown
    STDMETHODIMP QueryInterface(REFIID riid, __deref_out void **ppv)
    {
        static const QITAB qit[] = 
        {
            QITABENT(CExplorerBrowserHostDialog, IServiceProvider),
            QITABENT(CExplorerBrowserHostDialog, ICommDlgBrowser),
            { 0 },
        };
        return QISearch(this, qit, riid, ppv);
    }

    STDMETHODIMP_(ULONG) AddRef()
    {
        return InterlockedIncrement(&_cRef);
    }

    STDMETHODIMP_(ULONG) Release()
    {
        LONG cRef = InterlockedDecrement(&_cRef);
        if (!cRef)
            delete this;
        return cRef;
    }
    
    // IServiceProvider
    STDMETHODIMP QueryService(REFGUID guidService, REFIID riid, void **ppv)
    {
        HRESULT hr = E_NOINTERFACE;
        *ppv = NULL;
        if (guidService == SID_SExplorerBrowserFrame)
        {
            // responding to this SID allows us to hook up our ICommDlgBrowser
            // implementation so we get selection change events from the view
            hr = QueryInterface(riid, ppv);
        }
        return hr;
    }

    // ICommDlgBrowser
    STDMETHODIMP OnDefaultCommand(IShellView *psv) 
    { 
        _OnExplore();
        return S_OK; 
    }

    STDMETHODIMP OnStateChange(IShellView *psv, ULONG uChange)  
    {
        if (uChange == CDBOSC_SELCHANGE)
        {
            PostMessage(_hdlg, KFD_SELCHANGE, 0, 0);
        }
        return S_OK;
    }

    STDMETHODIMP IncludeObject(IShellView *psv, __in PCUITEMID_CHILD pidl)  
    { 
        return S_OK; 
    }

    void FillResultsOnBackgroundThread(IResultsFolder *prf);

private:
    ~CExplorerBrowserHostDialog()
    {
    }
  
    static BOOL CALLBACK s_DlgProc(HWND hdlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
        #pragma warning(push)
        #pragma warning(disable:4312) // GetWindowLongPtr is not w4 clean
        CExplorerBrowserHostDialog *pebhd = reinterpret_cast<CExplorerBrowserHostDialog *>(GetWindowLongPtr(hdlg, DWLP_USER));
        #pragma warning(pop)

        if (uMsg == WM_INITDIALOG)
        {
            pebhd = reinterpret_cast<CExplorerBrowserHostDialog *>(lParam);
            pebhd->_hdlg = hdlg;
            #pragma warning(push)
            #pragma warning(disable:4244) // SetWindowLongPtr is not w4 clean
            SetWindowLongPtr(hdlg, DWLP_USER, reinterpret_cast<LONG_PTR>(pebhd));
            #pragma warning(pop)
        }
        
        return pebhd ? pebhd->_DlgProc(uMsg, wParam, lParam) : FALSE;
    }

    BOOL _DlgProc(UINT uMsg, WPARAM wParam, LPARAM lParam);
    HRESULT _FillViewWithKnownFolders(IResultsFolder *prf);
    void _OnInitDlg();
    void _OnDestroyDlg();
    void _StartFolderEnum();
    void _OnSelChange();
    void _OnExplore();
    void _OnFind();

    class CFillResultsOnBackgroundThread
    {
    public:
        CFillResultsOnBackgroundThread(CExplorerBrowserHostDialog *pebhd) : _cRef(1), _pebhd(pebhd), _pStream(NULL)
        {
            _pebhd->AddRef();
        }

        HRESULT StartThread(IResultsFolder *prf)
        {
            HRESULT hr = CoMarshalInterThreadInterfaceInStream(IID_IResultsFolder, prf, &_pStream);
            if (SUCCEEDED(hr))
            {
                AddRef();
                hr = SHCreateThread(s_ThreadProc, this, CTF_COINIT, NULL) ? S_OK : E_FAIL;
                if (FAILED(hr))
                {
                    Release();
                }
            }
            return hr;
        }

        ULONG AddRef()
        {
            return InterlockedIncrement(&_cRef);
        }

        ULONG Release()
        {
            LONG cRef = InterlockedDecrement(&_cRef);
            if (!cRef)
                delete this;
            return cRef;
        }

    private:
        static DWORD WINAPI s_ThreadProc(__in void *pv)
        {
            CFillResultsOnBackgroundThread *pfrobt = (CFillResultsOnBackgroundThread*)pv;

            IResultsFolder* prf;
            HRESULT hr = CoGetInterfaceAndReleaseStream(pfrobt->_pStream, IID_PPV_ARGS(&prf));
            pfrobt->_pStream = NULL;
            if (SUCCEEDED(hr))
            {
                pfrobt->_pebhd->FillResultsOnBackgroundThread(prf);
            }
            pfrobt->Release();
            return 0;
        }

        ~CFillResultsOnBackgroundThread()
        {
            _pebhd->Release();
            if (_pStream)
            {
                _pStream->Release();
            }
        }

        long _cRef;
        CExplorerBrowserHostDialog *_pebhd;
        IStream *_pStream;
    };

    long _cRef;
    HWND _hdlg;

    IExplorerBrowser* _peb;
    IResultsFolder* _prf;
    BOOL _fEnumerated;
};

HRESULT CExplorerBrowserHostDialog::_FillViewWithKnownFolders(IResultsFolder* prf)
{
    IKnownFolderManager* pManager;
    HRESULT hr = CoCreateInstance(CLSID_KnownFolderManager, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pManager));
    if (SUCCEEDED(hr))
    {
        UINT cCount;
        KNOWNFOLDERID *pkfid;

        hr = pManager->GetFolderIds(&pkfid, &cCount);
        if (SUCCEEDED(hr))
        {
            for (UINT i = 0; i < cCount; i++)
            {
                IKnownFolder *pKnownFolder;
                hr = pManager->GetFolder(pkfid[i], &pKnownFolder);
                if (SUCCEEDED(hr))
                {
                    KNOWNFOLDERID fid;
                    pKnownFolder->GetId(&fid);

                    KF_CATEGORY cat;
                    pKnownFolder->GetCategory(&cat);

                    PWSTR pszPath;
                    if (SUCCEEDED(pKnownFolder->GetPath(0, &pszPath)))
                    {
                        CoTaskMemFree(pszPath);
                    }

                    IShellItem *psi;
                    hr = pKnownFolder->GetShellItem(0, IID_PPV_ARGS(&psi));
                    if (SUCCEEDED(hr))
                    {
                        hr = prf->AddItem(psi);
                        psi->Release();
                    }
                    pKnownFolder->Release();
                }
            }
            CoTaskMemFree(pkfid);
        }
        pManager->Release();
    }
    return hr;
}

void CExplorerBrowserHostDialog::_OnInitDlg()
{
    ShowWindow(GetDlgItem(_hdlg, IDC_FOLDERNAME), SW_HIDE);
    ShowWindow(GetDlgItem(_hdlg, IDC_FOLDERPATH), SW_HIDE);
    ShowWindow(GetDlgItem(_hdlg, IDC_LBLFOLDER), SW_HIDE);
    ShowWindow(GetDlgItem(_hdlg, IDC_LBLPATH), SW_HIDE);
    
    HWND hwndStatic = GetDlgItem(_hdlg, IDC_BROWSER);
    if (hwndStatic)
    {
        RECT rc;
        GetWindowRect(hwndStatic, &rc);
        MapWindowRect(HWND_DESKTOP, _hdlg, &rc);

        HRESULT hr = CoCreateInstance(CLSID_ExplorerBrowser, NULL, CLSCTX_INPROC, IID_PPV_ARGS(&_peb));
        if (SUCCEEDED(hr))
        {
            IUnknown_SetSite(_peb, static_cast<IServiceProvider *>(this));

            FOLDERSETTINGS fs = {0};
            fs.ViewMode = FVM_DETAILS;
            fs.fFlags = FWF_AUTOARRANGE | FWF_NOWEBVIEW; //  | FWF_TRICHECKSELECT;
            hr = _peb->Initialize(_hdlg, &rc, &fs);
            if (SUCCEEDED(hr))
            {
                _peb->SetOptions(EBO_NAVIGATEONCE); // don't allow navigations

                // init the exporer browser so that we can use the results folder
                // as the data source. that enables us to program the contents of
                // the view via IResultsFolder

                hr = _peb->FillFromObject(NULL, EBF_NODROPTARGET);
                if (SUCCEEDED(hr))
                {
                    IFolderView2* pfv2;
                    hr = _peb->GetCurrentView(IID_PPV_ARGS(&pfv2));
                    if (SUCCEEDED(hr))
                    {
                        IColumnManager *pcm;
                        hr = pfv2->QueryInterface(IID_PPV_ARGS(&pcm));
                        if (SUCCEEDED(hr))
                        {
                            PROPERTYKEY rgkeys[] = {PKEY_ItemNameDisplay, PKEY_ItemFolderPathDisplay};
                            hr = pcm->SetColumns(rgkeys, ARRAYSIZE(rgkeys));

                            CM_COLUMNINFO ci = {sizeof(ci), CM_MASK_WIDTH | CM_MASK_DEFAULTWIDTH | CM_MASK_IDEALWIDTH};
                            hr = pcm->GetColumnInfo(PKEY_ItemFolderPathDisplay, &ci);
                            if (SUCCEEDED(hr))
                            {
                                ci.uWidth += 100;
                                ci.uDefaultWidth += 100;
                                ci.uIdealWidth += 100;
                                hr = pcm->SetColumnInfo(PKEY_ItemFolderPathDisplay, &ci);
                            }

                            pcm->Release();
                        }

                        // pfv2->SetCurrentViewMode(FVM_DETAILS);

                        hr = pfv2->GetFolder(IID_PPV_ARGS(&_prf));
                        if (SUCCEEDED(hr))
                        {
                            _StartFolderEnum();
                        }
                        pfv2->Release();
                    }
                }
            }
        }
    }
}

// pass -1 for the current selected item
// returns an IShellItem type object

HRESULT GetItemFromView(IFolderView2 *pfv, int iItem, REFIID riid, void **ppv)
{
    *ppv = NULL;

    HRESULT hr = S_OK;

    if (iItem == -1)
    {
        hr = pfv->GetSelectedItem(-1, &iItem); // Returns S_FALSE if none selected
    }

    if (S_OK == hr)
    {
        hr = pfv->GetItem(iItem, riid, ppv);
    }
    else
    {
        hr = E_FAIL;
    }
    return hr;
}

void CExplorerBrowserHostDialog::_OnSelChange()
{
    if (_fEnumerated)
    {
        IFolderView2* pfv2;
        HRESULT hr = _peb->GetCurrentView(IID_PPV_ARGS(&pfv2));
        if (SUCCEEDED(hr))
        {
            IShellItem2 *psi;
            hr = GetItemFromView(pfv2, -1, IID_PPV_ARGS(&psi));
            if (SUCCEEDED(hr))
            {
                PWSTR pszName;
                hr = psi->GetDisplayName(SIGDN_NORMALDISPLAY, &pszName);
                if (SUCCEEDED(hr))
                {
                    SetDlgItemText(_hdlg, IDC_FOLDERNAME, pszName);
                    CoTaskMemFree(pszName);
                }

                hr = psi->GetDisplayName(SIGDN_DESKTOPABSOLUTEPARSING, &pszName);
                if (SUCCEEDED(hr))
                {
                    SetDlgItemText(_hdlg, IDC_FOLDERPATH, pszName);
                    CoTaskMemFree(pszName);
                }
                
                psi->Release();
            }
            else if (hr == S_FALSE)
            {
                SetDlgItemText(_hdlg, IDC_FOLDERNAME, TEXT(""));
                SetDlgItemText(_hdlg, IDC_FOLDERPATH, TEXT(""));
            }

            EnableWindow(GetDlgItem(_hdlg, IDC_EXPLORE), hr == S_OK);

            pfv2->Release();
        }
    } 
}

void CExplorerBrowserHostDialog::_OnDestroyDlg()
{
    if (_peb)
    {
        IUnknown_SetSite(_peb, NULL);
        _peb->Destroy();
        _peb->Release();
        _peb = NULL;
    }

    if (_prf)
    {
        _prf->Release();
        _prf = NULL;
    }
}

void CExplorerBrowserHostDialog::_OnExplore()
{
    IFolderView2* pfv2;
    HRESULT hr = _peb->GetCurrentView(IID_PPV_ARGS(&pfv2));
    if (SUCCEEDED(hr))
    {
        IShellItem *psi;
        hr = GetItemFromView(pfv2, -1, IID_PPV_ARGS(&psi));
        if (SUCCEEDED(hr))
        {
            PIDLIST_ABSOLUTE pidl;
            hr = SHGetIDListFromObject(psi, &pidl);
            if (SUCCEEDED(hr))
            {
                SHELLEXECUTEINFO ei = { sizeof(ei) };
                ei.fMask        = SEE_MASK_INVOKEIDLIST;
                ei.hwnd         = _hdlg;
                ei.nShow        = SW_NORMAL;
                ei.lpIDList     = pidl;

                ShellExecuteEx(&ei);

                CoTaskMemFree(pidl);
            }
        }
        pfv2->Release();
    }
}

void CExplorerBrowserHostDialog::_OnFind()
{
    _fEnumerated = FALSE;

    // Update UI
    EnableWindow(GetDlgItem(_hdlg, IDC_EXPLORE), FALSE);
    EnableWindow(GetDlgItem(_hdlg, IDC_FIND), FALSE);

    if (SUCCEEDED(_peb->RemoveAll()))
    {
        _StartFolderEnum();
    }
}

void CExplorerBrowserHostDialog::_StartFolderEnum()
{
    CFillResultsOnBackgroundThread *pfrobt = new CFillResultsOnBackgroundThread(this);
    if (pfrobt)
    {
        pfrobt->StartThread(_prf);
        pfrobt->Release();
    }
}

void CExplorerBrowserHostDialog::FillResultsOnBackgroundThread(IResultsFolder *prf)
{
    // Adjust dialog to show proper enumerating info and buttons
    SetDlgItemText(_hdlg, IDC_ENUMNAME, TEXT("Starting Enumeration..."));
    SetDlgItemText(_hdlg, IDC_ENUMPATH, TEXT(""));
    ShowWindow(GetDlgItem(_hdlg, IDC_STATUS), SW_SHOW);
    ShowWindow(GetDlgItem(_hdlg, IDC_ENUMNAME), SW_SHOW);
    ShowWindow(GetDlgItem(_hdlg, IDC_ENUMPATH), SW_SHOW);

    ShowWindow(GetDlgItem(_hdlg, IDC_FOLDERNAME), SW_HIDE);
    ShowWindow(GetDlgItem(_hdlg, IDC_FOLDERPATH), SW_HIDE);
    ShowWindow(GetDlgItem(_hdlg, IDC_LBLFOLDER), SW_HIDE);
    ShowWindow(GetDlgItem(_hdlg, IDC_LBLPATH), SW_HIDE);

    _FillViewWithKnownFolders(prf);

    _fEnumerated = TRUE;

    // Adjust dialog to show proper view info and buttons
    ShowWindow(GetDlgItem(_hdlg, IDC_STATUS), SW_HIDE);
    ShowWindow(GetDlgItem(_hdlg, IDC_ENUMNAME), SW_HIDE);
    ShowWindow(GetDlgItem(_hdlg, IDC_ENUMPATH), SW_HIDE);

    ShowWindow(GetDlgItem(_hdlg, IDC_FOLDERNAME), SW_SHOW);
    ShowWindow(GetDlgItem(_hdlg, IDC_FOLDERPATH), SW_SHOW);
    ShowWindow(GetDlgItem(_hdlg, IDC_LBLFOLDER), SW_SHOW);
    ShowWindow(GetDlgItem(_hdlg, IDC_LBLPATH), SW_SHOW);

    EnableWindow(GetDlgItem(_hdlg, IDC_FIND), TRUE);
}

BOOL CExplorerBrowserHostDialog::_DlgProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_INITDIALOG:
        _OnInitDlg();
        break;
    
    case WM_COMMAND:
        switch (GET_WM_COMMAND_ID(wParam, lParam))
        {
        case IDOK:
        case IDCANCEL:
        case IDC_CANCEL:        
            return EndDialog(_hdlg, TRUE);

        case IDC_FIND:
            _OnFind();
            break;

        case IDC_EXPLORE:
            _OnExplore();
            break;
        }
        break;
        
    case KFD_SELCHANGE:
        _OnSelChange();
        break;
    
    case WM_DESTROY:
        _OnDestroyDlg();
        break;
        
    default:
        return FALSE;
    }
    return TRUE;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, __in LPSTR, int nCmdShow)
{
    g_hinst = hInstance;

    HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
    if (SUCCEEDED(hr))
    {
        OleInitialize(0);   // for drag and drop

        CExplorerBrowserHostDialog *pdlg = new CExplorerBrowserHostDialog();
        if (pdlg)
        {
            pdlg->DoModal(NULL);
            pdlg->Release();
        }

        OleUninitialize();
        CoUninitialize();
    }

    return 0;
}
