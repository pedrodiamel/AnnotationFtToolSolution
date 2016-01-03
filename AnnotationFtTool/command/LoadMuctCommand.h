#pragma once
#include "Command.h"
#include "..\AnnotationFtToolDoc.h"
#include "..\model\DataMuctDb.h"]
#include "..\Annotation.h"
#include "..\model\ImageProxy.h"
#include "..\model\WireMask.h"



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


		//Get annotation tool class
		CAnnotation *ann = &_pDoc->m_annotation;


		//Path configurate 
		string pathNameOut = "out/";
		string path = "db/";
		string fname = pathNameOut + "annotations.yaml"; //file to save annotation data to
		string lmfile = path + "muct-landmarks/muct76-opencv.csv";
		//...

	
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
			if (!db.load(path, str))
				continue;

			
			CImageProxy imagen(db.getName());				
			(*ann).addWireMask( new CWireMask(imagen, db.getPoints()) );

			//Mat *img = ((Mat*)imagen);
			//CWireMask *wireMask = (*ann).list_wireMask[0];

			TRACE(">>%s, %s\n", db.getName().c_str(), db.getIndex().c_str());

		}


		
		file.close();




	
	}


};

