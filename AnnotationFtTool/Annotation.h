#pragma once
#include "model\WireMask.h"



class CAnnotation
{

public:

	CAnnotation();
	~CAnnotation();

	void addWireMask(CWireMask *wireMask)
	{
		assert(wireMask);
		list_wireMask.push_back(wireMask);
			
	}



public:


	vector<CWireMask*> list_wireMask;
	CWireMask *current_wireMask;
	unsigned int current_iter;

};

