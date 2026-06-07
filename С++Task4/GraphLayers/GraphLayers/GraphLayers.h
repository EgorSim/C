
// GraphLayers.h: основной файл заголовка для приложения GraphLayers
//
#pragma once

#ifndef __AFXWIN_H__
	#error "включить pch.h до включения этого файла в PCH"
#endif

#include "resource.h"       // основные символы


// CGraphLayersApp:
// Сведения о реализации этого класса: GraphLayers.cpp
//

class CGraphLayersApp : public CWinAppEx
{
public:
	CGraphLayersApp() noexcept;


// Переопределение
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Реализация
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CGraphLayersApp theApp;
