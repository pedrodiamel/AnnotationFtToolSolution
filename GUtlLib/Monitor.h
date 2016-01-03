

#ifndef _GUTL_MONITOR_H
#define _GUTL_MONITOR_H

#pragma once
#define WINDOWS_LEAN_AND_MEAN
#include <windows.h>


namespace gutl{

class CMonitor
{

public:
	CMonitor(void);
	virtual ~CMonitor(void);

	void MutexOn() const;
	void MutexOff() const;

private:

	HANDLE m_hMutex;

};

}

#endif //_FTK_MONITOR_H