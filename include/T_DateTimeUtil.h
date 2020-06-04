#pragma once
#ifndef __T_DATETIMEUTIL_H_
#define __T_DATETIMEUTIL_H_
#include "Pubfile.h"

class T_DateTimeUtil
{
public:
	static uint32_t elapse_seconds(std::chrono::system_clock::time_point &start);

	static uint64_t elapse_ms(std::chrono::system_clock::time_point &start);

	static uint32_t now_to_seconds();

	static uint64_t now_to_ms();

	static uint64_t now_to_us();

	static uint64_t to_ms(const std::chrono::system_clock::time_point &time);

	//"%Y-%m-%d %H:%M:%S"
	static std::string to_str(const std::chrono::system_clock::time_point &time);

	//"%d-%02d-%02d %02d:%02d:%02d.%03d"
	static std::string to_str_ex(const std::chrono::system_clock::time_point &time);

	static uint64_t now_to_ms_ex();

	//"%Y-%m-%d %H:%M:%S"
	static time_t to_time(std::string str);

	//"%d-%02d-%02d %02d:%02d:%02d.%03d"
	static std::chrono::system_clock::time_point to_time_ex(std::string str);

	static std::string to_str_ex(uint64_t ms);

	static uint32_t elapse_seconds(time_t &start);

	//"%Y-%m-%d %H:%M:%S"
	static std::string to_str(const time_t &time);
};

#endif