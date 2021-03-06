
// AnnotationFtToolDoc.h : interface of the CAnnotationFtToolDoc class
//


#pragma once
#include "Annotation.h"

class CAnnotationFtToolDoc : public CDocument
{
protected: // create from serialization only
	CAnnotationFtToolDoc();
	DECLARE_DYNCREATE(CAnnotationFtToolDoc)

// Attributes
public:

	CAnnotation* GetAnnotation() { return &m_annotation; }
	

// Operations
public:

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Implementation
public:
	virtual ~CAnnotationFtToolDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

	CAnnotation m_annotation;


// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	afx_msg void OnFileExportar();
};
