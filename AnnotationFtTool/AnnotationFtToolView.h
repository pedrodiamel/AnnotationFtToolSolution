
// AnnotationFtToolView.h : interface of the CAnnotationFtToolView class
//

#pragma once


class CAnnotationFtToolView : public CView
{
protected: // create from serialization only
	CAnnotationFtToolView();
	DECLARE_DYNCREATE(CAnnotationFtToolView)

// Attributes
public:
	CAnnotationFtToolDoc* GetDocument() const;
	CCanvas	 m_wndCanvas;
	BOOL	 m_bCreateCanva;

	enum TOOLSTATES { ST_VERTEX = 0, ST_COMPONECT, ST_SYMMETRIC,ST_SELECTALL };
	TOOLSTATES m_toolState;
	


// Operations
public:

	void AdjustLayout();

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// Implementation
public:
	virtual ~CAnnotationFtToolView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDatasetMuct();
	afx_msg void OnToolsRestart();
	afx_msg void OnToolsAdd();
	afx_msg void OnToolsComponet();
	afx_msg void OnUpdateToolsComponet(CCmdUI *pCmdUI);
	afx_msg void OnToolsVertex();
	afx_msg void OnUpdateToolsVertex(CCmdUI *pCmdUI);
	afx_msg void OnToolsReplicateall();
	afx_msg void OnToolsDeselect();
	afx_msg void OnToolsDelete();
	afx_msg void OnToolsSymmetric();
	afx_msg void OnUpdateToolsSymmetric(CCmdUI *pCmdUI);
	afx_msg void OnToolsAddsymmetric();
	afx_msg void OnToolsDeletesymmetric();
	afx_msg void OnToolsReplicatesymetric();
};

#ifndef _DEBUG  // debug version in AnnotationFtToolView.cpp
inline CAnnotationFtToolDoc* CAnnotationFtToolView::GetDocument() const
   { return reinterpret_cast<CAnnotationFtToolDoc*>(m_pDocument); }
#endif

