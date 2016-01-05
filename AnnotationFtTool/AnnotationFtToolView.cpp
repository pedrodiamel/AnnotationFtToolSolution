
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
#include "MainFrm.h"


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
	ON_COMMAND(ID_TOOLS_RESTART, &CAnnotationFtToolView::OnToolsRestart)
	ON_COMMAND(ID_TOOLS_ADD, &CAnnotationFtToolView::OnToolsAdd)
	ON_COMMAND(ID_TOOLS_COMPONET, &CAnnotationFtToolView::OnToolsComponet)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_COMPONET, &CAnnotationFtToolView::OnUpdateToolsComponet)
	ON_COMMAND(ID_TOOLS_VERTEX, &CAnnotationFtToolView::OnToolsVertex)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_VERTEX, &CAnnotationFtToolView::OnUpdateToolsVertex)
	ON_COMMAND(ID_TOOLS_REPLICATEALL, &CAnnotationFtToolView::OnToolsReplicateall)
	ON_COMMAND(ID_TOOLS_DESELECT, &CAnnotationFtToolView::OnToolsDeselect)
	ON_COMMAND(ID_TOOLS_DELETE, &CAnnotationFtToolView::OnToolsDelete)
END_MESSAGE_MAP()

// CAnnotationFtToolView construction/destruction

CAnnotationFtToolView::CAnnotationFtToolView()
	:m_bCreateCanva(FALSE)
	, m_toolState( TOOLSTATES::ST_VERTEX )
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

	m_wndCanvas.ShowWindow(SW_SHOWNORMAL);
	AdjustLayout();

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

	//Update
	((CMainFrame*)AfxGetMainWnd())->UpdateUI(this);


}


void CAnnotationFtToolView::OnToolsRestart()
{
	// TODO: Add your command handler code here
	m_wndCanvas.Restart();
}


void CAnnotationFtToolView::OnToolsAdd()
{
	// TODO: Add your command handler code here
	CAnnotationFtToolDoc *pDoc;	
	CAnnotation *ann;
	pDoc = GetDocument();
	ann = pDoc->GetAnnotation();
	ann->updateCurrentComponent( (*m_wndCanvas.getSelectPoints()) );
	
	m_wndCanvas.InvalidateRect(NULL, FALSE);
	

}


void CAnnotationFtToolView::OnToolsComponet()
{
	// TODO: Add your command handler code here
	m_toolState = TOOLSTATES::ST_COMPONECT;
	m_wndCanvas.changeCurrentToolState((int)m_toolState);

}


void CAnnotationFtToolView::OnUpdateToolsComponet(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here	
	pCmdUI->SetCheck(m_toolState == TOOLSTATES::ST_COMPONECT);

}


void CAnnotationFtToolView::OnToolsVertex()
{
	// TODO: Add your command handler code here
	m_toolState = TOOLSTATES::ST_VERTEX;
	m_wndCanvas.changeCurrentToolState((int)m_toolState);
}


void CAnnotationFtToolView::OnUpdateToolsVertex(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_toolState == TOOLSTATES::ST_VERTEX);
}


void CAnnotationFtToolView::OnToolsReplicateall()
{
	// TODO: Add your command handler code here
	CAnnotationFtToolDoc *pDoc;
	CAnnotation *ann;
	pDoc = GetDocument();
	ann = pDoc->GetAnnotation();
	ann->replicateCurrentComponent(); 



}


void CAnnotationFtToolView::OnToolsDeselect()
{
	// TODO: Add your command handler code here
	m_wndCanvas.clearSelect();
	m_wndCanvas.InvalidateRect(NULL, FALSE);

}


void CAnnotationFtToolView::OnToolsDelete()
{
	// TODO: Add your command handler code here
	CAnnotationFtToolDoc *pDoc;
	CAnnotation *ann;
	pDoc = GetDocument();
	ann = pDoc->GetAnnotation();

	vector<int> nullpoints; nullpoints.clear();
	ann->updateCurrentComponent(nullpoints);

	m_wndCanvas.InvalidateRect(NULL, FALSE);

}
