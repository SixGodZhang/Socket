// SocketUnitTest.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <Ws2tcpip.h>  //InetNtop 和InetPton 声明的文件

#pragma comment(lib,"Ws2_32.lib")

using namespace std;


#define EXCUTE_CPP
#ifdef EXCUTE_CPP

int main()
{
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	// 获取主机信息
	struct  hostent *host = gethostbyname("www.baidu.com");
	if (!host)
	{
		puts("Get IP address error!");
		system("pause");
		exit(0);
	}

	// 别名
	for (int i = 0; host->h_aliases[i]; i++)
	{
		cout << "Aliases  " << i + 1 << ": " << host->h_aliases[i] << endl;
	}

	// 地址类型
	const char* addressType = (host->h_addrtype == AF_INET) ? "AF_INET" : "AF_INET6";
	cout << "Address type: " << addressType << endl;

	// IP地址
	for (int i = 0; host->h_addr_list[i]; i++)
	{
		cout << "IP addr :" << inet_ntoa(*(struct in_addr*)host->h_addr_list[i]) << endl;
	}
}
#endif