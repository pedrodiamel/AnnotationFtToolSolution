#pragma once



#include "ImageProxy.h"

using namespace cv;
using namespace std;



class CWireComponet {

public:
		
	string name;	
	vector<int> inx_points;
	std::vector<Vec2i> conection;
	

public:

	CWireComponet():name(""){}
	CWireComponet(string nameComponent):name(nameComponent){}
	~CWireComponet() {}
	CWireComponet(const CWireComponet& comp) {
		
		name = comp.name;
		inx_points = comp.inx_points;
		conection = comp.conection;	
	}

	CWireComponet operator=(const CWireComponet& comp)
	{
		if (&comp != this)
		{
			name = comp.name;
			inx_points = comp.inx_points;
			conection = comp.conection;

		}
		return *this;
	
	}



};





/*!
 * \class	CWireMask
 *
 * \brief	A wire mask.
 * 			The wire mask is composition of different component, 
 * 			mouth, 	
 * 			left eye, 
 * 			right eye, 
 * 			nose, 
 * 			left eyebrow, 
 * 			right eyebrow
 * 			chin
 *
 * \author	Pedro
 * \date	31/12/2015
 */

class CWireMask
{


public:




	CWireMask(const CImageProxy &image);
	CWireMask(const CImageProxy &image, const vector<Point2f> &points);
	CWireMask(const string &pathName, const int flag = 2);

	CWireMask(const CWireMask& mask)
		: m_image(mask.m_image)
	{
		m_points = mask.m_points;
		m_components = mask.m_components;
		m_idx_componet = mask.m_idx_componet;
		m_symmetry = mask.m_symmetry;
	}

	~CWireMask();


	CWireMask operator=(const CWireMask& mask)
	{
		if (&mask != this)
		{
			m_image = mask.m_image;
			m_points = mask.m_points;
			m_components = mask.m_components;
			m_idx_componet = mask.m_idx_componet;
			m_symmetry = mask.m_symmetry;

		}
		return *this;
	}


	vector<Point2f>* getPoints() { return &m_points; }
	CImageProxy getImage() { return m_image; }
	void changeCurrentComponent(int idxCom) { check(idxCom);  m_idx_componet = idxCom; }
	CWireComponet* getCurrentComponent() { return &m_components[m_idx_componet]; }



	int fiendClosestPoint(const Point2f p, const double eps = 10) {
		
		float dist; 
		int n = m_points.size();
		for (int i = 0; i < n; i++)
		{
			Point2f pt = m_points[i];
			dist = norm(pt - p);
			if (dist < eps)
				return i;

		}
		return -1;	
	}


	

	
public:


	CImageProxy m_image; //imagen
	vector<Point2f> m_points; //points
	vector<int> m_symmetry;
	vector<CWireComponet> m_components; //vector of components
	int m_idx_componet;
	
	
private:

	void check(int i) { if (i < 0 && i < m_components.size())throw "range over"; }


};


