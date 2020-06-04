#pragma once
#ifndef __INI_FILE_H_
#define __INI_FILE_H_

#include <string>

using namespace std;

class T_IniFile
{
public:
	T_IniFile();
	T_IniFile(string filename);
	~T_IniFile();

	//Ð´²Ù×÷ string, int, boolean, double
	bool IniWriteString(string section, string key, string value);
	bool IniWriteInteger(string section, string key, int value);
	bool IniWriteDouble(string section, string key, double value);
	bool IniWriteBool(string section, string key, bool value);

	//¶Á²Ù×÷ string, int, boolean, double
	string IniReadString(string section, string key, string defaultValue);
	int IniReadInteger(string section, string key, int defaultValue);
	double IniReadDouble(string section, string key, double defaultValue);
	bool IniReadBool(string section, string key, bool defaultValue);

	bool IniDelKey(string section, string key);

private:
	string m_szFileName;
};

#endif