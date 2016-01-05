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
		int i = idx / num_component;
		int j = idx % num_component;
		current_iter = i;
		

		CWireMask *mask;
		mask = list_wireMask[current_iter];

		if (!pCurrentWireMask)
		pCurrentWireMask = new CWireMask(*mask);
		else (*pCurrentWireMask) = *mask; //clone

		
		pCurrentWireMask->changeCurrentComponent(j);


	}

	CWireMask * getCurrentWireMask() { return pCurrentWireMask;  }

	void updateCurrentComponent(const vector<int> &indxs)
	{
		int n; Vec2i v;
		CWireComponet wireCom;
		wireCom = *pCurrentWireMask->getCurrentComponent();
		wireCom.inx_points = indxs;

		//create conexion ...
		n = indxs.size();
		if (n < 1)return;
		
		wireCom.conection.resize(n);
		for (int i = 1; i < n; i++)
		{
			v = Vec2i(indxs[i - 1], indxs[i]);
			wireCom.conection.push_back(v);
		}
	
		
		//update
		*pCurrentWireMask->getCurrentComponent() = wireCom;
		*list_wireMask[current_iter] = *pCurrentWireMask;
	
	}


	void replicateCurrentComponent()
	{

		//get current component
		 CWireComponet wireCom = *pCurrentWireMask->getCurrentComponent();
		 int idx = pCurrentWireMask->m_idx_componet;

		 //for all wire mask
		 int n = list_wireMask.size();
		 for (int i = 0; i < n; i++)
		 {
			 // update
			 CWireMask* pMask = list_wireMask[i];
			 pMask->changeCurrentComponent(idx);
			 *pMask->getCurrentComponent() = wireCom;

		 }

		 *pCurrentWireMask = *list_wireMask[current_iter];
		 	
	}




public:

	string db_name; //name 
	unsigned int num_component;	
	unsigned int current_iter;
	

	vector<CWireMask*> list_wireMask;
	CWireMask *pCurrentWireMask;

	
};

