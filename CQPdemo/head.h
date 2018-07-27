#pragma once

#include <cstring>
#include <cstdio>
#include <string>
#include <iostream>
#include <ctime>
#include "stdafx.h"
#include <fstream>

using namespace std;

string place;
int OWNER;

int infile(string a)
{
	ofstream file(place, ios_base::out | ios_base::app);
	//file.open(LOCATION);
	file << a << "\n";
	file.close();
	return 0;
}

string rands()
{
	char value[6];
	srand((unsigned)time(NULL));
	memset(value,0,sizeof(value));
	for (int i=0;i<6;i++) value[i] = (char)(rand() % 26 + 65);
	string va(value);
	return va;
}

string wrte(int type, string id)
{
	char a1[17],b[17];
	memset(a1,0,sizeof(a1));
	memset(b, 0, sizeof(b));
	string a(a1);
	string b1(b);
	a = a + rands();
	b1 = a;
	a = a.substr(0,6) + ": ";
	switch (type)
	{
		//type=0 Thing
	case 0:a = a.substr(0,8) + "give {player} " + id; infile(a); break;
		//type=1 Permassion
	case 1:break; //wait
	default:break; //wait
	}
	return b1.substr(0,6);
}
