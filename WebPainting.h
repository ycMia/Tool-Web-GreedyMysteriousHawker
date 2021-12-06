#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <utility>
#include <iomanip>

//#define DEBUG

using namespace std;

class Html_Machine
{
public:
	Html_Machine() {}
	
	void initPage()
	{
		cout<<"Content-type:text/html"<<endl;
	}
	
	void head()
	{
		if(!_inHead)
			cout<<"<head>";
		else
			cout<<"</head>";
		_inHead = !_inHead;
		Liner();;
	}
	
	void body()
	{
		if(!_inBody)
			cout<<"<body>";
		else
			cout<<"</body>";
		_inBody = !_inBody;
		Liner();;
	}
	
	void html()
	{
		if(!_inHtml)
			cout<<"<html>";
		else
			cout<<"</html>";
		_inHtml = !_inHtml;
		Liner();;
	}
	
private:
	void Liner() { cout<<(_liner? "\n" : ""); }

	bool _inHead = false;
	bool _inBody = false;
	bool _inHtml = false;
	
	bool _liner = true;
};

class Table_Solid_Printer
{
public:
	
	void table()
	{
		if(!_inTable)
			cout<<"<table border=\"1\">";
		else
			cout<<"</table>";
		_inTable = !_inTable;
		Liner();
	}

	void th()
	{
		if(!_inTh)
			cout<<"<th>";
		else
			cout<<"</th>";
		_inTh = !_inTh;
		Liner();
	}
	
	void tr()
	{
		if(!_inTr)
			cout<<"<tr>";
		else
			cout<<"</tr>";
		_inTr = !_inTr;
		Liner();
	}
	
	void td()
	{
		if(!_inTd)
			cout<<"<td>";
		else
		{
			cout<<"</td>";
			Liner();
		}
		_inTd = !_inTd;
	}
	
private:
	void Liner() { cout<<(_liner? "\n" : ""); }

	bool _inTh = false;
	bool _inTr = false;
	bool _inTd = false;
	bool _inTable = false;
	
	bool _liner = true;
};
