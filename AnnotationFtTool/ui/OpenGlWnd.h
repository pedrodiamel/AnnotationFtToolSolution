

#pragma once



/*!
 * \class	COpenGlWnd
 *
 * \brief	An OpenGL class for graphic windows draw.
 *
 * \author	Pedro
 * \date	30/12/2015
 */

class COpenGlWnd 
	: public CWnd
	, public gutl::CThread
{

	DECLARE_DYNAMIC(COpenGlWnd)

public:

	COpenGlWnd();
	virtual ~COpenGlWnd();
	void DestroyAll();
	virtual BOOL Create( CRect wndsize, int bpp, CWnd *parent );


	// metodos graphic draw
	void DrawText(int posx, int posy, const char *format, ...);
	void DrawText(float posx, float posy, float posz, const char *format, ...);
	void DrawTexture(const unsigned char *buffer, int width, int height, float posx, float posy , float posz = 1.0, bool bfullwnd = false);
	void DrawTexture(const unsigned char *buffer, int width, int height, gutl::CVector pos, GLenum format = GL_RGBA,GLenum type = GL_UNSIGNED_BYTE, bool bfullwnd = false);
	void DrawAxes(gutl::CVector position, float alfa, float beta, float ganma, float scale = 1.0);
	void DrawCube(gutl::CVector position, float alfa, float beta, float ganma);	

	
	// metodos de acceso
	void SetProjetion( gutl::PROJECTION_TYPE projection );
	int GetWidth(){ return m_Width; }
	int GetHeight(){ return m_Height; }


	void Begin(){ while (!wglMakeCurrent(m_hDC,m_hRC)){} }
	void End(){ SwapBuffers(m_hDC); wglMakeCurrent(m_hDC, NULL); }	
	void Update(){ 	::InvalidateRect(m_hWnd,NULL,FALSE);  }


protected:
	
	DECLARE_MESSAGE_MAP()

	// metodos virtuales
	virtual void Init();	
	virtual void DoFrame( float timeDelta ){}

	virtual void InitGraphics();
	virtual void InitInput();
	virtual void InitExtraSubsystems();
	virtual void InitSound();
	virtual void Terminate(){}
	virtual DWORD ThreadProc();
	
	//mouse
	virtual void LButtonDown(UINT nFlags, CPoint point);
	virtual void LButtonUp(UINT nFlags, CPoint point);
	virtual void MouseMove(UINT nFlags, CPoint point);
	virtual void KeyUp(UINT nChar, UINT nRepCnt, UINT nFlags){}
	virtual void KeyDown(UINT nChar, UINT nRepCnt, UINT nFlags){}
	virtual void Size(UINT nType, int cx, int cy){}
	
	virtual void MouseWheel(UINT nFlags, short zDelta, CPoint pt)
	{
		int delta = 10;
		translate_z += ((float)zDelta/WHEEL_DELTA)*delta;
		m_coorWord = gutl::CVector(0,0, translate_z );
	}


protected:
	
	void SetupPixelFormat(void);
	void SetupPalette(void);		
	void SetupTextFormat(void);
			
	//variables	
	HDC m_hDC;// handle del dispositivo de contexto
	HGLRC m_hRC; 
	HPALETTE m_hPalette;
	int m_nFontList;
	float m_lastTime;
	gutl::PROJECTION_TYPE m_projection;
	int m_Width,m_Height;

	GLdouble matrix_projection[16], modelview[16], inverse[16];
		

public:

	// mouse controls
	int mouse_old_x, mouse_old_y;
	bool  blbuttondown;
	bool  brbuttondown;
	float rotate_x, rotate_y;
	float translate_z;
	
	//coordenadas del mundo
	gutl::CVector m_coorWord;
	
	
private:

	//aux
	virtual void CreateObjects();

public:

	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

	afx_msg int  OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnClose();
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
//	afx_msg void OnMouseHover(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
};
