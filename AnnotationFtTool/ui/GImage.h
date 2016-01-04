#pragma once
#include "GObject.h"
#include <GL/glew.h>
#include <GL/freeglut.h>

/*!
 * \class	CGImage
 *
 * \brief	A image graphic.
 *
 * \author	Pedro
 * \date	30/12/2015
 */

class CGImage :
	public CGObject
{
public:

	CGImage();
	~CGImage();


	void SetImage(cv::Mat *img) { 
		
		assert(img);
		m_img = img; 
		m_imWidth = img->cols; m_imHeight = img->rows;
	
	}
	
	void Move(int x, int y) { m_dx = x; m_dy = y; }

	void Zoom(int zoom)
	{

		m_scalaXY += zoom;
		m_scalaX = m_scalaXY; m_scalaY = m_scalaXY;
	
	}

	void Restart() {

		m_dx = 0; m_dy = 0;
		m_scalaXY = 0;
		m_scalaX = m_scalaY = m_scalaXY;

	}


	
	virtual void Prepare();
	virtual void Draw();


private:

	cv::Mat *m_img; //imagen 
	int m_imWidth;
	int m_imHeight;
		
	GLuint gl_rgb_tex;
	GLuint gl_colormap_tex;
	unsigned char color_map[3 * 256];
	int rgb_tex_width; //Real width of texture 
	int rgb_tex_height; //Real heightof texture
	
	float m_scalaXY;
	float m_scalaX; //scala en x
	float m_scalaY; //scala en y
	
	float m_dx;
	float m_dy;


private:

	void draw_image(int x, int y, int w, int h);




};

