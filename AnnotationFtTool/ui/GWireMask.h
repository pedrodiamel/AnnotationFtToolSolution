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
	enum MASKUISTATES { ST_VERTEX = 0, ST_COMPONECT, ST_SELECTALL };
	MASKUISTATES m_currentState;


	
	CGWireMask();
	~CGWireMask();
	
	void Move(int x, int y) { m_dx = x; m_dy = y; }
	void Zoom(int zoom);
	void Restart();


	//funciones acceso
	void SetWireMask(CWireMask *mask) { 
		
		m_mask = mask; 	
		ClearSelect(); 
	
	}


	void changeCurrentState(MASKUISTATES state) {
	
		m_currentState = state;
		switch (state)
		{
		ST_VERTEX:break;
		ST_COMPONECT:break;
		ST_SELECTALL:break;
		}

	
	}


	//eventos
	void LButtonUp(int estado, int x, int y)
	{
		
		
		if (!m_mask)return;		

		m_currentPoint.x = x;
		m_currentPoint.y = y;
		

		Point2f p; int idx;
		p = pixel2Coor(m_currentPoint);
		const double eps = 5.0/m_AspX;
		idx = m_mask->fiendClosestPoint(p, eps);
		if (idx < 0)
		return;

		//if (b_point_select[idx]) //is mark
		//{
		//	if (i_point_select[0] == idx) //is the one
		//	{
		//		//alert is closet point 
		//		return;
		//	}
		//	else //not action
		//	{
		//		return;
		//	}
		//	
		//}
		

		b_point_select[idx] = true;
		i_point_select.push_back(idx);

			
	}

	
	virtual void Prepare();
	virtual void Draw();

	void ClearSelect(){

		//clear 
		int n = m_mask->m_points.size();
		b_point_select.resize(n);

		for (size_t i = 0; i < n; i++)
		b_point_select[i] = false;
		i_point_select.clear();


	}




private:

	CWireMask *m_mask;
	cv::Point2f m_currentPoint; //current point 

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
	


private:


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




	inline float normL1(const cv::Point2f &p1, const cv::Point2f &p2){ return (p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y); }
	

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




};

