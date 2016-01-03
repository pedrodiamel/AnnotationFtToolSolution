#include "stdafx.h"
#include "ImageProxy.h"
#include "..\Utitity.h"


CImageProxy::CImageProxy(const string &pathName, const int flag)
	:m_imagen(NULL)
	,m_path(pathName)
	,m_flag(flag)
{
	
}


CImageProxy::~CImageProxy()
{

	SafeDelete(m_imagen);

}
