#include<iostream>
#include<fstream>

#include<cstring>
#include<cmath>

using namespace std;

int main(int argc, char *argv[])
{
	if(argc == 1)
	{
		cout<<"no input specified"<<endl;
		return 0;
	}
	
	cout<<argv[1]<<endl<<endl;
	
	if(argc==3 || argc==4)
	{
		if(strcmp(argv[1],"income")==0)
		{			
			cout<<"in";
			ofstream * pofs = new ofstream;
			pofs->open("default.csv", ios::out | ios::app);
			
			*pofs<<","<<atoi(argv[2]) // income recorded in the right
				<<(argc==4 ? "," : "")
				<<(argc==4 ? argv[3] : "")
				<<"\n";
			
			pofs->close();
			delete pofs;
		}
		else if(strcmp(argv[1],"disburse")==0)
		{			
			cout<<"in";
			ofstream * pofs = new ofstream;
			pofs->open("default.csv", ios::out | ios::app);
			
			*pofs<<atoi(argv[2])<<"," // disburse recorded in the left
				<<(argc==4 ? "," : "")
				<<(argc==4 ? argv[3] : "")
				<<"\n";
			
			pofs->close();
			delete pofs;
		}
		else 
		{
			cout<<"input wrong!"<<endl;
			return 0;
		}		
	}
	
	return 0;
}