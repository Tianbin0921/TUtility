#include "stdafx.h"
#include "T_DateTimeUtil.h"

#ifdef _WIN32
#include <Windows.h>
#include <WinSock2.h>
#else
#include <sys/time.h>
#endif

#ifdef _WIN32
void gettimeofday(struct timeval *tp, void *tzp)
{
	time_t clock;
	struct tm tm;
	SYSTEMTIME wtm;
	GetLocalTime(&wtm);
	tm.tm_year = wtm.wYear - 1900;
	tm.tm_mon = wtm.wMonth - 1;
	tm.tm_mday = wtm.wDay;
	tm.tm_hour = wtm.wHour;
	tm.tm_min = wtm.wMinute;
	tm.tm_sec = wtm.wSecond;
	//tm.tm_isdst = -1;
	clock = mktime(&tm);
	tp->tv_sec = clock;
	tp->tv_usec = wtm.wMilliseconds * 1000;
}

//struct
//{
//	__int64 tv_sec;
//	__int64 tv_usec;
//} timeval;
//
//void gettimeofday(struct timeval* tv) {
//
//	auto time_now = std::chrono::system_clock::now();
//	std::chrono::system_clock::time_point tp = std::chrono::system_clock::now();
//	auto duration_in_s = std::chrono::duration_cast<std::chrono::seconds>(time_now.time_since_epoch()).count();
//	auto duration_in_us = std::chrono::duration_cast<std::chrono::microseconds>(time_now.time_since_epoch()).count();
//
//	tv->tv_sec = duration_in_s;
//	tv->tv_usec = duration_in_us;
//}

void strptime(const char* strTime, const char* strFormat, struct tm * stm)
{
	sscanf(strTime, strFormat, &(stm->tm_year), &(stm->tm_mon),
		&(stm->tm_mday), &(stm->tm_hour), &(stm->tm_min), &(stm->tm_sec));

	stm->tm_year -= 1900;
	stm->tm_mon -= 1;
}
#endif

uint32_t T_DateTimeUtil::elapse_seconds(std::chrono::system_clock::time_point &start)
{
	return std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now() - start).count();
}

uint64_t T_DateTimeUtil::elapse_ms(std::chrono::system_clock::time_point &start)
{
	return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - start).count();
}

uint32_t T_DateTimeUtil::now_to_seconds()
{
	return std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

uint64_t T_DateTimeUtil::now_to_ms()
{
	return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

uint64_t T_DateTimeUtil::now_to_us()
{
	return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

uint64_t T_DateTimeUtil::to_ms(const std::chrono::system_clock::time_point &time)
{
	return std::chrono::duration_cast<std::chrono::milliseconds>(time.time_since_epoch()).count();
}

//"%Y-%m-%d %H:%M:%S"
std::string T_DateTimeUtil::to_str(const std::chrono::system_clock::time_point &time)
{
	char _time[25] = { 0 };
	time_t tt = std::chrono::system_clock::to_time_t(time);
	struct tm* local_time = localtime(&tt);
	strftime(_time, 22, "%Y-%m-%d %H:%M:%S", local_time);

	return std::string(_time);
}

//"%d-%02d-%02d %02d:%02d:%02d.%03d"
std::string T_DateTimeUtil::to_str_ex(const std::chrono::system_clock::time_point &time)
{
	uint64_t mill = std::chrono::duration_cast<std::chrono::milliseconds>(time.time_since_epoch()).count()
		- std::chrono::duration_cast<std::chrono::seconds>(time.time_since_epoch()).count() * 1000;

	char _time[25] = { 0 };
	time_t tt = std::chrono::system_clock::to_time_t(time);
	struct tm* local_time = localtime(&tt);

	//sprintf(_time, 22, "%Y-%m-%d %H:%M:%S", local_time);
	sprintf(_time, "%d-%02d-%02d %02d:%02d:%02d.%03d", local_time->tm_year + 1900, local_time->tm_mon + 1,
		local_time->tm_mday, local_time->tm_hour, local_time->tm_min, local_time->tm_sec, mill);

	return std::string(_time);
}

uint64_t T_DateTimeUtil::now_to_ms_ex()
{
	struct timeval tv;
	gettimeofday(&tv, 0);
	return (((uint64_t)tv.tv_sec) * 1000 + (tv.tv_usec) / 1000);
}

//"%Y-%m-%d %H:%M:%S"
time_t T_DateTimeUtil::to_time(std::string str)
{
	time_t t_;
	tm tm_;
	strptime(str.c_str(), "%d-%d-%d %d:%d:%d", &tm_);//将字符串转换为tm时间
	t_ = mktime(&tm_);//将tm时间转换为秒时间

	return t_;
}

//"%d-%02d-%02d %02d:%02d:%02d.%03d"
std::chrono::system_clock::time_point T_DateTimeUtil::to_time_ex(std::string str)
{
	int pos = str.length() - 3;

	time_t t_;
	tm tm_;
	strptime(str.substr(0, pos).c_str(), "%d-%d-%d %d:%d:%d", &tm_);//将字符串转换为tm时间
	t_ = mktime(&tm_);//将tm时间转换为秒时间

	int milli = std::stoi(str.substr(pos));

	return std::chrono::system_clock::time_point(std::chrono::milliseconds(t_ * 1000 + milli));
}

std::string T_DateTimeUtil::to_str_ex(uint64_t ms)
{
	uint64_t mill = ms % 1000;

	char _time[25] = { 0 };
	time_t tt = ms / 1000;
	struct tm *local_time = localtime(&tt);
	sprintf(_time, "%d-%02d-%02d %02d:%02d:%02d.%03d", local_time->tm_year + 1900,
		local_time->tm_mon + 1, local_time->tm_mday, local_time->tm_hour,
		local_time->tm_min, local_time->tm_sec, mill);

	return std::string(_time);
}

uint32_t T_DateTimeUtil::elapse_seconds(time_t &start)
{
	time_t now;
	time(&now);
	return static_cast<uint32_t>(difftime(now, start));
}

//"%Y-%m-%d %H:%M:%S"
std::string T_DateTimeUtil::to_str(const time_t &time)
{
	char _time[25] = { 0 };
	struct tm *local_time;
	local_time = localtime(&time);
	strftime(_time, 22, "%Y-%m-%d %H:%M:%S", local_time);

	return std::string(_time);
}