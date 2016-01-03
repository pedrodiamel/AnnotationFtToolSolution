#include "stdafx.h"
#include "DataMuctDb.h"


CDataMuctDb::CDataMuctDb()
{
}


CDataMuctDb::~CDataMuctDb()
{
}

bool CDataMuctDb::load(string pathName, string info)
{

	size_t p1 = 0, p2;

	//set image directory
	string idir = pathName; if (idir[idir.length() - 1] != '/') idir += "/";
	idir += "jpg/";

	//get image name
	p2 = info.find(",");
	if (p2 == string::npos) { 
		return false;
	}
	m_name = info.substr(p1, p2 - p1);

	//check name
	if ((strcmp(m_name.c_str(), "i434xe-fn") == 0) || //corrupted data
		(m_name[1] == 'r') ||//ignore flipped images
		(m_name[0] != 'i') //prefijo i
		) 
	{
		m_name = "";                
		return false;
	}
	
	m_name = idir + m_name + ".jpg"; p1 = p2 + 1;

	//get index
	p2 = info.find(",", p1);
	if (p2 == string::npos)
	return false;
	m_index = info.substr(p1, p2 - p1); p1 = p2 + 1;

	//get points
	for (int i = 0; i < 75; i++) {
		
		p2 = info.find(",", p1);
		if (p2 == string::npos)return false;
		string x = info.substr(p1, p2 - p1); p1 = p2 + 1;
		p2 = info.find(",", p1);
		if (p2 == string::npos)return false;
		string y = info.substr(p1, p2 - p1); p1 = p2 + 1;
		m_points.push_back(Point2f(atoi(x.c_str()), atoi(y.c_str())));

	}

	p2 = info.find(",", p1);
	if (p2 == string::npos) return false;
	string x = info.substr(p1, p2 - p1); p1 = p2 + 1;
	string y = info.substr(p1, info.length() - p1);
	m_points.push_back(Point2f(atoi(x.c_str()), atoi(y.c_str())));
	
	return true;
}

