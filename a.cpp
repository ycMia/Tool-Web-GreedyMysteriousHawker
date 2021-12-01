#include <stdlib.h>
#include <iostream>
#include <unistd.h>

#include "MilkCar.h"
using namespace std;

int main()
{
    cout<<"Content-type:text/html\n\n";
    cout<<"<!DOCTYPE html>\n\n<html><body>"<<endl;
	MilkCar * mc = new MilkCar();
	mc->Show_map(mc->Milk_POST());
    cout<<"</body></html>"<<endl;
	return 0;
}



