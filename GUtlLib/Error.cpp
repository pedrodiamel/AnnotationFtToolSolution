#include "StdAfx.h"
#include "Error.h"


using namespace gutl;

CError::CError(const char* error){

	int iCount;
	char str[] = "Error thrown!!! text: [%s]\n";
	char buff[1024];
	iCount = sprintf_s(buff,str,error);

	#ifdef _CONSOLE
	printf(buff);
	#elif defined(_WINDOWS_)
	OutputDebugStringA(buff);
	#endif

	m_errorName = std::string(buff);

}