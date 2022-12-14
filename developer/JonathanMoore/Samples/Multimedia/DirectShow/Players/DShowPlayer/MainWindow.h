//////////////////////////////////////////////////////////////////////////
// MainWindow.h: Main application window.
// 
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//
//////////////////////////////////////////////////////////////////////////

#pragma once

#include "wincontrol.h"
#include "button.h"
#include "toolbar.h"
#include "slider.h"
#include "tooltip.h"
#include "BaseWindow.h"
#include "DShowPlayer.h"
#include "resource.h"

#include <uuids.h>

// TODO: 
// Status bar - with size grip
// Tool tips (get rid of WTL way)
// Set minimum client area

// status bar: Display position / duration

// Make sure resources are released
// add memory check


// Handle errors from player
// Display change [TEST]
// Multimon
// frame stepping?
// Alpha bitmap?


// Some repaint problems:
//	- When open an audio-only file after a video file was opened


const UINT WM_GRAPH_EVENT = WM_APP + 1;


class MainWindow : public BaseWindow, public GraphEventCallback
{

public:
	MainWindow();
	~MainWindow();
	LRESULT OnReceiveMessage(UINT msg, WPARAM wparam, LPARAM lparam);

	void OnGraphEvent(long eventCode, LONG_PTR param1, LONG_PTR param2);

private:
	LPCTSTR ClassName() const { return TEXT("DSHOWPLAYER"); }
	LPCTSTR MenuName() const { return MAKEINTRESOURCE(IDC_DSHOWPLAYER); }
	LPCTSTR WindowName() const { return TEXT("Dshow Player"); }

	// Message handlers
	HRESULT OnCreate();
	void	OnPaint();
	void	OnSize();
	void	OnTimer();

	// Commands
	void	OnFileOpen();
	void	OnPlay();
	void	OnStop();
	void	OnPause();
	void	OnMute();

	// WM_NOTIFY handlers
    void    OnWmNotify(const NMHDR *pHdr);
	void	OnSeekbarNotify(const NMSLIDER_INFO *pInfo);
	void	OnVolumeSliderNotify(const NMSLIDER_INFO *pInfo);

	void	UpdateUI();
	void	UpdateSeekBar();
	void    StopTimer();

	Rebar		rebar;
	Toolbar		toolbar;
	Slider 		seekbar;
	Slider 		volumeSlider;
    ToolTip     toolTip;

	HBRUSH		brush;
	UINT_PTR	m_timerID; 

	DShowPlayer	*m_pPlayer;
};


