#include "pch.h"
#include <iostream>
#include <string>

using namespace std;

//#define EXCUTE_CPP

#ifdef EXCUTE_CPP
int main()
{
	// noskipws��skipws ֻ��������ȡ�ǿ����Ƿ���Կո񣬼�����ȡ
	string str,str1;
	cin >> noskipws >> str >> str1;
	cout << str << " , " <<str1 << endl;
	return 0;
}

#endif