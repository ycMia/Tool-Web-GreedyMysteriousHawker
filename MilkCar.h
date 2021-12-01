#pragma once

#include <stdlib.h>
#include <unistd.h>

#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

class MilkCar
{
public: 
	MilkCar() { }
	
	map<string,string> Milk_POST()
	{
		map<string,string> ret;
		string name;
    	string value;

        int n = atoi(getenv("CONTENT_LENGTH"));
		bool conFlag = false;
		for(int i = 0;i<n;i++)
		{
			char c;cin.get(c);
            
			if(c=='=')
			{
				conFlag = true;
				if(i!=n-1)  continue;
                else
                {
				    ret.insert(make_pair(name,value));
                    break;
                }
			}
			else if(c=='&')
			{
				conFlag = false;
				ret.insert(make_pair(name,value));
				name.clear();value.clear();
				continue;
			}
			else
			{ 
				if(!conFlag)
					name.push_back(c);
				else
                {
					value.push_back(c);
                    if(i==n-1) ret.insert(make_pair(name,value));
                }
			}
		}
		return ret;
	}
	
	void Show_map(map<string,string> mp)
	{
		for(map<string,string>::iterator iter = mp.begin();iter!=mp.end();iter++)
        {
            if(iter->second.size()>0)
    			cout<<iter->first<<" : "<<iter->second<<"</br>"<<endl;
            else
    			cout<<iter->first<<" : "<<"///empty///"<<"</br>"<<endl;
        }
	}
};


