#include "stdafx.h"
#include "ImageProxy.h"


CImageProxy::CImageProxy(const string &pathName, const int flag)
	:m_imagen(NULL)
	,m_path(pathName)
	,m_flag(flag)
{


}


CImageProxy::~CImageProxy()
{
	if (m_imagen)
	{
		delete m_imagen;
		m_imagen = NULL;
	}
}
