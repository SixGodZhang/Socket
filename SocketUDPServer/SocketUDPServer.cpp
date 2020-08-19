// SocketUDPServer.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>
#pragma comment (lib, "ws2_32.lib") // 加载 ws2_32.dll

using namespace std;
#define BUF_SIZE 100

int main()
{
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	// 创建套接字
	SOCKET sock = socket(AF_INET, SOCK_DGRAM, 0);

	// 绑定套接字
	sockaddr_in servAddr;
	memset(&servAddr, 0, sizeof(servAddr));//每个字节都用0填充
	servAddr.sin_family = PF_INET;// 使用IPv4地址
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY); // 自动获取IP地址
	servAddr.sin_port = htons(1234);// 端口
	bind(sock, (SOCKADDR*)&servAddr, sizeof(SOCKADDR));

	//接受客户端请求
	SOCKADDR clntAddr;// 客户端地址信息
	int nSize = sizeof(SOCKADDR);
	char buffer[BUF_SIZE] = {0};//缓冲区

	while (1) {
		int strlen = recvfrom(sock, buffer, BUF_SIZE, 0, &clntAddr, &nSize);

		cout << "-------> receive msg begin<------" << endl;
		WCHAR ip[16] = TEXT("0");
		InetNtop(PF_INET, &((SOCKADDR_IN*)&clntAddr)->sin_addr.S_un.S_addr, ip, 100);
		wcout << "客户端地址: " << ip << endl; // 端口： 因为ip是宽字符， 所以这里需要用wcout进行输出
		// 客户端向服务器的某个端口发送消息, 从客户端的哪个端口出来并不重要
		cout << "客户端端口: " << ntohs(((SOCKADDR_IN*)&clntAddr)->sin_port) << endl;//????
		// cout << "客户端消息长度:" << clntMsglen << endl;
		cout << "客户端消息: " << buffer << endl;
		cout << "------> receive msg end<------" << endl;

		sendto(sock, buffer, strlen, 0, &clntAddr, nSize);
	}

	closesocket(sock);
	WSACleanup();
	return 0;
}