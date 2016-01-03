


#include "stdafx.h"
#include "Monitor.h"
#include "Error.h"

using namespace gutl;


CMonitor::CMonitor( void )
{

	// This mutex will help the two threads share their toys.
	m_hMutex = CreateMutex( NULL, false, NULL );
	
	if( m_hMutex == NULL )
	throw CError("Monitor(): - Mutex creation failed." );


}


CMonitor::~CMonitor(void)
{

	if( m_hMutex != NULL )
	{
		CloseHandle( m_hMutex );
		m_hMutex = NULL;
	 }
}

void CMonitor::MutexOn() const
{
  WaitForSingleObject( m_hMutex, INFINITE );  // To be safe...
}


void CMonitor::MutexOff() const
{
  ReleaseMutex( m_hMutex );  // To be safe...
}



