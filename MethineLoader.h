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
		Specify(fileName);
	}
	
	void Specify(string fileName)
	{
		_ifs.open(fileName.c_str(),ios::in);
		if(_ifs.peek()==EOF || _ifs.is_open()==false)
			_ifs.open(Razor2Linux(fileName).c_str(),ios::in);
	}
	
	string Razor2Linux(string str)
	{
		for(int i = 0; i<str.size();++i)
			if(str[i]=='\\') str[i] = '/';
	}
	
	string Razor2Windows(string str)
	{
		for(int i = 0; i<str.size();++i)
			if(str[i]=='/') str[i] = '\\';
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
		Drop();
		Specify(fileName);
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
