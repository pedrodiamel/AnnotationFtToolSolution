#pragma once
#include "DataSet.h"

/*!
 * \class	CDataMuctDb
 *
 * \brief	A data muct database.
 * \note For more information about this data set please see:
 * <a href = "http://www.milbo.org/muct/" ><\a>
 *
 * \author	Pedro
 * \date	28/12/2015
 */

class CDataMuctDb
	: public CDataSet
{



public:

	CDataMuctDb();
	~CDataMuctDb();
	
	virtual bool load(string pathName, string info);
	
};

