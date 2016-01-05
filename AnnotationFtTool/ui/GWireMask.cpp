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

	//Obtener puntos 
	vector<Point2f> *pPoint;
	pPoint = m_mask->getPoints();
	Point2f pt, ptant;
	int n, m;
	int icp, iap;
	int selectComponent;



	//Draw all points and mark the select points 
	n = pPoint->size();
	for(size_t i = 0; i < n; i++)
	{
		pt = (*pPoint)[i];
		pt = coor2Pixel(pt);
		
		glColor3f(1.0, (float)b_point_select[i], 0.0);
		glPointSize((!b_point_select[i]) ? 3.0 : 5.0 );
		drawPoint(pt);		
	}


	//Draw component
	
	CWireComponet wireCom;
	n = m_mask->m_components.size();	
	selectComponent = m_mask->m_idx_componet;
	for (int i = 0; i < n; i++)
	{

		glLineWidth(  (selectComponent==i)? 5.0 : 2.0  );
		wireCom = m_mask->m_components[i];
		m = wireCom.inx_points.size();
		for (int j = 1; j < m; j++)
		{
			iap = wireCom.inx_points[j - 1];
			icp = wireCom.inx_points[j];

			pt = (*pPoint)[iap]; ptant = (*pPoint)[icp];
			pt = coor2Pixel(pt);
			ptant = coor2Pixel(ptant);			
			
			glColor3f(0.8, 0.0, 0.8);
			drawLine(pt, ptant);
			
			glColor3f(1.0, 0.0, 1.0);
			drawPoint(pt); 
			drawPoint(ptant);

		}

	}





	//Draw conection points 
	
	n = i_point_select.size();		
	glLineWidth(1.0);
	glColor3f(1.0, 1.0, 1.0);

	for (size_t i = 1; i < n; i++)
	{
		iap = i_point_select[i-1];
		icp = i_point_select[i];

		pt = (*pPoint)[iap]; ptant = (*pPoint)[icp];
		pt = coor2Pixel(pt);
		ptant = coor2Pixel(ptant);
		
		drawLine(pt, ptant);

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

	int length = pPoint->size();
	for (size_t i = 0; i < length; i++)
	{
		Point2f pt = (*pPoint)[i];
		pt = coor2Pixel(pt);
		drawPoint(pt);
	}



}
