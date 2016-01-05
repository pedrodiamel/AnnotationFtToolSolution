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
	virtual void UpdateScrollX(int posX);
	virtual void UpdateScrollY(int posY);

	

	void Restart();
	void setMask(CWireMask *mask);
	vector<int> *getSelectPoints() { return &m_gMask.i_point_select;  }


	void changeCurrentToolState(int state) {
		
		CGWireMask::MASKUISTATES st = (CGWireMask::MASKUISTATES)state;
		m_gMask.changeCurrentState(st);


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

