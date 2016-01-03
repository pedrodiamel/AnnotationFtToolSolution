

#include "stdafx.h"
#include "Thread.h"
#include "Error.h"
///#include "Global.h"

using namespace gutl;


static DWORD WINAPI GlobalThreadProc( CThread *pThis )
{
  return pThis->ThreadProc();
}



CThread::CThread(void)
	:CMonitor()
{
	m_dThreadID = 0;
	m_hThreadHandle = NULL;
	m_bIsRunning = false;


}


CThread::~CThread(void)
{
	End();	
}



void CThread::Begin()
{

	if(m_bIsRunning)
	throw CError("[CThread]::Begin() - Thread is runing.");

	// Start the thread.
	m_hThreadHandle = 
	CreateThread(	NULL,
					0,
					(LPTHREAD_START_ROUTINE)GlobalThreadProc,
					this,
					0,
					(LPDWORD)&m_dThreadID );

	if( m_hThreadHandle == NULL )
	throw CError("[CThread]::Begin() - Thread creation failed." );

	m_bIsRunning = true;
}



void CThread::End(){


	 if( m_hThreadHandle != NULL )
	  {
		m_bIsRunning = false;
		WaitForSingleObject( m_hThreadHandle, INFINITE );
		CloseHandle( m_hThreadHandle );
		m_hThreadHandle = NULL;
	  }

}


DWORD CThread::ThreadProc()
{
  return 0;
}


bool CThread::IsRunning()
{
  return m_bIsRunning;
}


void CThread::SetError( const char *pBuffer )
{
	if( pBuffer == NULL )
		strcpy_s( m_errorBuffer, "Unspecified." );
	else
	{
		if( sizeof( m_errorBuffer ) > strlen( pBuffer ) )
		strcpy_s( m_errorBuffer, pBuffer );
		else
		{
			strncpy_s( m_errorBuffer, pBuffer, sizeof( m_errorBuffer ) );
			m_errorBuffer[ sizeof( m_errorBuffer ) - 1 ] = '\0';
		}
	}


}


const char *CThread::Error()
{
  return (const char *)m_errorBuffer;
}



