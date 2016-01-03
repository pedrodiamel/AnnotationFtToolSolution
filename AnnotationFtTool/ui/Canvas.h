#pragma once


#include "OpenGlWnd.h"
#include "GImage.h"


/*!
 * \class	CCanvas
 *
 * \brief	An application canvas.
 * 			This class manager of graphic app
 *
 * \author	Pedro
 * \date	30/12/2015
 */

class CCanvas
	: public COpenGlWnd
{
public:

	CCanvas();
	~CCanvas();


	virtual void InitExtraSubsystems();
	virtual void DoFrame(float timeDelta);
	virtual void LButtonDown(UINT nFlags, CPoint point);
	virtual void LButtonUp(UINT nFlags, CPoint point);
	virtual void MouseMove(UINT nFlags, CPoint point);
	virtual void MouseWheel(UINT nFlags, short zDelta, CPoint pt);
	virtual void KeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);


	virtual void Size(UINT nType, int cx, int cy)
	{
		SetScrollRange(SB_HORZ, 0, cx);
		SetScrollRange(SB_VERT, 0, cy);
	}
	


	//funciones de acceso
	void setImage(const cv::Mat &img) { 
		
		m_img = img; 
		m_gImage.SetImage(&m_img); //conect to img
		m_gImage.SetPos(0, 0);
		m_gImage.SetSize(img.cols, img.rows);
		InvalidateRect(NULL, FALSE);
		
		
	}


	



private:
	
	//logic object
	cv::Mat m_img; //imagen 
	//CWireMask m_mask;
			
	//graphic object
	CGImage m_gImage;
	//CGWireMask m_gMask;

	//controls
	float m_scroll;
	float m_deltaScroll;
	int m_scrollInc;
	int m_posScrollX;
	int m_posScrollY;


public:

	DECLARE_MESSAGE_MAP()
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);


};

