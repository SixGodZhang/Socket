// SocketUnitTest.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <Ws2tcpip.h>  //InetNtop 和InetPton 声明的文件

#pragma comment(lib,"Ws2_32.lib")

using namespace std;

#ifdef EXCUTE_CPP

int main()
{
	//int inet_pton(int af, const char *src, void *dst);
	PCWSTR src = TEXT("192.168.100.16");
	WCHAR ip[16] = TEXT("0");  //初始化是个好习惯
	struct in_addr dst;

	int i = 0;
	i = InetPton(AF_INET, src, &dst);
	if (1 == i)
	{
		cout << "addr is " << dst.S_un.S_addr << endl;
	}

	//const char *inet_ntop(int af, const void *src, char *dst, socklen_t cnt);
	if (InetNtop(AF_INET, &dst.S_un.S_addr, ip, 100) == NULL)
	{
		cout << "error" << endl;
		return -1;
	}
	wcout << ip << endl;	//宽字符记得用宽字符的方式进行输出
}
#endif