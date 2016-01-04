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
	enum MASKUISTATES { ST_POINT = 0, ST_CONECT, ST_SYMMETRY };
	MASKUISTATES m_currentState;
	
	CGWireMask();
	~CGWireMask();



	void Move(int x, int y) { m_dx = x; m_dy = y; }
	void Zoom(int zoom)
	{

		m_scalaXY += zoom;
		m_scalaX =  m_scalaY = m_scalaXY;

		//Calcular escalas 
		float w = Width(); float h = Height();
		w = w - m_scalaXY*((float)w / h);
		h = h - m_scalaXY;

		AspX = (w / Width());
		AspY = (h / Height());



	}

	void Restart() {
	
		m_dx = 0; m_dy = 0;
		m_scalaXY = 0;
		m_scalaX = m_scalaY = m_scalaXY;
		AspX = 1;
		AspY = 1;
	
	}


	//funciones acceso
	void SetWireMask(CWireMask *mask) { m_mask = mask; 	ClearSelect(); }

	//eventos
	void LButtonUp(int estado, int x, int y)
	{
		
		
		Point2f p;
		int idx;

		m_currentPoint.x = x;
		m_currentPoint.y = y;
		
		p.x = (x - m_dx) / AspX;
		p.y = (y - m_dy) / AspY;

		const double eps = 5.0/AspX;
		idx = m_mask->fiendClosestPoint(p, eps);
		if (idx < 0)
		return;

		point_select[idx] = true;


	
	}

	
	virtual void Prepare();
	virtual void Draw();

	void ClearSelect(){

		//clear 
		int n = m_mask->m_points.size();
		point_select.resize(n);
		for (size_t i = 0; i < n; i++)
		point_select[i] = false;


	}





private:

	CWireMask *m_mask;
	cv::Point2f m_currentPoint; //current point 

	float m_scalaXY;
	float m_scalaX; //scala en x
	float m_scalaY; //scala en y

	int m_dx;
	int m_dy;

	float AspX;
	float AspY;


public:

	vector<bool> point_select;
	



private:



	inline float normL1(const cv::Point2f &p1, const cv::Point2f &p2){ return (p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y); }
	
	void drawPoint(const cv::Point2f &p);
	void drawAllPoint();




};

