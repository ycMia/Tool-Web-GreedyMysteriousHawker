#include <iostream>
#define DEBUG

using namespace std;

int main(int argc, char *args[])
{
	cout<<"<!DOCTYPE html>"<<endl<<endl;
	
#ifdef DEBUG
	system("pause");
#endif
	return 0;
}
