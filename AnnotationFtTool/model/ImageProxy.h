#pragma once

using namespace cv;
using namespace std;

class CImageProxy
{
public:
	
		
	CImageProxy(const string &pathName, const int flag=2);
	CImageProxy(const CImageProxy& img)	{
		
		m_path = img.m_path;
		m_flag = img.m_flag;
		m_imagen = NULL;
	
	}

	CImageProxy 
	operator=(const CImageProxy& img){
	
		if (&img != this)
		{
			m_path = img.m_path;
			m_flag = img.m_flag;

			if(m_imagen)
			delete m_imagen;
			
			m_imagen = NULL;


		}
		return *this;
	}


	~CImageProxy();
	operator Mat*(){ return getImagen(); }


private:
	
	Mat* m_imagen;
	string m_path;
	int m_flag;

private:

	Mat* getImagen() {
	

		if (m_imagen) 	//If loader 	
		return m_imagen;
		
		//If not loading 
		Mat img, im;
		if (m_flag < 2) img = imread(m_path, 0);
		else img = imread(m_path, 1);

		//if (m_flag % 2 != 0)flip(img, im, 1); else im = img;

		m_imagen = new Mat();
		(*m_imagen) = img;

		return m_imagen;
	
	}


};

