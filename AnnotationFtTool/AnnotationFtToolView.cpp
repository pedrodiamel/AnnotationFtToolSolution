
// AnnotationFtToolView.cpp : implementation of the CAnnotationFtToolView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "AnnotationFtTool.h"
#endif

#include "AnnotationFtToolDoc.h"
#include "AnnotationFtToolView.h"

#include "command\LoadMuctCommand.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAnnotationFtToolView

IMPLEMENT_DYNCREATE(CAnnotationFtToolView, CView)

BEGIN_MESSAGE_MAP(CAnnotationFtToolView, CView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_SIZE()
	ON_COMMAND(ID_DATASET_MUCT, &CAnnotationFtToolView::OnDatasetMuct)
END_MESSAGE_MAP()

// CAnnotationFtToolView construction/destruction

CAnnotationFtToolView::CAnnotationFtToolView()
	:m_bCreateCanva(FALSE)
{
	// TODO: add construction code here

}

CAnnotationFtToolView::~CAnnotationFtToolView()
{
}

BOOL CAnnotationFtToolView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
	cs.lpszClass = AfxRegisterWndClass(0);

	return CView::PreCreateWindow(cs);
}

// CAnnotationFtToolView drawing

void CAnnotationFtToolView::AdjustLayout()
{

	if (!GetSafeHwnd() ||
		!m_bCreateCanva)
	{
		return;
	}

	CRect rc;
	GetClientRect(rc);
	m_wndCanvas.SetWindowPos(NULL, rc.left, rc.top, rc.Width(), rc.Height(), SWP_NOACTIVATE | SWP_NOZORDER);



}

void CAnnotationFtToolView::OnDraw(CDC* /*pDC*/)
{
	CAnnotationFtToolDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}

void CAnnotationFtToolView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CAnnotationFtToolView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CAnnotationFtToolView diagnostics

#ifdef _DEBUG
void CAnnotationFtToolView::AssertValid() const
{
	CView::AssertValid();
}

void CAnnotationFtToolView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CAnnotationFtToolDoc* CAnnotationFtToolView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CAnnotationFtToolDoc)));
	return (CAnnotationFtToolDoc*)m_pDocument;
}
#endif //_DEBUG


// CAnnotationFtToolView message handlers


void CAnnotationFtToolView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO: Add your specialized code here and/or call the base class
	CDocument* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	//Create view
	if (!(m_bCreateCanva = m_wndCanvas.Create(CRect(), 32, this)))
	{
		TRACE0("No se pudo crear la ventana de vista\n");
		return;
	}

}


void CAnnotationFtToolView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	AdjustLayout();
}


void CAnnotationFtToolView::OnDatasetMuct()
{
	// TODO: Add your command handler code here
	CLoadMuctCommand cmd(GetDocument());
	cmd.Ejecutar();


}
