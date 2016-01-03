

#ifndef _GUTL_THREAD_H
#define _GUTL_THREAD_H


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#define WINDOWS_LEAN_AND_MEAN
#include <windows.h>
#include "Monitor.h"

namespace gutl{

/*!
 * \class	CThread
 *
 * \brief	A thread class.
 *
 * \author	Pedro
 * \date	30/12/2015
 */

class CThread : public CMonitor
{

public:

	CThread(void);
	~CThread(void);

	void Begin();
	void End();
	bool IsRunning();

	/*!
	 * \fn	virtual DWORD CThread::ThreadProc();
	 *
	 * \brief	The vistual Thread proc.
	 * \return	The state.
	 */

	virtual DWORD ThreadProc();
	
	void  SetError( const char *pBuffer );
	const char  *Error();

private:

	HANDLE  m_hThreadHandle; //handle of thread
	DWORD   m_dThreadID;	 //id
	bool    m_bIsRunning;	 //state 
	

protected:

  char m_errorBuffer[ 1000 ];

};

}


#endif //_FTK_THREAD_H