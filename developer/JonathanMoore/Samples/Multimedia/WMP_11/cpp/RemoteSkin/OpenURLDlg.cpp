// OpenURLDlg.cpp : Implementation of COpenURLDlg
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//

#include "stdafx.h"
#include "OpenURLDlg.h"

/////////////////////////////////////////////////////////////////////////////
// COpenURLDlg

//***************************************************************************
// Constructor
//
//***************************************************************************
COpenURLDlg::COpenURLDlg()
{
	m_bstrURL = _T("");
}

//***************************************************************************
// OnCancel()
//
//***************************************************************************
LRESULT COpenURLDlg::OnCancel(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	EndDialog(IDCANCEL);
	return 0;
}

//***************************************************************************
// OnOK()
// Read URL value to m_bstrURL
//
//***************************************************************************
LRESULT COpenURLDlg::OnOK(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	GetDlgItemText(IDC_URL, m_bstrURL.m_str);
	EndDialog(IDOK);
	return 0;
}

//***************************************************************************
// OnBrowse()
// Let users browse to the media file
//
//***************************************************************************
LRESULT COpenURLDlg::OnBrowse(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	OPENFILENAME	ofn;
	TCHAR			szURL[MAX_PATH];

	// display open dialog
	memset(&ofn, 0, sizeof(ofn));
	szURL[0] = _T('\0');
	ofn.lStructSize = sizeof(ofn);
	ofn.lpstrFile = szURL;
	ofn.nMaxFile = MAX_PATH;
	ofn.lpstrDefExt = NULL;
	ofn.Flags = OFN_FILEMUSTEXIST | OFN_EXPLORER;
	ofn.lpstrFilter = _T("Media Files\0*.wma;*.wmv;*.asf;*.mp3;*.avi;*.mpg;*.mpeg;*.wav;*.mid\0All files\0*.*\0");
	ofn.nFilterIndex = 0; 
	ofn.hwndOwner = m_hWnd;
	ofn.hInstance = _Module.GetResourceInstance();

	// If user chooses a file, set m_bstrURL to its path
	if (GetOpenFileName(&ofn))
	{
		m_bstrURL = szURL;
		EndDialog(IDOK);
	}
	else
	{
		EndDialog(IDCANCEL);
	}
		
	return 0;
}
