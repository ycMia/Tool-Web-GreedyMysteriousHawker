#include <iostream>

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "MethineLoader.h"
#include "WebPainting.h"
#include "CsvReader.h"
#include "MilkCar.h"
#include "CookieOperator.h"

#define DEBUG

#ifdef DEBUG
const int verifySum = 100000;

int main()
{
    CSV_reader * cr = new CSV_reader();
	Table_Solid_Printer * tsp = new Table_Solid_Printer();
	MethineLoader * ml = new MethineLoader("xml/submit.xml");
    Html_Machine * hm = new Html_Machine();
	CookieOperator * co = new CookieOperator();
    GMTTimer * gt = new GMTTimer();

    hm->initPage();
    
    char * cookie = getenv("HTTP_COOKIE");
    char * poi = cookie;

    int cookieStatus = 0;
    
    if(cookie)
    {
        int cookieLength = strlen(cookie);
        string strSession;
        for(int i = 0; i<cookieLength; i++)
        {
            strSession.push_back(*poi++);
            if(strSession == "session=")
                strSession.clear();
        }
        
        if(co->GetVerifyFeature() != -1)
        {
            if(atoi(strSession.c_str())/*atoi(cookie)*/+co->GetVerifyFeature() == verifySum)
            {
                //all normal, allow submit data here
                cookieStatus = 0;
            }
            else
            {
                //may submit the data twice
                cookieStatus = 1;
            }
        }
        else // I've lost the cookieFile
        {
            cookieStatus = 2;
        }
    }
    else
    {
        //the client do NOT have cookie
        cookieStatus = 3;
    }
    
    int seed = (int)time(nullptr) + 15;
    srand(seed);
    int clientSession = (random() % verifySum);
    int serverVerify = verifySum-clientSession;
    cout<<co->GiveClientCookie_str(3600,clientSession);
    if(cookieStatus!=0) co->SetServerCookie(serverVerify);
    
    //end of http Head
    cout<<endl<<endl;
    
    switch(cookieStatus)
    {
        case 0:
        {
            // accept post data
            cout<<"<!--"<<endl;
            MilkCar * mc = new MilkCar();
            mc->Show_map(mc->Milk_POST());
            cout<<"-->"<<endl;
            
            if(mc->AskForDrink("in")!="" || mc->AskForDrink("out")!="")
            {
                ofstream * pofs = new ofstream;
                pofs->open("default.csv",ios::out | ios::app);
                
                if(mc->AskForDrink("in")!="")
                {
                    *pofs<<","<<atoi(mc->AskForDrink("in").c_str())<<","<<mc->AskForDrink("comment")<<endl;
                }
                else
                {
                    *pofs<<atoi(mc->AskForDrink("out").c_str())<<","<<","<<mc->AskForDrink("comment")<<endl;
                }
                pofs->close();
            }
            // show normal Site then
            break;
        }
        case 1:
        case 2:
        case 3:
            // show normal Site
            break;
    }

    cout << "<!-- " << cookieStatus << " -->" << endl;
    cout << "<!-- " << cookie << " -->" << endl;
    cout << "<!-- " << co->GetVerifyFeature() << " -->" << endl;
    
    hm->html();
	hm->body();
    
    

	//TODO: this should be a class doing the table calculating
    tsp->table();
    {
		bool * trFlag = new bool;
		*trFlag = true;
		for(int i = 0;i<1000;i++)
		{
			pair<string,int> res = cr -> GetElement();
			
			if(res.second == -1 || res.second == 0)
				break;
			
			if(*trFlag)
			{
				tsp->tr();
				*trFlag = false;
			}
			
			if(res.second == 1)
			{
				tsp->td();
				if(res.first.size() == 0)
					cout<<"&nbsp;";
				else
					cout<<res.first;
				tsp->td();
				continue;
			}
			else if(res.second == 2)
			{
				tsp->td();
				if(res.first.size() == 0)
					cout<<"&nbsp;";
				else
					cout<<res.first;
				tsp->td();
				tsp->tr();
				*trFlag = true;
				continue;
			}
			/*
			cout<<setw(32)<<right
				if(res.first.size() == 0)
					cout<<"&nbsp;";
				else
					cout<<res.first;
				tsp->td();
				tsp->tr();
				*trFlag = true;
				continue;
			}
			/*
			cout<<setw(32)<<right
				<<(res.first.size() == 0 ? "<<EMPTY>>" : res.first.c_str()) 
				<<" -- ";
			cout<<setw(32)<<left
				<<(res.second==1 ? "Normal" : "Line\'s End")<<endl;
			*/
		}
		delete trFlag;
	}
	tsp->table();
	
	if(cookieStatus!=0)
    {
        string formStr = ml->GetAmmo();
        for(int i=0;i<formStr.size();i++)
            cout<<formStr[i];
        hm->body();
        hm->html();
    }

	return 0;
}

#endif

#ifndef DEBUG
using namespace std;
int main()
{
	CSV_reader * cr = new CSV_reader();
	Table_Solid_Printer * tsp = new Table_Solid_Printer();
	MethineLoader * ml = new MethineLoader("xml/submit.xml");
	Html_Machine * hm = new Html_Machine();
	CookieOperator * co = new CookieOperator();
	
	hm->initPage();
	
	/*
	if(co->IHaveCookie())
	{
		CheckClientCookie()
	}
	else if(
	*/
	
	cout<<endl<<endl;
	
	//TODO: this should be a class doing the outputing csv
    
     
    cout<<"<!--"<<endl;
    MilkCar * mc = new MilkCar();
    mc->Show_map(mc->Milk_POST());
    cout<<"-->"<<endl;
	
	if(mc->AskForDrink("in")!="" || mc->AskForDrink("out")!="")
	{
		ofstream * pofs = new ofstream;
		pofs->open("default.csv",ios::out | ios::app);
		
		if(mc->AskForDrink("in")!="")
		{
			*pofs<<","<<atoi(mc->AskForDrink("in").c_str())<<","<<mc->AskForDrink("comment")<<endl;
		}
		else
		{
			*pofs<<atoi(mc->AskForDrink("out").c_str())<<","<<","<<mc->AskForDrink("comment")<<endl;
		}
		pofs->close();
	}
	
	
	
	return 0;
}

void ShowNormalSite()
{
	hm->html();
	hm->body();
	
	//TODO: this should be a class doing the table calculating
	tsp->table();
	
    {
		bool * trFlag = new bool;
		*trFlag = true;
		for(int i = 0;i<1000;i++)
		{
			pair<string,int> res = cr -> GetElement();
			
			if(res.second == -1 || res.second == 0)
				break;
			
			if(*trFlag)
			{
				tsp->tr();
				*trFlag = false;
			}
			
			if(res.second == 1)
			{
				tsp->td();
				if(res.first.size() == 0)
					cout<<"&nbsp;";
				else
					cout<<res.first;
				tsp->td();
				continue;
			}
			else if(res.second == 2)
			{
				tsp->td();
				if(res.first.size() == 0)
					cout<<"&nbsp;";
				else
					cout<<res.first;
				tsp->td();
				tsp->tr();
				*trFlag = true;
				continue;
			}
			/*
			cout<<setw(32)<<right
				<<(res.first.size() == 0 ? "<<EMPTY>>" : res.first.c_str()) 
				<<" -- ";
			cout<<setw(32)<<left
				<<(res.second==1 ? "Normal" : "Line\'s End")<<endl;
			*/
		}
		delete trFlag;
    }
    tsp->table();
    hm-> body();
    hm-> html();
}
#endif



