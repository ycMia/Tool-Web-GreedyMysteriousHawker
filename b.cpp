#include <iostream>

#include "MethineLoader.h"
#include "WebPainting.h"
#include "CsvReader.h"
#include "MilkCar.h"
#include "CookieOperator.h"

#define DEBUG

#ifdef DEBUG
int main()
{
	CookieOperator * co = new CookieOperator();
	cout<< co->GetVerifyFeature() <<endl;
	
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
	MilkCar * mc = new MilkCar();
	mc->Milk_POST();
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
			*pofs<<atoi(mc->AskForDrink("in").c_str())<<","<<","<<mc->AskForDrink("comment")<<endl;
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
	
	string formStr = ml->GetAmmo();
	for(int i=0;i<formStr.size();i++)
		cout<<formStr[i];
	hm->body();
	hm->html();
}
#endif

