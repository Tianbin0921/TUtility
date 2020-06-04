#pragma once
#ifndef __T_THREAD_H
#define __T_THREAD_H
#include "Pubfile.h"
class T_Thread
{
public:
	T_Thread();
	virtual ~T_Thread();

	virtual void    ThreadRun() {}
	void            StartThread();
	void            StopThread();
	bool            IsStopThread();

protected:
	static DWORD WINAPI ThreadProc(LPVOID p);
private:
	bool    m_stopFlag;
	HANDLE  m_hThread;
};
#endif