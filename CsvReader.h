#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <utility>
#include <iomanip>

class CSV_reader
{
public:
	CSV_reader()
	{
		_ifs = new ifstream;
		_ifs->open("default.csv",ios::in);
			//TODO: error processing
		streampos b = _ifs->tellg();
		_ifs->seekg(0,ios::end);
		fileSize = _ifs->tellg()-b;
		_ifs->seekg(0,ios::beg);
	}
	
	~CSV_reader()
	{
		_ifs->close();
	}
	
	pair<string,int> GetElement()
	{
		string s = "";
		if(_ifs->eof()) { return make_pair(s,-1); }
		
		char c;
		_ifs->get(c);
		for(;_ifs->eof()==false && c!= '\n' && c!= ','; _ifs->get(c))
		{
			s.push_back(c);
			// cout<<"----"<<endl;
			// cout<<s.c_str()<<endl;
			// cout<<"----"<<endl<<endl;
		}
		if(_ifs->eof())	return make_pair(s,0); //TODO: what is that?
		
		//_ifs->seekg(1,ios::cur);
		if(c==',')
			return make_pair(s,1);
		else if(c=='\n')
			return make_pair(s,2);
		else if(c=='\r') //windows format fix
		{
			_ifs->seekg(1,ios::cur);
			return make_pair(s,2);
		}
		throw c; //TODO: may be buggy
	}
	
	int Out_fileSize() { return (int)fileSize; }
	
private:
	ifstream * _ifs;
	streampos fileSize;
};
