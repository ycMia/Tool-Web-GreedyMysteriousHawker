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
		cout<<"Content-type:text/html"<<endl<<endl;
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
