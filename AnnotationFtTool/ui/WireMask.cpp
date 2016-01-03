#include "stdafx.h"
#include "WireMask.h"


CWireMask::CWireMask()
{



}


CWireMask::~CWireMask()
{

	for (auto iter = m_componentnMap.begin(); iter != m_componentnMap.end(); ++iter)
	{
		delete iter->second;
		iter->second = nullptr;
	}



}
