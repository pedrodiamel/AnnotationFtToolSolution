#include "stdafx.h"
#include "Annotation.h"


CAnnotation::CAnnotation()
	:current_wireMask(NULL)
	, current_iter(0)
{
}


CAnnotation::~CAnnotation()
{

	for (auto iter = list_wireMask.begin(); iter != list_wireMask.end(); iter++)
	{
		CWireMask *valor = *iter;

		if(valor)
		delete valor;
		valor = NULL;

	}



}
