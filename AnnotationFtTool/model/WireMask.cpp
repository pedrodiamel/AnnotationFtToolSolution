#include "stdafx.h"
#include "WireMask.h"
#include "..\Utitity.h"


CWireMask::CWireMask(const CImageProxy &image)
	: m_image(image)
	, m_idx_componet(0)
{
}

CWireMask::CWireMask(const CImageProxy &image, const vector<Point2f> &points)
	: m_image(image)
	, m_points(points)
	, m_idx_componet(0)
{
}


CWireMask::CWireMask(const string &pathName, const int flag)
	:m_image(pathName, flag)
	, m_idx_componet(0)
{
}



CWireMask::~CWireMask()
{

}





