//-----------------------------------------------------------------------------
// File: Dialog.cpp
// Desc: Dialog class
//
//  Copyright (C) Microsoft Corporation. All rights reserved.
//-----------------------------------------------------------------------------

#include "dialog.h"




HINSTANCE GetInstance()
{
	return (HINSTANCE)GetModuleHandle(NULL); 
}



// SetBitmapImg - Set a bitmap image on a window
HBITMAP SetBitmapImg(HINSTANCE hinst, WORD nImgId, HWND hwnd)
{
    HBITMAP hBitmap = LoadBitmap(hinst, MAKEINTRESOURCE(nImgId));
    if (hBitmap)
    {
        SendMessage(hwnd, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBitmap);
        // BM_SETIMAGE returns the handle to the _previous_ bitmap.
        return hBitmap;
    }
    return 0;
}


//-----------------------------------------------------------------------------
// Name: CBaseDialog()
// Desc: Constructor
// 
// nID: Resource ID of the dialog
//-----------------------------------------------------------------------------

CBaseDialog::CBaseDialog(int nID)
: m_nID(nID), m_hDlg(0), m_hinst(0), m_hwnd(0),
  m_NcTop(0), m_NcBottom(0), m_NcWidth(0)
{
}


CBaseDialog::~CBaseDialog()
{
}


//-----------------------------------------------------------------------------
// Name: ShowDialog()
// Desc: Displays the dialog
//
// hinst: Application instance
// hwnd:  Handle to the parent window. Use NULL if no parent.
//
// Returns TRUE if successful or FALSE otherwise
//-----------------------------------------------------------------------------
BOOL CBaseDialog::ShowDialog(HINSTANCE hinst, HWND hwnd)
{
    // Cache these...
    m_hinst = hinst;
    m_hwnd = hwnd;

    // Show the dialog. Pass a pointer to ourselves as the LPARAM
    INT_PTR ret = DialogBoxParam(hinst, MAKEINTRESOURCE(m_nID), 
        hwnd, DialogProc, (LPARAM)this);

    if (ret == 0 || ret == -1)
    {
        MessageBox(NULL, TEXT("Error showing the dialog."), NULL, MB_ICONERROR);
        return FALSE;
    }

    return (IDOK == ret);
}


//-----------------------------------------------------------------------------
// Name: DialogProc()
// Desc: DialogProc for the dialog. This is a static class method.
//
// lParam: Pointer to the CBaseDialog object. 
//
// The CBaseDialog class specifies lParam when it calls DialogBoxParam. We store the 
// pointer as user data in the window. 
//
// (Note: The DirectShow CBasePropertyPage class uses the same technique.)
//-----------------------------------------------------------------------------
INT_PTR CALLBACK CBaseDialog::DialogProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
    CBaseDialog *pDlg = 0;  // Pointer to the dialog class that manages the dialog 

    if (msg == WM_INITDIALOG)
    {
        // Get the pointer to the dialog object and store it in 
        // the window's user data

        SetWindowLongPtr(hDlg, DWLP_USER, (LONG)lParam);
        pDlg = (CBaseDialog*)lParam;
        if (pDlg)
        {
            pDlg->m_hDlg = hDlg;
            pDlg->CalcNcSize();
            HRESULT hr = pDlg->OnInitDialog();
            if (FAILED(hr))
            {
                MessageBox(0, TEXT("Could not initialize the dialog."), NULL, MB_ICONERROR);
                pDlg->EndDialog(0);
            }
        }
        return FALSE;
    }

    // Get the dialog object from the window's user data
    pDlg = (CBaseDialog*)(DWORD_PTR) GetWindowLongPtr(hDlg, DWLP_USER);

    if (pDlg != NULL)
    {
        switch (msg)
        {
        case WM_COMMAND:
            switch (LOWORD(wParam))
            {
            case IDOK:
                if (pDlg->OnOK())
                {
                    pDlg->EndDialog(IDOK);
                }
                return TRUE;

            case IDCANCEL:
                if (pDlg->OnCancel())
                {
                    pDlg->EndDialog(IDCANCEL);
                }
                return TRUE;

            default:
                return pDlg->OnCommand((HWND)lParam, LOWORD(wParam), HIWORD(wParam));
            }

        case WM_NOTIFY:
            return pDlg->OnNotify((NMHDR*)lParam);

        default:
            return pDlg->OnReceiveMsg(msg, wParam, lParam);
        }
    }
    else
    {
        return FALSE;
    }
}


//-----------------------------------------------------------------------------
// Name: CalcNcSize()
// Desc: Calculate the non-client top, bottom, and width
//-----------------------------------------------------------------------------

void CBaseDialog::CalcNcSize()
{
    LONG_PTR dwStyles = GetWindowLongPtr(m_hDlg, GWL_STYLE);

    m_NcTop = 0;
    m_NcBottom = 0;
    m_NcWidth = 0;

    if (dwStyles & WS_SIZEBOX)
    {
        m_NcTop += GetSystemMetrics(SM_CYSIZEFRAME);
        m_NcBottom += GetSystemMetrics(SM_CYSIZEFRAME);
        m_NcWidth += GetSystemMetrics(SM_CXSIZEFRAME);
    }
    else if (dwStyles & WS_BORDER)
    {
        m_NcTop += GetSystemMetrics(SM_CYBORDER);
        m_NcBottom += GetSystemMetrics(SM_CYBORDER);
        m_NcWidth += GetSystemMetrics(SM_CXBORDER);
    }

    if (dwStyles & WS_CAPTION)
    {
        m_NcTop += GetSystemMetrics(SM_CYCAPTION);
    }
    if (GetMenu(m_hDlg))
    {
        m_NcTop += GetSystemMetrics(SM_CYMENU);
    }
}

//-----------------------------------------------------------------------------
// Name: RedrawControl()
// Desc: Repaints a control
//
// nID: Resource ID of the control
//-----------------------------------------------------------------------------

void CBaseDialog::RedrawControl(int nID)
{
    // Find the dialog rect and the control rect, both relative to the display
    RECT rcDlg, rcControl;
    GetWindowRect(m_hDlg, &rcDlg);
    GetWindowRect(GetDlgItem(nID), &rcControl);

    // Adjust the dialog rect by the size of the border and caption 
    rcDlg.top += NonClientTop();
    rcDlg.left += NonClientWidth();

    // Find the dialog rect relative to the dialog position
    OffsetRect(&rcControl, - rcDlg.left, - rcDlg.top);

    InvalidateRect(m_hDlg, &rcControl, TRUE);
    UpdateWindow(m_hDlg);
}



