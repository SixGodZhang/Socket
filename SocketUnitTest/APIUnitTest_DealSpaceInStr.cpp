#include "pch.h"
#include <iostream>
#include <string>

using namespace std;

//#define EXCUTE_CPP

#ifdef EXCUTE_CPP
int main()
{
	// noskipws、skipws 只是在流读取是考虑是否忽略空格，继续读取
	string str,str1;
	cin >> noskipws >> str >> str1;
	cout << str << " , " <<str1 << endl;
	return 0;
}

#endif