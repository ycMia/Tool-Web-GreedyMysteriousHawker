#include <iostream>

#include "WebPainting.h"
#include "CsvReader.h"

using namespace std;

int main(int argc, char *args[])
{
	Html_Machine * hm = new Html_Machine();
	hm->initPage();
	hm->html();
	
	hm->head();
	hm->head();
	
	hm->body();
	
	Table_Solid_Printer * tsp = new Table_Solid_Printer();
	tsp->table();
	
	CSV_reader * cr = new CSV_reader();
	
	// tsp->tr();
	// tsp->td();cout<<"r1d1";tsp->td();
	// tsp->td();cout<<"r1d2";tsp->td();
	// tsp->tr();
	
	// tsp->tr();
	// tsp->td();cout<<"r2d1";tsp->td();
	// tsp->td();cout<<"r2d2";tsp->td();
	// tsp->tr();
	
	// tsp->tr();
	// tsp->td();cout<<cr->Out_fileSize();tsp->td();
	// tsp->td();cout<<"r2d2";tsp->td();
	// tsp->tr();
	
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
	
	tsp->table();
	
	hm->body();
	
	hm->html();
#ifdef DEBUG
	system("pause");
#endif
	return 0;
}
