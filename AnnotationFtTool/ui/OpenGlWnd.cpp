// OGLWnd.cpp : implementation file
//

#include "stdafx.h"
#include "OpenGlWnd.h"



#define CP_AXEX    1 //compile axes



// COGLWnd

IMPLEMENT_DYNAMIC(COpenGlWnd, CWnd)

COpenGlWnd::COpenGlWnd()
	: m_hDC(0)
	, m_hPalette(0)
	, m_hRC(0)
	, m_projection(  gutl::GGL_ORTOGONAL )
	,m_Width(0), m_Height(0)
{
	m_lastTime = (float)timeGetTime();
	m_nFontList = 0;

	//mouse control initialize
	blbuttondown = false;
	brbuttondown = false;
	rotate_x = 0.0;
	rotate_y = 0.0;
	translate_z = -3.0; 

	//cordenadas del mundo
	m_coorWord = gutl::CVector(0.0, 0.0, -5.0);

}

COpenGlWnd::~COpenGlWnd()
{	
	DestroyAll();
		
}


BEGIN_MESSAGE_MAP(COpenGlWnd, CWnd)
	ON_WM_CREATE()
	ON_WM_CLOSE()
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_KEYUP()
	ON_WM_KEYDOWN()
//	ON_WM_MOUSEHOVER()
	ON_WM_MOUSEWHEEL()
END_MESSAGE_MAP()



void COpenGlWnd::DestroyAll()
{

	if( gutl::CThread::IsRunning() )
		gutl::CThread::End();


	if(wglGetCurrentContext()!=NULL)
	{
		// make the rendering context not current
		wglMakeCurrent(NULL, NULL) ;
	}


	if (m_hRC) 
	{	
		wglDeleteContext(m_hRC); 
		m_hRC = 0;		
	}
	
	if (m_hDC) 
	{	
		::ReleaseDC(m_hWnd, m_hDC);
		m_hDC = 0;
	}

	if (m_hPalette)
	{	
		DeleteObject(m_hPalette);
		m_hPalette = 0;
	}

	glDeleteLists( m_nFontList, 128 );

	

}


// SetupPixelFormat
// desc: Establecer el formato del pixel
void COpenGlWnd::SetupPixelFormat(void)
{
	//set format	
	PIXELFORMATDESCRIPTOR pfd, *ppfd; 
	int pixelformat; 
 
	ppfd = &pfd; 
 
	ppfd->nSize = sizeof(PIXELFORMATDESCRIPTOR); 
	ppfd->nVersion = 1; 
	ppfd->dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL |  PFD_DOUBLEBUFFER; 
	ppfd->dwLayerMask = PFD_MAIN_PLANE; 
	ppfd->iPixelType = PFD_TYPE_COLORINDEX; 
	ppfd->cColorBits = 32; 
	ppfd->cDepthBits = 16; 
	ppfd->cAccumBits = 0; 
	ppfd->cStencilBits = 0; 
 
 
	if ( (pixelformat = ChoosePixelFormat(m_hDC, ppfd)) == 0 ) 
	{ 
		throw new gutl::CError("Error al seleccionar el formato del pixel");
	} 
 

	if (SetPixelFormat(m_hDC, pixelformat, ppfd) == FALSE) 
	{ 
		throw new gutl::CError("Error al establecer el formato del pixel");
	}


}

void COpenGlWnd::SetupPalette(void){

	int pixelFormat = GetPixelFormat(m_hDC);
	PIXELFORMATDESCRIPTOR pfd;
	LOGPALETTE* pPal;
	int paletteSize;

	int redMask, greenMask, blueMask;
	int i;

	DescribePixelFormat(m_hDC, pixelFormat, sizeof(PIXELFORMATDESCRIPTOR), &pfd);

	if (pfd.dwFlags & PFD_NEED_PALETTE)
		paletteSize = 1 << pfd.cColorBits;
	else
		return;

	pPal = (LOGPALETTE*)LocalAlloc(LPTR, sizeof(LOGPALETTE) + paletteSize * sizeof(PALETTEENTRY));
	pPal->palVersion = 0x300;
	pPal->palNumEntries = (short)paletteSize;

	//	build a simple RGB color palette
	redMask   = (1 << pfd.cRedBits)   - 1;
	greenMask = (1 << pfd.cGreenBits) - 1;
	blueMask  = (1 << pfd.cBlueBits)  - 1;

	for (i=0; i<paletteSize; ++i)
	{	pPal->palPalEntry[i].peRed = (BYTE)(
			(((i >> pfd.cRedShift) & redMask) * 255) / redMask);
		pPal->palPalEntry[i].peGreen = (BYTE)(
			(((i >> pfd.cGreenShift) & greenMask) * 255) / greenMask);
		pPal->palPalEntry[i].peBlue = (BYTE)(
			(((i >> pfd.cBlueShift) & blueMask) * 255) / blueMask);
		pPal->palPalEntry[i].peFlags = 0;
	}

	m_hPalette = CreatePalette(pPal);
	LocalFree(pPal);

	if (m_hPalette )
	{
		DeleteObject(SelectPalette(m_hDC, m_hPalette, FALSE));
		RealizePalette(m_hDC);
	}
}

void COpenGlWnd::SetupTextFormat(void){

	// Set up the Font characteristics
	HFONT hFont;
	LOGFONT logfont;

	logfont.lfHeight = -12;
	logfont.lfWidth = 0;
	logfont.lfEscapement = 0;
	logfont.lfOrientation = 0;
	logfont.lfWeight = FW_BOLD;
	logfont.lfItalic = FALSE;
	logfont.lfUnderline = FALSE;
	logfont.lfStrikeOut = FALSE;
	logfont.lfCharSet = ANSI_CHARSET;
	logfont.lfOutPrecision = OUT_TT_PRECIS; // OUT_DEFAULT_PRECIS;
	logfont.lfClipPrecision = CLIP_DEFAULT_PRECIS;
	logfont.lfQuality = ANTIALIASED_QUALITY; //DEFAULT_QUALITY;
	logfont.lfPitchAndFamily = FF_DONTCARE | DEFAULT_PITCH; //DEFAULT_PITCH;	
	swprintf_s(logfont.lfFaceName,L"Arial");
	
	// Create the font and display list
	if(!(hFont = CreateFontIndirect(&logfont))){
		
		throw new gutl::CError("Create the font and display list error");
	
	}
	


	SelectObject (m_hDC, hFont);
	
	// Create display lists for glyphs 0 through 128
	m_nFontList = glGenLists(128);
	wglUseFontBitmapsA(m_hDC, 0, 128, m_nFontList);
	DeleteObject(hFont); // Don�t need original font anymore
	
}



BOOL COpenGlWnd::Create( 
	CRect wndsize,
	int bpp, 
	CWnd *parent
	){


	BOOL  bCreate =	CWnd::CreateEx(
			0,
			NULL,NULL, 
			WS_CHILD /*WS_OVERLAPPEDWINDOW*/ | WS_VISIBLE | 
			WS_CLIPCHILDREN | WS_CLIPSIBLINGS,
			wndsize, 
			parent,
			AFX_IDW_PANE_FIRST, 
			NULL
			);

	m_Width = wndsize.Width();
	m_Height = wndsize.Height();

	return bCreate;

	 
}


int COpenGlWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here
		
	Init();
	//gutl::CgutlThread::Begin();	

	return 0;

}





void COpenGlWnd::Init(){

	InitGraphics();
	InitInput();
	//InitExtraSubsystems();
	InitSound();

}

void COpenGlWnd::InitGraphics()
{
	//m_hDC = ::GetDC(m_hWnd);
	if(!(m_hDC = ::GetDC(m_hWnd)))
		throw gutl::CError( "Error al obtener el dispositivo de contexto" );
	
	SetupPixelFormat();	
			
	if(!(m_hRC = wglCreateContext(m_hDC)))
		throw gutl::CError("Error al crear el dispositivo de renderizado");
	wglMakeCurrent(m_hDC, m_hRC);
		
	SetupPalette();
	SetupTextFormat();


	// initialize necessary OpenGL extensions
    glewInit();
    GLboolean bGLEW = glewIsSupported("GL_VERSION_2_0 GL_ARB_pixel_buffer_object");
	InitExtraSubsystems();

	
	CreateObjects();

	wglMakeCurrent(m_hDC, NULL);


}

void COpenGlWnd::InitInput(){

	//cInputLayer::Create( AfxGetInstanceHandle() , m_hWnd , NULL, true, true);

}

void COpenGlWnd::InitExtraSubsystems(){}

void COpenGlWnd::InitSound(){

	//cSoundLayer::Create( m_hWnd );

}


void COpenGlWnd::OnClose()
{
	Terminate();

	// TODO: Add your message handler code here and/or call default
	DestroyAll();
	CWnd::OnClose();
		
	
}


void COpenGlWnd::OnDestroy()
{
	CWnd::OnDestroy();
	Terminate();


	// TODO: Add your message handler code here
	DestroyAll();
}



void COpenGlWnd::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);
	m_Width = cx; m_Height = cy;
	

	if(m_Height==0)
	m_Height = 1;

	

	//Begin current contex
	while (!wglMakeCurrent(m_hDC,m_hRC)){}	

	// Set Viewport to window dimensions
	glViewport(0, 0, m_Width, m_Height);


	// TODO: Add your message handler code here
	GLfloat nRange = 4700.0f;	

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	

	if( m_projection == gutl::GGL_ORTOGONAL){
			
		///glOrtho(-w,w, -h, h, 0, 10); 
		//gluOrtho2D(0,w, h, 0);
		glOrtho (0, m_Width, m_Height, 0, -nRange, nRange);
	
	}	
	else 
	{
		//float nearClip = 1.0f / 100.0f;
		//float farClip  = 256.0f;//127.0f;

		/*glFrustum(
			-0.50f * width  / aspect * nearClip,
			 0.50f * width  / aspect * nearClip,
			-0.50f * height / aspect * nearClip,
			 0.50f * height / aspect * nearClip, nearClip, farClip);
		*/
		GLfloat fAspect  = (GLfloat)m_Width/(GLfloat)m_Height;		
		gluPerspective(/*54.0f*/60.0f, (GLdouble)fAspect, 0.5f, nRange);
		
	}	
		
	glGetDoublev(GL_PROJECTION_MATRIX, matrix_projection);


	// Viewing transformation
	glMatrixMode(GL_MODELVIEW);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glLoadIdentity();
	
	//glClearColor(0.31,0.31,0.34,1.0);
	//glClearColor(1.0,1.0,1.0,1.0);
	
	glGetDoublev(GL_MODELVIEW_MATRIX, modelview);

	//End current contex
	wglMakeCurrent(m_hDC, NULL);
	glDisable(GL_DEPTH_TEST);


	Size(nType,cx,cy);

}

void COpenGlWnd::SetProjetion( gutl::PROJECTION_TYPE projection ){

	if(m_projection==projection)
	return;

	m_projection = projection;

	//Begin current contex	
	//while (!wglMakeCurrent(m_hDC,m_hRC)){}	

	// Set Viewport to window dimensions
	//glViewport(0, 0, m_Width, m_Height);


	// TODO: Add your message handler code here
	GLfloat nRange = 4700.0f;	
	GLfloat fAspect  = (GLfloat)m_Width/(GLfloat)m_Height;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	

	if( m_projection == gutl::GGL_ORTOGONAL){
	glOrtho (0, m_Width, m_Height, 0, -nRange, nRange);	
	}	
	else {
	gluPerspective(/*54.0f*/ 60.0f, (GLdouble)fAspect, 0.5f, nRange);
		
	}			
	
	glGetDoublev(GL_PROJECTION_MATRIX, matrix_projection);
	
	
	// Viewing transformation
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	
	glGetDoublev(GL_MODELVIEW_MATRIX, modelview);

	//End current contex
	//wglMakeCurrent(m_hDC, NULL);
	glDisable(GL_DEPTH_TEST);

}




DWORD COpenGlWnd::ThreadProc(){
	
	bool done = false;

	while( !done && IsRunning() )
	{
			
		
		Sleep(33);		
		::InvalidateRect(m_hWnd,NULL,FALSE);	
				
	}

	return 0;

}


void COpenGlWnd::DrawText(int posx, int posy, const char *format, ...){


	va_list args;
    char buffer[255];
    
    va_start(args, format);
    vsprintf_s(buffer, format, args);
    va_end(args);

	glPushMatrix();

		glLoadIdentity();
		glTranslatef(0.0f, 0.0f, -1.0f);	// translate one unit into the screen

		// Blue 3D Text - Note color is set before the raster position
		//glColor3f(1.0f, 1.0f, 1.0f);
		glPixelZoom(1.0f,1.0f);
		glRasterPos2i(posx, posy);
		
		glPushAttrib(GL_LIST_BIT);
		glListBase(m_nFontList);
		glCallLists ((GLsizei)strlen(buffer), GL_UNSIGNED_BYTE, buffer);
		glPopAttrib();

	glPopMatrix();


}

void COpenGlWnd::DrawText(float posx, float posy, float posz, const char *format, ...){


	va_list args;
    char buffer[255];
    
	if(!format)
		return;


    va_start(args, format);
    vsprintf_s(buffer, format, args);
    va_end(args);

	glPushMatrix();

		//glLoadIdentity();
		//glTranslatef(0.0f, 0.0f, -1.0f);	// translate one unit into the screen

		// Blue 3D Text - Note color is set before the raster position
		//glColor3f(1.0f, 1.0f, 1.0f);
		glPixelZoom(1.0f,1.0f);
		glRasterPos3f(posx, posy, posz);
		
		glPushAttrib(GL_LIST_BIT);
		glListBase(m_nFontList);
		glCallLists ((GLsizei)strlen(buffer), GL_UNSIGNED_BYTE, buffer);
		glPopAttrib();

	glPopMatrix();


}


void COpenGlWnd::DrawTexture(const unsigned char *buffer, int width, int height, float posx, float posy, float posz, bool bfullwnd){
	

	glPushMatrix();
		
		glLoadIdentity();
		glTranslatef(0.0f, 0.0f, -1.0f);	// translate one unit into the screen

		// Targas are 4 byte aligned	
		glPixelStorei(GL_UNPACK_ALIGNMENT, 4); // set memory alignment

		// Use Window coordinates to set raster position
		if(bfullwnd)
		{
			GLint iViewport[4];
			glGetIntegerv(GL_VIEWPORT, iViewport);
			glPixelZoom((GLfloat) iViewport[2] / (GLfloat)width, -(GLfloat) iViewport[3] / (GLfloat)height);


		}
		else
		glPixelZoom(1.0f,-1.0f);
		
		
		if(posz == 0.0 )
		glRasterPos2i(posx, posy);	
		else glRasterPos3f(posx, posy, posz);

		
		glDrawPixels(width, height, GL_BGR,GL_UNSIGNED_BYTE, buffer); // draw the bitmap

	glPopMatrix();

}

//DrawTexture
//desc: Draw texture 
void COpenGlWnd::DrawTexture(
	const unsigned char *buffer, 
	int width, int height, 
	gutl::CVector pos,
	GLenum format,
	GLenum type,
	bool bfullwnd
	){



	glPushMatrix();
		
		glLoadIdentity();
		glTranslatef(0.0f, 0.0f, -1.0f);	// translate one unit into the screen

		// Targas are 4 byte aligned	
		glPixelStorei(GL_UNPACK_ALIGNMENT, 4); // set memory alignment

		// Use Window coordinates to set raster position
		if(bfullwnd)
		{
			GLint iViewport[4];
			glGetIntegerv(GL_VIEWPORT, iViewport);
			glPixelZoom((GLfloat) iViewport[2] / (GLfloat)width, -(GLfloat) iViewport[3] / (GLfloat)height);


		}
		else
		glPixelZoom(1.0f,-1.0f);
		
		if(pos.z == 0.0 )
		glRasterPos2i(pos.x, pos.y);	
		else glRasterPos3f(pos.x, pos.y, pos.z);


		//format:
		//GL_RGB Colors are in red, green, blue order.
		//GL_RGBA Colors are in red, green, blue, alpha order.
		//GL_BGR Colors are in blue, green, red order.
		//GL_BGRA Colors are in blue, green, red, alpha order.
		//GL_RED Each pixel contains a single red component.
		//GL_GREEN Each pixel contains a single green component.
		//GL_BLUE Each pixel contains a single blue component.
		//GL_ALPHA Each pixel contains a single alpha component.
		//GL_LUMINANCE Each pixel contains a single luminance
		//(intensity) component.
		//GL_LUMINANCE_ALPHA Each pixel contains a luminance followed by
		//an alpha component.
		//GL_STENCIL_INDEX Each pixel contains a single stencil value.
		//GL_DEPTH_COMPONENT Each pixel contains a single depth value.
		
		//type
		//GL_UNSIGNED_BYTE		
		glDrawPixels(width, height, format, type, buffer); // draw the bitmap

		
	glPopMatrix();

}




void COpenGlWnd::OnPaint()
{
	//CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	// Do not call __super::OnPaint() for painting messages


	float currTime = (float)timeGetTime();
	float delta = (currTime - m_lastTime)/1000.f;
	
	while (!wglMakeCurrent(m_hDC,m_hRC)){}
	
	//// Call OpenGL drawing code
	DoFrame(delta);	
	
	
	//glFlush();
	SwapBuffers(m_hDC);	
	//glFinish();

	wglMakeCurrent(m_hDC, NULL);


	m_lastTime = currTime;
				
	//Validate the newly painted client area
	::ValidateRect(m_hWnd,NULL);	
	//ValidateRect(NULL);

}


BOOL COpenGlWnd::PreCreateWindow(CREATESTRUCT& cs)
{
	
	// TODO: Add your specialized code here and/or call the base class
	if (!CWnd::PreCreateWindow(cs))
	return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass
		(
		/*CS_HREDRAW | CS_VREDRAW | CS_OWNDC, 
		::LoadCursor(NULL, IDC_ARROW), 
		reinterpret_cast<HBRUSH>(WHITE_BRUSH), 
		NULL*/
		0
		);


	return TRUE;
	
	////return __super::PreCreateWindow(cs);
}



void COpenGlWnd::CreateObjects(){

	
	//Create axes in 3d
	glNewList(CP_AXEX, GL_COMPILE); 
        
	    glColor3ub(255, 0, 0);
		glBegin(GL_LINE_STRIP);
			glVertex3f(0.0, 0.0, 0.0);
			glVertex3f(1.0, 0.0, 0.0);
			glVertex3f(0.75, 0.25, 0.0);
			glVertex3f(0.75, -0.25, 0.0);
			glVertex3f(1.0, 0.0, 0.0);
			glVertex3f(0.75, 0.0, 0.25);
			glVertex3f(0.75, 0.0, -0.25);
			glVertex3f(1.0, 0.0, 0.0);
		glEnd();

		glColor3ub(0, 255, 0);
		glBegin(GL_LINE_STRIP);
			glVertex3f(0.0, 0.0, 0.0);
			glVertex3f(0.0, 1.0, 0.0);
			glVertex3f(0.0, 0.75, 0.25);
			glVertex3f(0.0, 0.75, -0.25);
			glVertex3f(0.0, 1.0, 0.0);
			glVertex3f(0.25, 0.75, 0.0);
			glVertex3f(-0.25, 0.75, 0.0);
			glVertex3f(0.0, 1.0, 0.0);
		glEnd();
		glColor3ub(0, 0, 255);
		glBegin(GL_LINE_STRIP);
			glVertex3f(0.0, 0.0, 0.0);
			glVertex3f(0.0, 0.0, 1.0);
			glVertex3f(0.25, 0.0, 0.75);
			glVertex3f(-0.25, 0.0, 0.75);
			glVertex3f(0.0, 0.0, 1.0);
			glVertex3f(0.0, 0.25, 0.75);
			glVertex3f(0.0, -0.25, 0.75);
			glVertex3f(0.0, 0.0, 1.0);
		glEnd();
    
		
		glColor3ub(255, 255, 0);
		DrawText(1.05, 0.0, 0.0, "x");
		DrawText(0.0, 1.05, 0.0, "y");
		DrawText(0.0, 0.0, 1.05, "z");
		/**/

	glEndList(); 

	///others ...




}



void COpenGlWnd::DrawAxes(gutl::CVector position, float alfa, float beta, float ganma, float scale /*= 1.0*/){
		
	
	glPushMatrix();
	glLoadIdentity();
		
		
		glTranslated(position.x , position.y, position.z);		
		glRotatef(ganma,0.0,0.0,1.0);
		glRotatef(alfa,1.0,0.0,0.0);
		glRotatef(beta,0.0,1.0,0.0);
			
		glScaled(scale,scale,scale);
		glCallList(CP_AXEX); 

	glPopMatrix();
	
	
}


void COpenGlWnd::
	DrawCube(gutl::CVector position, 
	float alfa, float beta, float ganma)
{

	float v[8][3] ={{-0.5f, -0.5f, 0.5f}, {0.5f, -0.5f, 0.5f}, {0.5f, -0.5f, -0.5f},
					{-0.5f, -0.5f, -0.5f}, {-0.5f, 0.5f, 0.5f}, {0.5f, 0.5f, 0.5f},
					{0.5f, 0.5f, -0.5f}, {-0.5f, 0.5f, -0.5f}};


	glPushMatrix();
	glLoadIdentity();

	glTranslated(position.x , position.y, position.z);

		glRotatef(ganma,0.0,0.0,1.0);
		glRotatef(alfa,1.0,0.0,0.0);
		glRotatef(beta,0.0,1.0,0.0);

		//glutSolidCube(0.5);
		glBegin (GL_LINE_LOOP);
			glVertex3fv (v[0]);
			glVertex3fv (v[1]);
			glVertex3fv (v[2]);
			glVertex3fv (v[3]);
			glVertex3fv (v[7]);
			glVertex3fv (v[6]);
			glVertex3fv (v[5]);
			glVertex3fv (v[4]);
		glEnd ();
		glBegin (GL_LINES);
			glVertex3fv (v[0]);
			glVertex3fv (v[3]);
			glVertex3fv (v[1]);
			glVertex3fv (v[5]);
			glVertex3fv (v[2]);
			glVertex3fv (v[6]);
			glVertex3fv (v[4]);
			glVertex3fv (v[7]);
		glEnd ();

	glPopMatrix();
}



void COpenGlWnd::LButtonDown(UINT nFlags, CPoint point)
{		
	mouse_old_x = point.x;
	mouse_old_y = point.y;
	
	blbuttondown = ( nFlags != 9  );
	brbuttondown = !blbuttondown;

}

void COpenGlWnd::LButtonUp(UINT nFlags, CPoint point)
{		
	mouse_old_x = point.x;
	mouse_old_y = point.y;
	blbuttondown = false;
	brbuttondown = false;
}

void COpenGlWnd::MouseMove(UINT nFlags, CPoint point)
{

	float dx, dy;
	dx = (float)(point.x - mouse_old_x);
	dy = (float)(point.y - mouse_old_y);

	//MK_CONTROL   

	if (blbuttondown) {

		rotate_x += dy * 0.2f;
		rotate_y += dx * 0.2f;   

	} else if (brbuttondown ) {

		translate_z += dy * 0.1f;
		m_coorWord = gutl::CVector(0,0, translate_z );

	}

	mouse_old_x = point.x;
	mouse_old_y = point.y;

	::InvalidateRect(m_hWnd,NULL,FALSE);

	
}





void COpenGlWnd::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Agregue aqu� su c�digo de controlador de mensajes o llame al valor predeterminado
	
	LButtonDown(nFlags, point);
	__super::OnLButtonDown(nFlags, point);
}


void COpenGlWnd::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Agregue aqu� su c�digo de controlador de mensajes o llame al valor predeterminado
	LButtonUp(nFlags, point);
	__super::OnLButtonUp(nFlags, point);
}


void COpenGlWnd::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Agregue aqu� su c�digo de controlador de mensajes o llame al valor predeterminado
	MouseMove(nFlags, point);
	__super::OnMouseMove(nFlags, point);
}


void COpenGlWnd::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default
	KeyUp(nChar, nRepCnt, nFlags);
	__super::OnKeyUp(nChar, nRepCnt, nFlags);
}


void COpenGlWnd::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default
	KeyDown(nChar, nRepCnt, nFlags);
	__super::OnKeyDown(nChar, nRepCnt, nFlags);
}


//void COpenGlWnd::OnMouseHover(UINT nFlags, CPoint point)
//{
//	// TODO: Add your message handler code here and/or call default
//	TRACE("OnMouseHover\n");
//	__super::OnMouseHover(nFlags, point);
//}


BOOL COpenGlWnd::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: Add your message handler code here and/or call default
	MouseWheel(nFlags, zDelta, pt);
	return __super::OnMouseWheel(nFlags, zDelta, pt);
}
