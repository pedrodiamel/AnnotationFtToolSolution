#pragma once

#include "GObject.h"
#include <GL/glew.h>
#include <GL/freeglut.h>

#include "..\model\WireMask.h"




class CGWireMask :
	public CGObject
{
public:

	//state
	typedef 
	enum _MASKUISTATES 
	{	ST_VERTEX = 0, 
		ST_COMPONECT, 
		ST_SYMMETRIC,
		ST_SELECTALL 
	}MASKUISTATES;
	MASKUISTATES m_currentState;


	
	CGWireMask();
	~CGWireMask();
	
	void Move(int x, int y) { m_dx = x; m_dy = y; }
	void Zoom(int zoom);
	void Restart();


	//funciones acceso
	void SetWireMask(CWireMask *mask) { 
		
		m_mask = mask; 	
		clearSelect();		
	
	}


	void changeCurrentState(MASKUISTATES state) {
	

		if (!m_mask)return;

		m_currentState = state;
		switch (state)
		{
			case ST_VERTEX:break;
			case ST_COMPONECT:break;
			case ST_SYMMETRIC:	break;
			case ST_SELECTALL:break;
		}

		clearSelect();	

	
	}


	//eventos
	void LButtonUp(int estado, int x, int y)
	{
		
		
		if (!m_mask)return;		

		m_currentPoint.x = x;
		m_currentPoint.y = y;
		
		switch (m_currentState)
		{
			case ST_VERTEX:break;
			case ST_COMPONECT: componentLButtonUpState(); break;
			case ST_SYMMETRIC: symmetricLButtonUpState(); break;
			case ST_SELECTALL:break;
		}

		

			
	}

	
	virtual void Prepare();
	virtual void Draw();

	void clearSelect(){

		//clear 
		int n = m_mask->m_points.size();
		b_point_select.resize(n);
		i_symmetry.resize(n);

		for (size_t i = 0; i < n; i++)
		{
			b_point_select[i] = false;
			i_symmetry[i] = i;
		}		
		
		i_point_select.clear();
		m_currentIdx = -1;


	}






private:

	CWireMask *m_mask;
	cv::Point2f m_currentPoint; //current point 
	int m_currentIdx;



	float m_scalaXY;
	float m_scalaX; //scala en x
	float m_scalaY; //scala en y

	int m_dx;
	int m_dy;

	float m_AspX;
	float m_AspY;


public:

	vector<bool> b_point_select;
	vector<int>  i_point_select;
	vector<int>  i_symmetry;


private:

	//draw state
	void vertexDrawState() {
	
	
	}

	void componentDrawState()
	{
		
		drawComponent();
		drawConexion();
		
	}

	void symmetricDrawState() {
	
		drawSymmetricOld();
		drawSymmetric();

	
	}


	//event state
	void componentLButtonUpState()
	{

		Point2f p; int idx;
		p = pixel2Coor(m_currentPoint);
		const double eps = 5.0 / m_AspX;
		idx = m_mask->fiendClosestPoint(p, eps);
		if (idx < 0)
			return;

		if (b_point_select[idx]) //is mark
		{
			if (i_point_select[0] != idx) //is not the one
				return;

		}

		b_point_select[idx] = true;
		i_point_select.push_back(idx);
	
	}


	void symmetricLButtonUpState()
	{
				
		Point2f p; int idx;
		p = pixel2Coor(m_currentPoint);
		const double eps = 5.0 / m_AspX;
		idx = m_mask->fiendClosestPoint(p, eps);
		
		if (idx >= 0) {
			if (m_currentIdx < 0)
			m_currentIdx = idx;
			else {
				i_symmetry[m_currentIdx] = idx;
				i_symmetry[idx] = m_currentIdx;
				m_currentIdx = -1;				
			}
		}
	}
	





	inline Point2f coor2Pixel(const Point2f &pt) 
	{ 		 
		Point2f newpt;
		newpt.x = pt.x*m_AspX + m_dx;
		newpt.y = pt.y*m_AspY + m_dy;

		return newpt;
	
	}

	inline Point2f pixel2Coor(const Point2f &pt)
	{
		Point2f newpt;
		newpt.x = (pt.x - m_dx) / m_AspX;
		newpt.y = (pt.y - m_dy) / m_AspY;
		return newpt;

	}

	

	void drawPoint(const cv::Point2f &p);
	
	///drawLine
	/** desc: dibuja una recta entre dos puntos*/
	void drawLine(cv::Point2f p1, cv::Point2f p2)
	{

		glBegin(GL_LINES);
		glVertex2f(p1.x, p1.y);
		glVertex2f(p2.x, p2.y);
		glEnd();

	}



	void drawAllPoint();
	void drawConexion() {
	
		vector<Point2f> *pPoint;
		pPoint = m_mask->getPoints();
		Point2f pt, ptant;
		int n, m;
		int icp, iap;		

		//Draw conection points 	
		n = i_point_select.size();
		glLineWidth(1.0);
		

		for (size_t i = 1; i < n; i++)
		{
			iap = i_point_select[i - 1];
			icp = i_point_select[i];

			pt = (*pPoint)[iap]; ptant = (*pPoint)[icp];
			pt = coor2Pixel(pt);
			ptant = coor2Pixel(ptant);


			glColor3f(1.0, 1.0, 1.0);
			drawLine(pt, ptant);

			glColor3f(1.0, 1.0, 0.0);
			glPointSize(5.0);
			drawPoint(pt);
			drawPoint(ptant);


		}
	
	
	}


	void drawComponent() {
	
		vector<Point2f> *pPoint;
		pPoint = m_mask->getPoints();
		Point2f pt, ptant;
		int n, m;
		int icp, iap;
		int selectComponent;


		//Draw component	
		CWireComponet wireCom;
		n = m_mask->m_components.size();
		selectComponent = m_mask->m_idx_componet;
		for (int i = 0; i < n; i++)
		{

			glLineWidth((selectComponent == i) ? 5.0 : 2.0);
			glPointSize(5.0);

			wireCom = m_mask->m_components[i];
			m = wireCom.inx_points.size();
			for (int j = 1; j < m; j++)
			{
				iap = wireCom.inx_points[j - 1];
				icp = wireCom.inx_points[j];

				pt = (*pPoint)[iap]; ptant = (*pPoint)[icp];
				pt = coor2Pixel(pt);
				ptant = coor2Pixel(ptant);

				glColor3f(0.7, 0.0, 0.7);
				drawLine(pt, ptant);

				glColor3f(1.0, 0.0, 1.0);
				drawPoint(pt);
				drawPoint(ptant);

			}

		}


	
	}

	void drawSymmetric()
	{

		vector<Point2f> *pPoint;
		pPoint = m_mask->getPoints();
		Point2f pt, ptant;	

				
		glPointSize(5.0);
		glColor3f(0.0, 0.0, 1.0);
		for (int i = 0; i < (int)i_symmetry.size(); i++)
		{

			int j = i_symmetry[i];
			if (j != i) {


				pt = (*pPoint)[i]; ptant = (*pPoint)[j];
				pt = coor2Pixel(pt);
				ptant = coor2Pixel(ptant);
												
				drawPoint(pt);
				drawPoint(ptant);

				
			}
		}

		glColor3f(0.0, 1.0, 1.0);
		if (m_currentIdx >= 0)
		{
			
			pt = (*pPoint)[m_currentIdx];
			pt = coor2Pixel(pt);
			drawPoint(pt);

		}
			
	
	
	}

	void drawSymmetricOld()
	{

		vector<Point2f> *pPoint;
		pPoint = m_mask->getPoints();
		Point2f pt, ptant;

		vector<int> symmetry = m_mask->m_symmetry;

		glPointSize(6.0);
		glColor3f(0.0, 0.5, 0.5);
		for (int i = 0; i < (int)symmetry.size(); i++)
		{

			int j = symmetry[i];
			if (j != i) {


				pt = (*pPoint)[i]; ptant = (*pPoint)[j];
				pt = coor2Pixel(pt);
				ptant = coor2Pixel(ptant);

				drawPoint(pt);
				drawPoint(ptant);


			}
		}



	}



};

