#pragma once



#include "ImageProxy.h"

using namespace cv;
using namespace std;



class CWireComponet {

public:
		
	string name;	
	vector<unsigned int> inx_points;
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
	}


	~CWireMask();


	CWireMask operator=(const CWireMask& mask)
	{
		if (&mask != this)
		{
			m_image = mask.m_image;
			m_points = mask.m_points;
			m_components = mask.m_components;
			
		}
		return *this;
	}

	
	vector<Point2f>*
	getPoints() { return &m_points; }
	CImageProxy getImage() { return m_image; }


public:


	CImageProxy m_image; //imagen
	vector<Point2f> m_points; //points
	vector<CWireComponet> m_components; //vector of components

	
	
	

};


