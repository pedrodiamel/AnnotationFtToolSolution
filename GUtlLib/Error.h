

#ifndef _GUTL_ERROR_H
#define _GUTL_ERROR_H

#pragma once
#include <string>

namespace gutl{

	/*!
	 * \class	CError
	 *
	 * \brief	An manager error for gutl.
	 *
	 * \author	Pedro
	 * \date	30/12/2015
	 */

	class CError
	{

	public:	

		
		CError(const char* error);
		CError(const CError &err){ m_errorName = err.m_errorName; }
		~CError(void){}
	
		//GetTextError
		//acceso a text error
		inline const char* GetTextError(){ 	return m_errorName.c_str(); }
	

	protected:

		std::string m_errorName;
	};


}

#endif //_GUTL_ERROR_H