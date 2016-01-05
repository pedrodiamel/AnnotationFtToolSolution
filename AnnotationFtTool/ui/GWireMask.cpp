#include "stdafx.h"
#include "GWireMask.h"


CGWireMask::CGWireMask()
	: m_mask(NULL)
	, m_scalaX(1)
	, m_scalaY(1)
	, m_scalaXY(0)
	, m_dx(0)
	, m_dy(0)
	, m_AspX(1)
	, m_AspY(1)
	, m_currentState(ST_VERTEX)
	

{

	m_currentPoint = cv::Point2i(0, 0);

}


CGWireMask::~CGWireMask()
{
}

void CGWireMask::Zoom(int zoom)
{

	m_scalaXY += zoom;
	m_scalaX = m_scalaY = m_scalaXY;

	float w = Width(); float h = Height();
	w = w - m_scalaXY*((float)w / h);
	h = h - m_scalaXY;

	m_AspX = (w / Width());
	m_AspY = (h / Height());

}

void CGWireMask::Restart() {

	m_dx = 0; m_dy = 0;
	m_scalaXY = 0;
	m_scalaX = m_scalaY = m_scalaXY;
	m_AspX = 1;
	m_AspY = 1;

}

void CGWireMask::Prepare()
{
}

void CGWireMask::Draw()
{
	if (!m_mask)return;


	drawAllPoint();

	
	switch ((int)m_currentState)
	{
		case ST_VERTEX: break;
		case ST_COMPONECT: componentDrawState();
		break;
		case ST_SELECTALL:break;
	}

	
	

}


///drawPoint
/** desc: dibuja un punto */
void CGWireMask::drawPoint(const cv::Point2f & p)
{
	glBegin(GL_POINTS);
	glVertex2f(p.x, p.y);
	glEnd();

}



void CGWireMask::drawAllPoint()
{

	//Obtener puntos 
	vector<Point2f> *pPoint;
	pPoint = m_mask->getPoints();
	Point2f pt;
	int n;

	//Draw all points and mark the select points 
	glColor3f(1.0, 0, 0.0);
	glPointSize(3.0);

	n = pPoint->size();
	for (size_t i = 0; i < n; i++)
	{
		pt = (*pPoint)[i];
		pt = coor2Pixel(pt);

		//draw point and resalt the select
		//glColor3f(1.0, (float)b_point_select[i], 0.0);
		//glPointSize((!b_point_select[i]) ? 3.0 : 5.0);		
		
		drawPoint(pt);
	}



}
