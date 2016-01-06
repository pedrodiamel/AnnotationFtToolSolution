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

		const int num_component = 8;
		string NAME_COMPONENT[num_component] =
		{
			"mouth",
			"mouth inter",
			"left eye",
			"right eye",
			"nose",
			"left eyebrow",
			"right eyebrow",
			"chin"
		};


		//Get annotation tool class
		CAnnotation *ann = _pDoc->GetAnnotation();
		ann->db_name = "muct-db";
		ann->num_component = num_component;

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
		int i = 1;while (i++<100 && !file.eof()) {

			//file >> str;
			getline(file, str);
			if (str.length() == 0)
				break;

			CDataMuctDb db;			
			if (!db.load(path, str))
				continue;

			
			CImageProxy imagen(db.getPathName());				
			CWireMask *wireMask = new CWireMask(imagen, db.getPoints());
			CWireComponet wireComponent;

			for (size_t comp = 0; comp < num_component; comp++)
			{
				string name_comp = NAME_COMPONENT[comp];				
				wireComponent.name = name_comp;
				wireComponent.inx_points.clear();
				wireComponent.conection.clear();
				wireMask->m_components.push_back(wireComponent);


			}			
			
			(*ann).addWireMask( wireMask );		
			TRACE(">>%s, %s\n", db.getName().c_str(), db.getIndex().c_str());

		}

			
		file.close();
		(*ann).removeIncompleteWireMask();



	
	}


};

