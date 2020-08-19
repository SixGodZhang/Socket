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
	char bufSend[BUF_SIZE] = { 0 };// 文件名
	char bufRecv[MAXBYTE] = { 0 };
	int nCount; // 如果socket 输入缓冲区内容读取完毕, 此值为0

	while (1)
	{
		// 创建套接字
		SOCKET sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
		// 与服务器建立连接
		connect(sock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));

		cout << "Input a filename that u want to download from server: " << endl;
		gets_s(bufSend);
		cout << "发送服务端的数据: " << bufSend << endl;
		send(sock, bufSend, strlen(bufSend), 0);

		FILE *fp = fopen(bufSend, "wb");// 以二进制方式打开(创建)文件
		if (fp == NULL)
		{
			cout << "Can't createFile, press key to exit!" << endl;
			closesocket(sock);
			WSACleanup();
			system("pause");
			exit(0);
		}

		while ((nCount = recv(sock, bufRecv, BUF_SIZE, 0)) > 0) {

			fwrite(bufRecv, nCount, 1, fp);
		}

		cout << "file download complete. please check!" << endl;

		// 关闭文件句柄
		fclose(fp);
		// 关闭套接字
		closesocket(sock);
	}

	// 终止使用DLL
	WSACleanup();

	system("pause");
	return 0;
}
