#include "stdafx.h"
#include "GImage.h"


CGImage::CGImage():
	m_img(NULL)
{
	m_rBox = CRect(0,0,0,0);
}


CGImage::~CGImage()
{
}

void CGImage::SetPos(int x, int y)
{
	
	m_rBox.left = x; m_rBox.top = y;
	m_position = gutl::CVector(x, y, 0);


}

void CGImage::Move(int x, int y)
{
	m_rBox = m_rBox + x; m_rBox = m_rBox + y;
	m_position += gutl::CVector(x, y, 0);

}


void CGImage::Prepare()
{
	//RGB texture for opengl 
	glGenTextures(1, &gl_colormap_tex);
	glBindTexture(GL_TEXTURE_1D, gl_colormap_tex);
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage1D(GL_TEXTURE_1D, 0, 3, 256, 0, GL_RGB, GL_UNSIGNED_BYTE, color_map);
	
	glGenTextures(1, &gl_rgb_tex);
	glBindTexture(GL_TEXTURE_2D, gl_rgb_tex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glEnable(GL_TEXTURE_2D);


}

void CGImage::Draw()
{

	int x, y, w, h;
	x = m_rBox.left; y = m_rBox.top;
	w = Width(); h = Height();

	draw_image(x, y, w, h);

}

void CGImage::draw_image(int x, int y, int w, int h)
{

	if (!m_img || !m_img->data) //si la imagen no existe
		return;

	//RGB texture
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, gl_rgb_tex);

	GLint bytes;
	GLenum format;
	GLenum type;
	if (m_img->channels() == 1) {
		bytes = 1;
		format = GL_LUMINANCE;
		type = GL_UNSIGNED_BYTE;
	}
	else {
		bytes = 3;
		format = GL_BGR;
		type = GL_UNSIGNED_BYTE;
	}

	glTexImage2D(GL_TEXTURE_2D, 0, bytes, m_img->cols, m_img->rows, 0, format, type, m_img->data);

	glBegin(GL_TRIANGLE_FAN);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glTexCoord2f(0, 0); glVertex3f(x, y, 0);
	glTexCoord2f(1, 0); glVertex3f(x + w, y, 0);
	glTexCoord2f(1, 1); glVertex3f(x + w, y + h, 0);
	glTexCoord2f(0, 1); glVertex3f(x, y + h, 0);
	glEnd();

	glDisable(GL_TEXTURE_2D);

}


