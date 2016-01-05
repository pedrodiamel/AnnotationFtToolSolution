#include "stdafx.h"
#include "Annotation.h"
#include "Utitity.h"

CAnnotation::CAnnotation()
	: current_iter(0)
	, num_component(0)
	, pCurrentWireMask(NULL)
{
}


CAnnotation::~CAnnotation()
{

	SafeDelete(pCurrentWireMask);

	for (auto iter = list_wireMask.begin(); iter != list_wireMask.end(); iter++)
	{
		CWireMask *mask = (*iter);
		SafeDelete(mask);

	}

}
