#pragma once

#include <fstream>
#include <string>

using namespace std;

class MethineLoader
{
public:
	MethineLoader() {}
	MethineLoader(string fileName)
	{
		_ifs.open(fileName.c_str(),ios::in);
	}
	
	string GetAmmo()
	{
		string str = "<!--An Error Occurred-->\n";
		if(!_ifs.is_open()) return str;
		
		str.clear();
		for(char c;_ifs.peek()!=EOF&&!_ifs.eof();)
		{
			_ifs.get(c);
			str.push_back(c);
		}
		_ifs.seekg(0,ios::beg);
		return str;
	}
	
	string GetAmmo(string fileName)
	{
		_ifs.close();
		_ifs.open(fileName.c_str(),ios::in);
		return GetAmmo();
	}
	
	void Occupy(string str)
	{
		_ifs.open(str);
		return;
	}
	
	bool Drop()
	{
		if(_ifs.is_open()) 
		{
			_ifs.close();
			return true;
		}
		return false;
	}
	
private:
	ifstream _ifs;
};
