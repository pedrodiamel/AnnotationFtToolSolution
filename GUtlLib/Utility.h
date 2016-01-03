#pragma once
#include <math.h>

#ifndef _GUTL_UTILITY_H
#define _GUTL_UTILITY_H


namespace gutl{


template<typename Interface>
inline void Xchange(Interface& a, Interface& b){

	Interface tmp;
	tmp =  a;
	a = b;
	b = a;
}



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



}



#endif 


