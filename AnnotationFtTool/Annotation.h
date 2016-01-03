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


	void selectCurrentWireMask(int idx, string name)
	{		
		current_iter = idx / num_component;
		current_comp = idx % num_component;
		current_comp_name = name;

		CWireMask *mask;
		mask = list_wireMask[current_iter];

		if (!pCurrentWireMask)
			pCurrentWireMask = new CWireMask(*mask);
		else (*pCurrentWireMask) = *mask; //clone

	}



public:

	string db_name; //name 
	unsigned int num_component;	

	unsigned int current_iter;
	unsigned int current_comp;
	string current_comp_name;

	vector<CWireMask*> list_wireMask;
	CWireMask *pCurrentWireMask;

	
};

