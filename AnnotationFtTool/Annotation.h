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


	void exportFt( const string &pathName) {
	
		vector<int> symmetry;                    //indices of symmetric points
		vector<Vec2i> connections;               //indices of connected points 
		vector<string> imnames;                  //images
		vector<vector<Point2f> > points;         //points
		CWireMask* mask;

		ft_data ft;

		int n = (int)list_wireMask.size();
		if (n == 0)return;


		points.resize(n);
		imnames.resize(n);
		//connections.resize(n);

		for (int i = 0; i < n; i++)
		{
			mask = list_wireMask[i];
			points[i] = mask->m_points;
			imnames[i] = mask->m_image.getPathName();
			
			
		}
	
		mask = list_wireMask[0];
		symmetry = mask->m_symmetry;

		
		CWireComponet *com;
		Vec2i v;

		n = mask->m_components.size();
		for (int i = 0; i < n; i++)
		{			
			com = &mask->m_components[i];
			int m = (int)com->inx_points.size();
			for (int j = 1; j < m; j++)
			{
				v = Vec2i(com->inx_points[j - 1], com->inx_points[j]);
				connections.push_back(v);
			}			

		}

		ft.points = points;
		ft.symmetry = symmetry;
		ft.imnames = imnames;
		ft.connections = connections;

		save_ft(pathName.c_str(), ft);

	
	}


	void removeWireMask(const int idx) {
		
		int maskN = (int)list_wireMask.size();
		if ((idx < 0) || (idx >= maskN))return;
		list_wireMask.erase(list_wireMask.begin() + idx);	
	
	}

	void removeIncompleteWireMask() {
	
		
		
		int maskN = (int)list_wireMask.size();		
		int ptN;

		ptN = list_wireMask[0]->m_points.size();
		for (int i = 1; i < maskN; i++) ptN = max(ptN, (int)list_wireMask[i]->m_points.size());
		for (int i = 1; i < (int)list_wireMask.size(); i++)
		{
			
			//check the point size
			if ((int)list_wireMask[i]->m_points.size() != ptN)
			{ 
				list_wireMask.erase(list_wireMask.begin() + i);
				i--;
			}
			//test of coordenate
			else {			
				
				vector<Point2f> *pPoint;
				int j = 0;
				pPoint = &list_wireMask[i]->m_points;
				int n = (int)pPoint->size();

				for (; j < n ; j++)
				if ((*pPoint)[j].x <= 0 || (*pPoint)[j].y <= 0)
				break;

				if(j!=n)
				{
					list_wireMask.erase(list_wireMask.begin() + i);
					i--;
				}
			}

			

		}
			
	}




public:

	string db_name; //name 
	unsigned int num_component;	
	unsigned int current_iter;
	

	vector<CWireMask*> list_wireMask;
	CWireMask *pCurrentWireMask;

	
};

