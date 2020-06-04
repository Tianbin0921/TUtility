#include "stdafx.h"
#include "T_Thread.h"

T_Thread::T_Thread()
	:m_stopFlag(FALSE)
	, m_hThread(INVALID_HANDLE_VALUE)
{
}

T_Thread::~T_Thread()
{
	StopThread();
}
void T_Thread::StartThread()
{
	m_stopFlag = FALSE;
	unsigned long *p = NULL;
	m_hThread = ::CreateThread(NULL, 0, ThreadProc, this, 0, p);
}

DWORD WINAPI T_Thread::ThreadProc(LPVOID p)
{
	T_Thread* thread = (T_Thread*)p;
	thread->ThreadRun();

	CloseHandle(thread->m_hThread);
	thread->m_hThread = INVALID_HANDLE_VALUE;
	return 0;
}

void T_Thread::StopThread()
{
	m_stopFlag = TRUE;

	if (m_hThread != INVALID_HANDLE_VALUE)
	{
		if (WaitForSingleObject(m_hThread, 1000) != WAIT_ABANDONED)
		{
			CloseHandle(m_hThread);
		}
		m_hThread = INVALID_HANDLE_VALUE;
	}
}


bool T_Thread::IsStopThread()
{
	return m_stopFlag;
}