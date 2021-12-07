#pragma once

#include <iostream>
#include <string>
#include <stdlib.h>
#include <ctime>

#include <fstream>

#include "MilkCar.h"

using namespace std;

class CookieOperator
{
public:
	CookieOperator() 
	{
		_iHaveCookie = false;
		
		ifstream ifs;
		ifs.open("cookie.save",ios::in);
		if(!ifs.is_open()) {}
		else
		{
			// cout<<"1"<<endl;
			ifs.seekg(0,ios::beg);
			streampos length = ifs.tellg();
			ifs.seekg(0,ios::end);
			length = ifs.tellg() - length;
			ifs.seekg(0,ios::beg);
			
			_cookieFileLength = (int) length;
			if(_cookieFileLength>0)
			{
				// cout<<"11"<<endl;
				_iHaveCookie = true;
				
				string cookieStr;
				for(char c;!ifs.eof() && ifs.peek()!=EOF && ifs.peek()!='\r' && ifs.peek()!='\n' ;)
				{
					ifs.get(c);
					cookieStr.push_back(c);
					// cout<<cookieStr.c_str()<<endl;
				}
				
				_verifyFeature = atoi(cookieStr.c_str());
			}
		}
		ifs.close();
	}
	
	/*
	bool IHaveCookie() 
	{
		return false;
	}
	*/
	
	long long GetVerifyFeature()
	{
		return _verifyFeature;
	}
	
	void GiveClientCookie(int expireTime) {}
private:
	bool _iHaveCookie; // = false
	int _cookieFileLength = 0;
	long long _verifyFeature = -1;
};

class GMTTimer
{
public:
	GMTTimer() 
	{
		_destTime = new char[_timeStrSize+1];
	}
	
	~GMTTimer()
	{
		delete _destTime;
	}
	
 	char * GetTime_now()
	{
		delete _destTime;
		_destTime = new char[_timeStrSize+1];
		
		time_t now = time(nullptr);
		tm* gmt = gmtime(&now);
		
		// e.g.: Sat, 22 Aug 2015 11:48:50 GMT
		//       5+   3+4+   5+   9+       3   = 29
		const char* format = "%a, %d %b %Y %H:%M:%S GMT";
		
		strftime(_destTime,_timeStrSize,format,gmt);
		return _destTime;
	}
	
	char * GetTime(long offset)
	{
		delete _destTime;
		_destTime = new char[_timeStrSize+1];
		
		time_t now = time(nullptr);
		now += offset;
		tm* gmt = gmtime(&now);
		
		// e.g.: Sat, 22 Aug 2015 11:48:50 GMT
		//       5+   3+4+   5+   9+       3   = 29
		const char* format = "%a, %d %b %Y %H:%M:%S GMT";
		
		strftime(_destTime,_timeStrSize,format,gmt);
		return _destTime;
	}
	
	
private:
	char * _destTime;
	const int _timeStrSize = 32;
};
