

#pragma once
#include <string.h>


class CAppManagers
{

protected:

	CAppManagers(void);

public:

	~CAppManagers(void);
	static CAppManagers* getInstance();
	static void Destroy(){ if(m_instancia)delete m_instancia;}

	
	
	/// CreateStructFolder
	/** 
	 * @brief crea la estructura de carpeta
	 * @param filename 
	 * @return si existe
	 */
	bool CreateStructFolder(const std::string &pathName)
	{
		
		m_pathName = pathName;	
		std::string file = pathName + "/est-conf.xml";


		if( exists( file.c_str() ) )
		{
			//cargar
			m_numFolder = 0;
			for(directory_iterator it(m_pathName); it != directory_iterator(); it++) 
			{
				std::string name = it->path().filename().string();
				if(name.compare(4,3,"ET-")==0)
				{
					int idx = boost::lexical_cast< int >(name.substr(0,4).c_str())+1;
					if(idx > m_numFolder)
					m_numFolder = idx;
				}
			}
			
			return true;
		
		}

		//crear
		cv::FileStorage fs( file, cv::FileStorage::WRITE); 
		if (!fs.isOpened())
		{
			return false;
		}

		time_t tm;
		time( &tm );
		struct tm *t2 = localtime( &tm );
		char buf[1024];
		strftime( buf, sizeof(buf)-1, "%c", t2 );

		fs << "estudio_Time" << buf;
		
		
		fs.release();			
		
		
		return true;

	}


	/// CreateFolder
	/** 
	 * @brief crear carpeta
	 * @param filename 
	 * @return si existe
	 */
	bool CreateFolder( std::string &folderName )
	{
		
		boost::filesystem::create_directory( m_pathName + "/" + folderName);
		m_currentFolder = folderName;

		return true;
	}
	




private:
	
	static CAppManagers *m_instancia;
	

public:

	std::string m_pathName;
	std::string m_currentFolder;



	unsigned int m_xdcIdx; //index xdc
	unsigned int m_numFolder; //numero de casos en el estudio

	


private:


	/// exists
	/** 
	 * @brief si existe fichero
	 * @param filename 
	 * @return si existe
	 */
	bool exists( const char* filename )
	{
		// try to open the file.  if we can't, it must not exist
		FILE *file;
		file = fopen( filename, "r" );

		// make sure everything went well
		if( file == NULL )
		{
			return false;
		}	
	
		fclose( file );
	
		return true;
	}




};

