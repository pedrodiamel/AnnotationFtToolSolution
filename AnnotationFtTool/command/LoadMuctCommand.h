#pragma once
#include "Command.h"
#include "..\AnnotationFtToolDoc.h"
#include "..\model\DataMuctDb.h"


#include <string>
using namespace std;



/*!
 * \class	CLoadMuctCommand
 *
 * \brief	A load muct dataset command.
 *
 * \author	Pedro
 * \date	02/01/2016
 */

class CLoadMuctCommand :
	public pt::CCommand
{

	CAnnotationFtToolDoc* _pDoc;

public:

	CLoadMuctCommand(CAnnotationFtToolDoc* pDoc);
	~CLoadMuctCommand();

	virtual void Ejecutar() {
	

		TRACE("CLoadMuctCommand():Ejecutar \n");

		string pathNameOut = "out/";
		string path = "db/";
		string fname = pathNameOut + "annotations.yaml"; //file to save annotation data to
		string lmfile = path + "muct-landmarks/muct76-opencv.csv";
	
		ifstream file(lmfile.c_str());
		if (!file.is_open()) {
			cerr << "Failed opening " << lmfile << " for reading!" << endl;
			return;
		}
		
		string str;
		//while (!file.eof()) {
		int i = 1;
		while (i++<20 && !file.eof()) {

			//file >> str;
			getline(file, str);
			if (str.length() == 0)
				break;

			CDataMuctDb db;
			db.load(path, str);
			if (db.getName().length() == 0)
				continue;

			//ann.data.imnames.push_back(db.getName());
			//ann.data.points.push_back(db.getPoints());

			TRACE(">>%s, %s\n", db.getName().c_str(), db.getIndex().c_str());

		}

		file.close();




	
	}


};

