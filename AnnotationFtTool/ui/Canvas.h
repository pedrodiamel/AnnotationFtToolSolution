#pragma once



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
	virtual void Size(UINT nType, int cx, int cy);


	virtual void UpdateScrollX(int posX) {

		m_posScrollX = posX;
		m_gImage.Move(-m_posScrollX, -m_posScrollY);	
		m_gMask.Move(-m_posScrollX, -m_posScrollY);

		SetScrollPos(SB_HORZ, posX);		
			
	}

	virtual void UpdateScrollY(int posY) {
	
		m_posScrollY = posY;
		m_gImage.Move(-m_posScrollX, -m_posScrollY);
		m_gMask.Move(-m_posScrollX, -m_posScrollY);

		SetScrollPos(SB_VERT, posY);		
	
	}

	


	void setMask(CWireMask *mask) {

		assert(mask);
		
		m_img = *(Mat*)(mask->getImage());
		m_gImage.SetImage(&m_img); //conect to img
		m_gImage.SetPos(0, 0);
		m_gImage.SetSize(m_img.cols, m_img.rows);
		
		m_gMask.SetWireMask(mask);
		m_gMask.SetPos(0, 0);
		m_gMask.SetSize(m_img.cols, m_img.rows);
					

		InvalidateRect(NULL, FALSE);

	}


	void Restart()
	{
		
		UpdateScrollX(0);
		UpdateScrollY(0);
		m_gImage.Restart();
		m_gMask.Restart();
	
		InvalidateRect(NULL, FALSE);
	}



private:
	
	//logic object
	cv::Mat m_img; //imagen 
	CWireMask *m_mask;
			
	//graphic object
	CGImage m_gImage;
	CGWireMask m_gMask;

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

