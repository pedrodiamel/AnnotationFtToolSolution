#pragma once
#include <string.h>
#include <opencv2\core.hpp>


using namespace std;
using namespace cv;


class CDataSet
{

protected:

	string m_name;
	string m_index;
	vector<Point2f> m_points;

public:

	CDataSet();
	~CDataSet();

	//funcion access
	string getName()const { return m_name; }
	string getIndex()const { return m_index; }
	vector<Point2f> getPoints()const { return m_points; }

	
	/*!
	* \fn	void CDataMuctDb::load(string pathName, string file_img);
	*
	* \brief	Loads the given file.
	*
	* \author	Pedro
	* \date	28/12/2015
	*
	* \param	info		info for current image.
	* \param	pathName	Full pathname of the file.
	*
	*/

	virtual void load(string pathName, string info)=0;



};

