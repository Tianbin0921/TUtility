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
* �������ܣ�ɾ��ָ���ڵ�ָ����
* ��ڲ�����������string��, ������string��
* �� �� ֵ��ɾ���ɹ����� TRUE�� ���򷵻� FALSE
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
* �������ܣ���ָ���ڵ�ָ����д����Ӧ������ֵ
* ��ڲ�����������string��, ������string���� д��ֵ��int��
* �� �� ֵ��д��ɹ����� TRUE�� ���򷵻� FALSE
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
* �������ܣ���ָ���ڵ�ָ����д����Ӧ�ĸ���ֵ
* ��ڲ�����������string��, ������string���� д��ֵ��double��
* �� �� ֵ��д��ɹ����� TRUE�� ���򷵻� FALSE
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
* �������ܣ���ָ���ڵ�ָ����д����Ӧ���ַ���
* ��ڲ�����������string��, ������string���� д��ֵ��string��
* �� �� ֵ��д��ɹ����� TRUE�� ���򷵻� FALSE
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
* �������ܣ���ָ���ڵ�ָ����д����Ӧ�Ĳ���ֵ
* ��ڲ�����������string��, ������string���� д��ֵ��bool��
* �� �� ֵ��д��ɹ����� TRUE�� ���򷵻� FALSE
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
* �������ܣ���ȡָ���ڵ�ָ������ֵ(string)
* ��ڲ�����������string��, ������string���� Ĭ�Ϸ���ֵ��string��
* �� �� ֵ���ҵ���Ӧֵ�򷵻���Ӧֵ�����򷵻�ָ��Ĭ��ֵ
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
* �������ܣ���ȡָ���ڵ�ָ������ֵ(int)
* ��ڲ�����������string��, ������string���� Ĭ�Ϸ���ֵ��int��
* �� �� ֵ���ҵ���Ӧֵ�򷵻���Ӧֵ�����򷵻�ָ��Ĭ��ֵ
*
**********************************************************************************/
int T_IniFile::IniReadInteger(string section, string key, int defaultValue)
{
	int value = GetPrivateProfileInt(section.c_str(), key.c_str(), defaultValue, m_szFileName.c_str());
	return value;
}

/**********************************************************************************
*
* �������ܣ���ȡָ���ڵ�ָ������ֵ(double)
* ��ڲ�����������string��, ������string���� Ĭ�Ϸ���ֵ��double��
* �� �� ֵ���ҵ���Ӧֵ�򷵻���Ӧֵ�����򷵻�ָ��Ĭ��ֵ
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
* �������ܣ���ȡָ���ڵ�ָ������ֵ(bool)
* ��ڲ�����������string��, ������string���� Ĭ�Ϸ���ֵ��bool��
* �� �� ֵ���ҵ���Ӧֵ�򷵻���Ӧֵ�����򷵻�ָ��Ĭ��ֵ
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
