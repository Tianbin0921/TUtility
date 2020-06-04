#include "stdafx.h"
#include "PublicDefine.h"
#include "T_IniFile.h"
#include <sstream>

T_IniFile::T_IniFile()
{
	m_szFileName = ".\\Configuration.ini";
}

T_IniFile::T_IniFile(string filename)
{
	m_szFileName = filename;
}

T_IniFile ::~T_IniFile()
{
}

/**********************************************************************************
*
* 函数功能：删除指定节的指定键
* 入口参数：节名（string）, 键名（string）
* 返 回 值：删除成功返回 TRUE， 否则返回 FALSE
*
**********************************************************************************/
bool T_IniFile::IniDelKey(string section, string key)
{
	if (WritePrivateProfileString(section.c_str(), key.c_str(), NULL, m_szFileName.c_str()))
		return true;
	else
		return false;
}

/**********************************************************************************
*
* 函数功能：向指定节的指定键写入相应的整数值
* 入口参数：节名（string）, 键名（string）， 写入值（int）
* 返 回 值：写入成功返回 TRUE， 否则返回 FALSE
*
**********************************************************************************/
bool T_IniFile::IniWriteInteger(string section, string key, int value)
{
	stringstream str;
	str << value;
	if (WritePrivateProfileString(section.c_str(), key.c_str(), str.str().c_str(), m_szFileName.c_str()))
		return true;
	else
		return false;
}

/**********************************************************************************
*
* 函数功能：向指定节的指定键写入相应的浮点值
* 入口参数：节名（string）, 键名（string）， 写入值（double）
* 返 回 值：写入成功返回 TRUE， 否则返回 FALSE
*
**********************************************************************************/
bool T_IniFile::IniWriteDouble(string section, string key, double value)
{
	stringstream str;
	str << value;
	if (WritePrivateProfileString(section.c_str(), key.c_str(), str.str().c_str(), m_szFileName.c_str()))
		return true;
	else
		return false;
}

/**********************************************************************************
*
* 函数功能：向指定节的指定键写入相应的字符串
* 入口参数：节名（string）, 键名（string）， 写入值（string）
* 返 回 值：写入成功返回 TRUE， 否则返回 FALSE
*
**********************************************************************************/
bool T_IniFile::IniWriteString(string section, string key, string value)
{

	if (WritePrivateProfileString(section.c_str(), key.c_str(), value.c_str(), m_szFileName.c_str()))
		return true;
	else
		return false;
}

/**********************************************************************************
*
* 函数功能：向指定节的指定键写入相应的布尔值
* 入口参数：节名（string）, 键名（string）， 写入值（bool）
* 返 回 值：写入成功返回 TRUE， 否则返回 FALSE
*
**********************************************************************************/
bool T_IniFile::IniWriteBool(string section, string key, bool value)
{
	stringstream str;
	str << (value ? "true" : "false");
	if (WritePrivateProfileString(section.c_str(), key.c_str(), str.str().c_str(), m_szFileName.c_str()))
		return true;
	else
		return false;
}

/**********************************************************************************
*
* 函数功能：读取指定节的指定键的值(string)
* 入口参数：节名（string）, 键名（string）， 默认返回值（string）
* 返 回 值：找到对应值则返回相应值，否则返回指定默认值
*
**********************************************************************************/
string T_IniFile::IniReadString(string section, string key, string defaultValue)
{
	char *value = new char[255];
	GetPrivateProfileString(section.c_str(), key.c_str(), defaultValue.c_str(), value, 255, m_szFileName.c_str());
	string RValue(value);
	delete[] value;
	return RValue;
}

/**********************************************************************************
*
* 函数功能：读取指定节的指定键的值(int)
* 入口参数：节名（string）, 键名（string）， 默认返回值（int）
* 返 回 值：找到对应值则返回相应值，否则返回指定默认值
*
**********************************************************************************/
int T_IniFile::IniReadInteger(string section, string key, int defaultValue)
{
	int value = GetPrivateProfileInt(section.c_str(), key.c_str(), defaultValue, m_szFileName.c_str());
	return value;
}

/**********************************************************************************
*
* 函数功能：读取指定节的指定键的值(double)
* 入口参数：节名（string）, 键名（string）， 默认返回值（double）
* 返 回 值：找到对应值则返回相应值，否则返回指定默认值
*
**********************************************************************************/
double T_IniFile::IniReadDouble(string section, string key, double defaultValue)
{
	char * value = new char[255];
	stringstream str;
	str << defaultValue;
	GetPrivateProfileString(section.c_str(), key.c_str(), str.str().c_str(), value, 255, m_szFileName.c_str());
	string RValue(value);
	delete[] value;
	stringstream str1;
	str1 << RValue;
	double Result;
	str1 >> Result;
	return Result;
}

/**********************************************************************************
*
* 函数功能：读取指定节的指定键的值(bool)
* 入口参数：节名（string）, 键名（string）， 默认返回值（bool）
* 返 回 值：找到对应值则返回相应值，否则返回指定默认值
*
**********************************************************************************/
bool T_IniFile::IniReadBool(string section, string key, bool defaultValue)
{
	char * value = new char[255];
	stringstream str;
	str << (defaultValue ? "True" : "False");
	GetPrivateProfileString(section.c_str(), key.c_str(), str.str().c_str(), value, 255, m_szFileName.c_str());
	string RValue(value);
	delete[] value;
	bool Result;
	Result = (RValue == "True" ? TRUE : FALSE);
	return Result;
}
