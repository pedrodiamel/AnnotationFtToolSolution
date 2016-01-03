#include "stdafx.h"
#include "GWireMask.h"


CGWireMask::CGWireMask()
{

	m_currentPoint = cv::Point2i(0, 0);

}


CGWireMask::~CGWireMask()
{
}

void CGWireMask::Prepare()
{
}

void CGWireMask::Draw()
{


	drawPoint(m_currentPoint);

}
