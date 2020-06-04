#include "stdafx.h"
#include "T_TraceLog.h"
#include "T_DateTimeUtil.h"


long long getLen(ifstream & fs)
{
	fs.seekg(0, ios::end);
	long long len = fs.tellg();
	return len;
}

T_TraceLog::T_TraceLog(string fileName, long long maxSize) :m_fileName(fileName), m_maxSize(maxSize)
{
	m_logFile.open(m_fileName, ios::app);
	m_ilogFile.open(m_fileName);
}

T_TraceLog::~T_TraceLog()
{
	if (m_logFile.is_open())
	{
		m_logFile.close();
	}
	if (m_ilogFile.is_open())
	{
		m_ilogFile.close();
	}
}

void T_TraceLog::AddLog(string operation)
{
	if (m_logFile.is_open())
	{
		long long restBytes = m_maxSize - getLen(m_ilogFile);
		if (restBytes > (long long)operation.length())
		{
			m_logFile << GetTime() << ": " << operation << std::endl;
		}
		else
		{
			m_logFile.flush();
			m_logFile.close();
			m_ilogFile.close();

			//然后创建第二个文件
			char timestamp[32];
			time_t	now = time(0);
			struct tm *ptm = localtime(&now);
			ptm->tm_year += 1900;
			ptm->tm_mon += 1;
			memset(timestamp, 0, sizeof(timestamp));
			sprintf(timestamp, "_%04d-%02d-%02d-%02d-%02d-%02d", ptm->tm_year, ptm->tm_mon, ptm->tm_mday, ptm->tm_hour, ptm->tm_min, ptm->tm_sec);

			std::string tmpFile = m_fileName + std::string(timestamp);
			m_logFile.open(tmpFile, std::ios::app);
			m_ilogFile.open(tmpFile);
			m_logFile << GetTime() << " " << operation << std::endl;
		}
	}
}

string T_TraceLog::GetTime()
{
	return T_DateTimeUtil::to_str_ex(T_DateTimeUtil::now_to_ms());
}