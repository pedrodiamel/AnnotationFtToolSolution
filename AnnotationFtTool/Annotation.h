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
		wireCom.conection.clear();

				
		n = (int)indxs.size();
		if (n > 0)
		{
			//create conexion ...
			wireCom.conection.resize(n);
			for (int i = 1; i < n; i++)
			{
				v = Vec2i(indxs[i - 1], indxs[i]);
				wireCom.conection.push_back(v);
			}
		
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
		 int n = (int)list_wireMask.size();
		 for (int i = 0; i < n; i++)
		 {
			 if (i == current_iter)
				 continue;

			 // update
			 CWireMask* pMask = list_wireMask[i];
			 pMask->changeCurrentComponent(idx);
			 *pMask->getCurrentComponent() = wireCom;

		 }

		 *pCurrentWireMask = *list_wireMask[current_iter];
		 	
	}



	void updateSymmetric(const vector<int> &symm)
	{

		int n; Vec2i v;
		CWireComponet wireCom;
		pCurrentWireMask->m_symmetry = symm;

		//update
		*list_wireMask[current_iter] = *pCurrentWireMask;

	}


	void replicateSymmetric()
	{

		//get current component
		vector<int> symm = pCurrentWireMask->m_symmetry;

		//for all wire mask
		int n = (int)list_wireMask.size();
		for (int i = 0; i < n; i++)
		{
			if (i == current_iter)
				continue;

			// update
			CWireMask* pMask = list_wireMask[i];
			pMask->m_symmetry = symm;

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

