



#ifndef _ANN_UTILITY_H
#define _ANN_UTILITY_H

#pragma once

// Safe release for interfaces
template<class Interface>
inline void SafeRelease(Interface*& pInterfaceToRelease)
{
    if (pInterfaceToRelease)
    {
        pInterfaceToRelease->Release();
        pInterfaceToRelease = nullptr;
    }
}

// Safe delete pointers
template<class T>
inline void SafeDelete(T*& ptr)
{
    if(ptr)
    {
        delete ptr;
        ptr = nullptr;
    }
}

// Safe delete array
template<class T>
inline void SafeDeleteArray(T*& pArray)
{
    if(pArray)
    {
        delete[] pArray;
        pArray = nullptr;
    }
}

template<typename T>
inline void FreeMemory(T*&mem){
	
	if(mem){
	
		free(mem);
		mem = NULL;
	
	}

}


static void StrToStd( std::string &des, const CString &src )
{
			
	const size_t newsizew = (src.GetLength() + 1)*2;
	char *nstringw = new char[newsizew];
	size_t convertedCharsw = 0;
	wcstombs_s(&convertedCharsw, nstringw, newsizew, src, _TRUNCATE );		
	des = nstringw;
	delete[]nstringw;

	
}






#endif //_ANN_UTILITY_H