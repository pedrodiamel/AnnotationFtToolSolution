#pragma once
#include "GObject.h"
#include "WireMask.h"

#include <GL/glew.h>
#include <GL/freeglut.h>

class CGWireMask :
	public CGObject
{
public:

	//state
	enum MASKUISTATES { ST_POINT = 0, ST_CONECT, ST_SYMMETRY };
	MASKUISTATES m_currentState;
	
	CGWireMask();
	~CGWireMask();


	//funciones acceso
	void SetWireMask(CWireMask *mask) { m_mask = mask; }

	//eventos
	void LButtonUp(int estado, int x, int y)
	{
		m_currentPoint.x = x;
		m_currentPoint.y = y;
	
	}

	
	virtual void Prepare();
	virtual void Draw();


private:

	CWireMask *m_mask;
	cv::Point2f m_currentPoint; //current point 


private:


	///drawPoint
	/** desc: dibuja un punto */
	void drawPoint(const cv::Point2f &p)
	{
		glBegin(GL_POINTS);
		glVertex2f(p.x, p.y);
		glEnd();

	}





};

