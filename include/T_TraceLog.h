#pragma once
#ifndef __T_TRACELOG_H_
#define __T_TRACELOG_H_
#include <string>
#include <fstream>

using namespace std;

class T_TraceLog
{
public:
	T_TraceLog(string fileName, long long maxSize);
	virtual ~T_TraceLog();
	void AddLog(string operation);
	string GetTime();

private:
	ofstream m_logFile;
	ifstream m_ilogFile;
	string m_fileName;
	long long m_maxSize;
};

#endif