// SocketUnitTest.cpp : ���ļ����� "main" ����������ִ�н��ڴ˴���ʼ��������
//

#include "pch.h"
#include <iostream>
#include <Ws2tcpip.h>  //InetNtop ��InetPton �������ļ�

#pragma comment(lib,"Ws2_32.lib")

using namespace std;


#define EXCUTE_CPP
#ifdef EXCUTE_CPP

int main()
{
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	// ��ȡ������Ϣ
	struct  hostent *host = gethostbyname("www.baidu.com");
	if (!host)
	{
		puts("Get IP address error!");
		system("pause");
		exit(0);
	}

	// ����
	for (int i = 0; host->h_aliases[i]; i++)
	{
		cout << "Aliases  " << i + 1 << ": " << host->h_aliases[i] << endl;
	}

	// ��ַ����
	const char* addressType = (host->h_addrtype == AF_INET) ? "AF_INET" : "AF_INET6";
	cout << "Address type: " << addressType << endl;

	// IP��ַ
	for (int i = 0; host->h_addr_list[i]; i++)
	{
		cout << "IP addr :" << inet_ntoa(*(struct in_addr*)host->h_addr_list[i]) << endl;
	}
}
#endif