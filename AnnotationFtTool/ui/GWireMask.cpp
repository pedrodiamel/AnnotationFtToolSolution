#include "stdafx.h"
#include "GWireMask.h"


CGWireMask::CGWireMask()
	: m_mask(NULL)
	, m_scalaX(1)
	, m_scalaY(1)
	, m_scalaXY(0)
	, m_dx(0)
	, m_dy(0)
	, AspX(1)
	, AspY(1)

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
	if (!m_mask)return;

	//Obtener puntos 
	vector<Point2f> *pPoint;
	pPoint = m_mask->getPoints();
	
	

	//Draw all points
	int n = pPoint->size();
	for(size_t i = 0; i < n; i++)
	{
		Point2f pt = (*pPoint)[i];

		//scalar 
		pt.x = pt.x*AspX + m_dx;
		pt.y = pt.y*AspY + m_dy;

		//draw
		if(!point_select[i])
		{
			glColor3f(1.0, 0.0, 0.0);
			glPointSize(3.0);		
		
		}
		else {
		
			glColor3f(1.0, 1.0, 0.0);
			glPointSize(5.0);
		
		}

		drawPoint(pt);

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

	vector<Point2f> *pPoint;
	pPoint = m_mask->getPoints();


	float w = Width(); float h = Height();
	float aspX = (float)w / h;
	float aspY = (float)h / w;

	w = w - m_scalaXY*aspX;
	h = h - m_scalaXY;

	float AspX = (w / Width());
	float AspY = (h / Height());


	int length = pPoint->size();
	for (size_t i = 0; i < length; i++)
	{
		Point2f pt = (*pPoint)[i];

		pt.x = pt.x*AspX + m_dx;
		pt.y = pt.y*AspY + m_dy;

		drawPoint(pt);
	}



}
