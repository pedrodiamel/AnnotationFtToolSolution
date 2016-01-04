#include "stdafx.h"
#include "Canvas.h"


CCanvas::CCanvas()
	: m_scrollInc(10)
	, m_scroll(0)
	, m_deltaScroll(10)
	, m_posScrollX(1)
	, m_posScrollY(1)
	, m_img(cv::Mat())
	, m_mask(NULL)


{


}


CCanvas::~CCanvas()
{
}




void CCanvas::InitExtraSubsystems()
{
	glClearColor(0.31, 0.31, 0.34, 1.0);	
	//glClearColor(0.0, 0.0, 0.0, 1.0);
	
	m_img = cv::Mat();	
	m_gImage.Prepare();
	m_gMask.Prepare();

	//visualize scroll
	ShowScrollBar(SB_BOTH);
	SetScrollPos(SB_HORZ, 0);
	SetScrollPos(SB_VERT, 0);

}

void CCanvas::DoFrame(float timeDelta)
{

	// clear graphics then render from the vbo
	glClear(GL_COLOR_BUFFER_BIT);
	

	m_gImage.Draw(); //draw imge
	m_gMask.Draw();



	//draw text
	DrawText(30, 30, "Scrol X:%d, Y:%d", m_posScrollX, m_posScrollY);
	DrawText(30, 50, "Zoom Z:%f", m_scroll);
	
	

}

void CCanvas::LButtonDown(UINT nFlags, CPoint point)
{
}

void CCanvas::LButtonUp(UINT nFlags, CPoint point)
{
	m_gMask.LButtonUp(0, point.x, point.y);
	InvalidateRect(NULL, FALSE);

}

void CCanvas::MouseMove(UINT nFlags, CPoint point)
{
}

void CCanvas::MouseWheel(UINT nFlags, short zDelta, CPoint pt)
{

	COpenGlWnd::MouseWheel(nFlags, zDelta, pt);

	//actualizar scroll del mouse
	m_deltaScroll = ((float)zDelta / WHEEL_DELTA)*m_scrollInc;
	m_scroll += m_deltaScroll;


	m_gImage.Zoom(m_deltaScroll);
	m_gMask.Zoom(m_deltaScroll);


	InvalidateRect(NULL, FALSE);

}

void CCanvas::KeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
}

inline void CCanvas::Size(UINT nType, int cx, int cy)
{
	SetScrollRange(SB_HORZ, 0, cx);
	SetScrollRange(SB_VERT, 0, cy);
}



BEGIN_MESSAGE_MAP(CCanvas, COpenGlWnd)
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
END_MESSAGE_MAP()

void CCanvas::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: Add your message handler code here and/or call default

	// Get the minimum and maximum scroll-bar positions.
	int minpos;
	int maxpos;
	GetScrollRange(SB_HORZ, &minpos, &maxpos);
	maxpos = GetScrollLimit(SB_HORZ);

	// Get the current position of scroll box.
	int curpos = GetScrollPos(SB_HORZ);

	// Determine the new position of scroll box.
	switch (nSBCode)
	{
	case SB_LEFT:      // Scroll to far left.
		curpos = minpos;
		break;

	case SB_RIGHT:      // Scroll to far right.
		curpos = maxpos;
		break;

	case SB_ENDSCROLL:   // End scroll.
		break;

	case SB_LINELEFT:      // Scroll left.
		if (curpos > minpos)
			curpos--;
		break;

	case SB_LINERIGHT:   // Scroll right.
		if (curpos < maxpos)
			curpos++;
		break;

	case SB_PAGELEFT:    // Scroll one page left.
	{
		// Get the page size. 
		SCROLLINFO   info;
		GetScrollInfo(SB_HORZ, &info, SIF_ALL);

		if (curpos > minpos)
			curpos = __max(minpos, curpos - (int)info.nPage);
	}
	break;

	case SB_PAGERIGHT:      // Scroll one page right.
	{
		// Get the page size. 
		SCROLLINFO   info;
		GetScrollInfo(SB_HORZ, &info, SIF_ALL);

		if (curpos < maxpos)
			curpos = __min(maxpos, curpos + (int)info.nPage);
	}
	break;

	case SB_THUMBPOSITION: // Scroll to absolute position. nPos is the position
		curpos = nPos;      // of the scroll box at the end of the drag operation.
		break;

	case SB_THUMBTRACK:   // Drag scroll box to specified position. nPos is the
		curpos = nPos;     // position that the scroll box has been dragged to.
		break;
	}

	// Set the new position of the thumb (scroll box).
	//SetScrollPos(SB_HORZ, curpos);
	UpdateScrollX(curpos);
	InvalidateRect(NULL, FALSE);

	COpenGlWnd::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CCanvas::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: Add your message handler code here and/or call default

	// Get the minimum and maximum scroll-bar positions.
	int minpos;
	int maxpos;
	GetScrollRange(SB_VERT, &minpos, &maxpos);
	maxpos = GetScrollLimit(SB_VERT);

	// Get the current position of scroll box.
	int curpos = GetScrollPos(SB_VERT);

	// Determine the new position of scroll box.
	switch (nSBCode)
	{
	case SB_LEFT:      // Scroll to far left.
		curpos = minpos;
		break;

	case SB_RIGHT:      // Scroll to far right.
		curpos = maxpos;
		break;

	case SB_ENDSCROLL:   // End scroll.
		break;

	case SB_LINELEFT:      // Scroll left.
		if (curpos > minpos)
			curpos--;
		break;

	case SB_LINERIGHT:   // Scroll right.
		if (curpos < maxpos)
			curpos++;
		break;

	case SB_PAGELEFT:    // Scroll one page left.
	{
		// Get the page size. 
		SCROLLINFO   info;
		GetScrollInfo(SB_VERT, &info, SIF_ALL);

		if (curpos > minpos)
			curpos = __max(minpos, curpos - (int)info.nPage);
	}
	break;

	case SB_PAGERIGHT:      // Scroll one page right.
	{
		// Get the page size. 
		SCROLLINFO   info;
		GetScrollInfo(SB_HORZ, &info, SIF_ALL);

		if (curpos < maxpos)
			curpos = __min(maxpos, curpos + (int)info.nPage);
	}
	break;

	case SB_THUMBPOSITION: // Scroll to absolute position. nPos is the position
		curpos = nPos;      // of the scroll box at the end of the drag operation.
		break;

	case SB_THUMBTRACK:   // Drag scroll box to specified position. nPos is the
		curpos = nPos;     // position that the scroll box has been dragged to.
		break;
	}

	// Set the new position of the thumb (scroll box).
	//SetScrollPos(SB_VERT, curpos);
	UpdateScrollY(curpos);
	InvalidateRect(NULL, FALSE);

	COpenGlWnd::OnVScroll(nSBCode, nPos, pScrollBar);
}


