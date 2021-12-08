#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <ctime>

#include <fstream>

#include "MilkCar.h"

using namespace std;

class GMTTimer
{
public:
    GMTTimer();
    ~GMTTimer();

    char * GetTime_now();
    char * GetTime(long); 
private:
    char * _destTime;
    const int _timeStrSize = 32;
};

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
				}
				
				_verifyFeature = atoi(cookieStr.c_str());
			}
		}
		ifs.close();
	}
    
    int GetClientCookie()
    {
        return -1;
    }
    
    void SetServerCookie(int serverVerify)
    {
        //danger Method! 
        ofstream ofs;
        ofs.open("cookie.save" , ios::out | ios::trunc);
        ofs << serverVerify;
        ofs.close();
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
	
	string GiveClientCookie_str(int expireTime,int clientSession)
    {
        GMTTimer * gt = new GMTTimer();
        stringstream ss;
        string str;
        ss << "Set-Cookie:session=" << clientSession<< ";expires=" << gt->GetTime(expireTime) << ";path=/cgi-bin/;domain=silcfunc.com;";
        getline(ss,str);

        return str;
    }

private:
	bool _iHaveCookie; // = false
	int _cookieFileLength = 0;
	long long _verifyFeature = -1;
};

GMTTimer::GMTTimer() 
{
    _destTime = new char[_timeStrSize+1];
}

GMTTimer::~GMTTimer()
{
    delete _destTime;
}

char * GMTTimer::GetTime_now()
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
	
char * GMTTimer::GetTime(long offset)
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

