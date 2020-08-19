// SocketClient.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <stdio.h>
#pragma comment(lib, "ws2_32.lib")
using namespace std;

#define BUF_SIZE 100

int main()
{
	// 初始化DLL
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	// 向服务器发起请求 <---- 这个可以放在while外面, 因为每次请求都是一样的
	sockaddr_in sockAddr;
	PCWSTR addrStr = TEXT("127.0.0.1");//服务端地址
	memset(&sockAddr, 0, sizeof(sockAddr)); // 每个字节都用0填充
	sockAddr.sin_family = PF_INET;
	InetPton(PF_INET, addrStr, &sockAddr.sin_addr);
	sockAddr.sin_port = htons(1234);// 服务端监听的端口

	// 获取用户的输入字符串并发送给服务端
	char bufSend[BUF_SIZE] = { 0 };
	char bufRecv[MAXBYTE] = { 0 };

	while (1)
	{
		// 创建套接字
		SOCKET sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
		// 与服务器建立连接
		connect(sock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));

		cout << "Input a string: " << endl;
		gets_s(bufSend);
		cout << "发送服务端的数据: " << bufSend << endl;
		send(sock, bufSend, strlen(bufSend), 0);
		// 接收服务器传回的数据
		recv(sock, bufRecv, MAXBYTE, NULL);
		// 输出接收到的数据
		cout << bufRecv << endl;
		// 关闭套接字
		closesocket(sock);
	}

	// 终止使用DLL
	WSACleanup();

	system("pause");
	return 0;
}
