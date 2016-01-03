#pragma once

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <vector>
#include <map>
#include <assert.h>

using namespace cv;
using namespace std;



class CWireComponet {


public:


	unsigned int id;
	vector<Point2f> points;
	std::vector<unsigned int> conection;
	

};





typedef std::map<const std::string, CWireComponet* >::iterator ComponentMapIterator;
typedef std::map<const std::string, CWireComponet* >::value_type ValueType;



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
	

	vector<vector<Point2f> > points;         //points
	vector<Vec2i> conections;               //indices of connected points
	std::map<const std::string, CWireComponet*> m_componentnMap;


public:


	CWireMask();
	~CWireMask();


	CWireComponet* 
	addNewComponet(
		const std::string &name, //name of contions 
		const CWireComponet &component //struct conection
		)
	{
		
		CWireComponet *pComponent;
		auto iter = addComponent(name);
		pComponent = new CWireComponet();
		iter->second = pComponent;

		return iter->second;

	}

	CWireComponet*
	getComponent(const std::string &name)
	{
		auto iter = m_componentnMap.find(name);
		if (iter != m_componentnMap.end())
		{
			CWireComponet *pConection = (*iter).second;
			return pConection;
		}
		return nullptr;
	}

	void 
	deleteAllComponent()
	{

		for (auto iter = m_componentnMap.begin(); iter != m_componentnMap.end(); ++iter)
		{
			delete iter->second;
			iter->second = nullptr;
		}

		m_componentnMap.clear();

	}








private:

	
	ComponentMapIterator 
	addComponent(const std::string name)
	{
		CWireComponet* pComponent = nullptr;
		ComponentMapIterator iter = m_componentnMap.insert(std::make_pair(name, pComponent)).first;
		return iter;
	}

	void removeComponent(ComponentMapIterator iter)
	{
		assert(iter != m_componentnMap.end());

		delete iter->second;
		iter->second = nullptr;

		m_componentnMap.erase(iter);
	}



	
	



};


