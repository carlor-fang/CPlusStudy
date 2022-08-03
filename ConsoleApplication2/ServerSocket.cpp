#include <WS2tcpip.h>
//﻿#include <winsock2.h>
#include <iostream>
#include <stdio.h>
#include <thread>
#include <vector>

#pragma comment(lib, "Ws2_32.lib")

#define ListenPort 7000
#define MaxBufferSize 1024
#define MaxCount 10

void ThreadServer(int ClientSocket)
{
    char RecvBuffer[MaxBufferSize];
    while (1)
    {
        memset(RecvBuffer, 0, MaxBufferSize);
        int recvSize = recv(ClientSocket, RecvBuffer, MaxBufferSize, 0);
        if (recvSize <= 0)
        {
            std::cout << "Received failed:" << WSAGetLastError() << std::endl;
            closesocket(ClientSocket);
            break;
        }

        if (send(ClientSocket, RecvBuffer, strlen(RecvBuffer) + 1, 0) > 0)
        {
            std::cout << "send success:" << RecvBuffer << std::endl;
        }
        else
        {
            closesocket(ClientSocket);
            break;
        }
    }
}


int server()
{
    WSADATA WsaData;
    if (WSAStartup(MAKEWORD(2, 2), &WsaData) != 0)
    {
        std::cout << "startup failed" << std::endl;

    }

    int ServerSocket = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in Sockaddr;
    Sockaddr.sin_family = AF_INET;
    Sockaddr.sin_port = htons(ListenPort);
    Sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    
    if (bind(ServerSocket, (struct sockaddr*)&Sockaddr, sizeof(Sockaddr)) == -1)
    {
        closesocket(ServerSocket);
        WSACleanup();
        return -1;
    }
    if (listen(ServerSocket, MaxCount) == -1)
    {
        closesocket(ServerSocket);
        WSACleanup();
        return -1;
    }

    while (true)
    {
        int ClientSocket = accept(ServerSocket, NULL, NULL); 
        if (ClientSocket == INVALID_SOCKET)
        {
            std::cout << "accept failed" << std::endl;
            closesocket(ServerSocket);
            WSACleanup();
            return -1;
        }

        std::thread Thread(ThreadServer, ClientSocket);
        Thread.detach();
    }


    closesocket(ServerSocket);
    WSACleanup();

    return 0;
}
