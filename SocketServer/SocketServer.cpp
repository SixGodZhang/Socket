// SocketServer.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>

using namespace std;
#pragma comment (lib, "ws2_32.lib") // 定义这个仍然需要

// wsock32.dll 大小为19KB【System32】、16KB【SysWOW64】, 对应头文件winsock1.h
// ws2_32.dll 大小为425KB【System32】、大小 376KB【SysWOW64】, 对应头文件winsock2.h

#define BUF_SIZE 100

int main()
{
	/*
		typedef struct WSAData {
			WORD                    wVersion;// ws2_32.dll 建议我们使用的版本号
			WORD                    wHighVersion;// ws2_32.dll 支持的最高版本号
			unsigned short          iMaxSockets;// 2.0 以后不再使用
			unsigned short          iMaxUdpDg;// 2.0 以后不再使用
			char FAR *              lpVendorInfo; // 2.0 以后不再使用
			// 一个以null结尾的字符串, 用来说明ws2_32.dll的实现及厂商信息
			char                    szDescription[WSADESCRIPTION_LEN + 1];
			// 一个以null结尾的字符串, 用来说明ws2_32.dll 的状态及配置信息
			char                    szSystemStatus[WSASYS_STATUS_LEN + 1];
		} WSADATA, FAR * LPWSADATA;
	*/

	// 初始化 DLL
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);// 指定socket的实现版本, 并返回其它一些细节

	// 打印套接字(Socket)的一些细节
	cout << "wVersion: " << int(LOBYTE(wsaData.wVersion)) << "," << int(HIBYTE(wsaData.wVersion)) << endl;
	cout << "wHighVersion: " << int(LOBYTE(wsaData.wHighVersion)) << "," << int(HIBYTE(wsaData.wHighVersion)) << endl;
	cout << wsaData.szDescription << endl;
	cout << wsaData.szSystemStatus << endl;


	/*
	SOCKET
	WSAAPI
	socket(
		_In_ int af, // IP地址类型 常用的有AF_INET、AF_INET6, 分别带一熬IPv4地址和IPv6地址
		_In_ int type,// 传输方式: SOCK_STREAM【面向流】, SOCK_DGRAM【面向数据报】
		_In_ int protocol // 传输协议, 常用的有IPPROTO_TCP、IPPROTO_UDP， 分别代表TCP、UDP
		);
	*/
	// 创建套接字
	SOCKET servSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	/*
	//
	// IPv4 Socket address, Internet style
	//

	typedef struct sockaddr_in {

		ADDRESS_FAMILY sin_family;// 地址族(Address Family), 也就是地址类型
		USHORT sin_port; // 16位的端口号
		IN_ADDR sin_addr; // 32位的IP地址
		CHAR sin_zero[8];// 不使用, 一般用0填充
	} SOCKADDR_IN, *PSOCKADDR_IN;
	*/

	// 绑定套接字
	sockaddr_in sockAddr;
	PCWSTR addrStr = TEXT("127.0.0.1");// 服务端地址
	memset(&sockAddr, 0, sizeof(sockAddr));// 每个字节都用0填充
	sockAddr.sin_family = PF_INET; // 使用IPv4地址
	InetPton(PF_INET, addrStr, &sockAddr.sin_addr);// 具体的IP地址
	sockAddr.sin_port = htons(1234);// 服务端监听的端口
	//cout << "端口: " << ntohs(sockAddr.sin_port) << endl;
	bind(servSock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));

	// 进入监听状态
	listen(servSock, 20);//SOMAXCONN

	// 接收客户端请求
	SOCKADDR clntAddr;
	int nSize = sizeof(SOCKADDR);
	while (1)
	{
		SOCKET clntSock = accept(servSock, (SOCKADDR*)&clntAddr, &nSize);

		// 例子2: 回声服务端实现
		char buffer[BUF_SIZE] = { 0 }; // 缓冲区 <---- 这里记得初始化, 否则输出字符串时，会带一堆乱码
		int clntMsglen = recv(clntSock, buffer, BUF_SIZE, 0);//  接受客户端发来的数据
		cout << "-------> receive msg begin<------" << endl;
		WCHAR ip[16] = TEXT("0");
		InetNtop(PF_INET, &((SOCKADDR_IN*)&clntAddr)->sin_addr.S_un.S_addr, ip, 100);
		wcout << "客户端地址: " << ip << endl; // 端口： 因为ip是宽字符， 所以这里需要用wcout进行输出
		// 客户端向服务器的某个端口发送消息, 从客户端的哪个端口出来并不重要
		cout << "客户端端口: " << ntohs(((SOCKADDR_IN*)&clntAddr)->sin_port) << endl;//????
		// cout << "客户端消息长度:" << clntMsglen << endl;
		cout << "客户端消息: " << buffer << endl;
		cout << "------> receive msg end<------" << endl;
		send(clntSock, buffer, clntMsglen, 0);// 将数据原样返回


		// 例子1： 向客户端发送数据
		//const char *str = "Hello World!";
		//send(clntSock, str, strlen(str) + sizeof(char), NULL);

		closesocket(clntSock);
	}


	// 关闭套接字
	closesocket(servSock);

	// 终止DLL的使用
	WSACleanup();

	system("pause");

	return 0;
}
