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
		m_imW = img->cols;
		m_imH = img->rows;
	
	}


	void SetPos(int x, int y);
	void SetSize(int w, int h) { m_rBox.right = w; m_rBox.bottom = h; }
	void Move(int x, int y);
	void Zoom(int zoom)
	{

		float w = Width() + 0.5;
		float h = Height() + 0.5;
		float aspX = (float)m_imW / m_imH;
		float aspY = (float)m_imH / m_imW;

		SetSize(w - zoom*aspX,  h - zoom);
	
	}


	
	virtual void Prepare();
	virtual void Draw();


private:

	cv::Mat *m_img; //imagen 
	int m_imW, m_imH;


	
	GLuint gl_rgb_tex;
	GLuint gl_colormap_tex;
	unsigned char color_map[3 * 256];
	int rgb_tex_width; //Real width of texture 
	int rgb_tex_height; //Real heightof texture
	

private:

	void draw_image(int x, int y, int w, int h);




};

