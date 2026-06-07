
// GraphLayersView.cpp: реализация класса CGraphLayersView
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS можно определить в обработчиках фильтров просмотра реализации проекта ATL, эскизов
// и поиска; позволяет совместно использовать код документа в данным проекте.
#ifndef SHARED_HANDLERS
#include "GraphLayers.h"
#endif

#include "GraphLayersDoc.h"
#include "GraphLayersView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGraphLayersView

IMPLEMENT_DYNCREATE(CGraphLayersView, CView)

BEGIN_MESSAGE_MAP(CGraphLayersView, CView)
	// Стандартные команды печати
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CGraphLayersView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// Создание или уничтожение CGraphLayersView

CGraphLayersView::CGraphLayersView() noexcept
{
	// TODO: добавьте код создания

}

CGraphLayersView::~CGraphLayersView()
{
}

BOOL CGraphLayersView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: изменить класс Window или стили посредством изменения
	//  CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// Рисование CGraphLayersView

void CGraphLayersView::OnDraw(CDC* /*pDC*/)
{
	CGraphLayersDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: добавьте здесь код отрисовки для собственных данных
}


// Печать CGraphLayersView


void CGraphLayersView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CGraphLayersView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// подготовка по умолчанию
	return DoPreparePrinting(pInfo);
}

void CGraphLayersView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: добавьте дополнительную инициализацию перед печатью
}

void CGraphLayersView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: добавьте очистку после печати
}

void CGraphLayersView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CGraphLayersView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// Диагностика CGraphLayersView

#ifdef _DEBUG
void CGraphLayersView::AssertValid() const
{
	CView::AssertValid();
}

void CGraphLayersView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGraphLayersDoc* CGraphLayersView::GetDocument() const // встроена неотлаженная версия
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGraphLayersDoc)));
	return (CGraphLayersDoc*)m_pDocument;
}
#endif //_DEBUG


// Обработчики сообщений CGraphLayersView
