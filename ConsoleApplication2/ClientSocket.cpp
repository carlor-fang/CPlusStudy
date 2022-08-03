#include <winsock2.h>
#include <iphlpapi.h>   
#include <WS2tcpip.h>
#include <iostream>
#include <string>
#include <thread>
#include <WS2tcpip.h>

#define ClientPort 7000
#define MaxBufferSize 1024

void SendThread(int ClientSocket)
{
    char SendBuffer[MaxBufferSize];
    while (1)
    {
        fgets(SendBuffer, sizeof(SendBuffer), stdin);
        if (send(ClientSocket, SendBuffer, strlen(SendBuffer), 0) > 0)
        {
            std::cout << "client send success:" << SendBuffer << std::endl;
        }
        else
        {
            std::cout << "client received failed:" << WSAGetLastError() << std::endl;
            break;
        }
    }
}

void RecvThread(int ClientSocket)
{
    char RecvBuffer[MaxBufferSize];
    while (1)
    {
        memset(RecvBuffer, 0, MaxBufferSize);
        if (recv(ClientSocket, RecvBuffer, MaxBufferSize, 0) > 0)
        {
            std::cout << "client received success:" << RecvBuffer << std::endl;
        }
        else
        {
            std::cout << "client received failed:" << WSAGetLastError() << std::endl;
            break;
        }
    }
}

int client()
{
    WSADATA WsaData;
    if (WSAStartup(MAKEWORD(2, 2), &WsaData) != 0)
    {
        std::cout << "startup failed" << std::endl;

    }

    int ClientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    struct sockaddr_in ClientAddr;
    ClientAddr.sin_family = AF_INET;
    //ClientAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    ClientAddr.sin_port = htons(ClientPort);
    inet_pton(AF_INET, "127.0.0.1", &ClientAddr.sin_addr.s_addr);

    if (connect(ClientSocket, (struct sockaddr*)&ClientAddr, sizeof(ClientAddr)) < 0)
    {
        std::cout << "connect failed" << std::endl;
        std::cout << "Received failed:" << WSAGetLastError() << std::endl;
        closesocket(ClientSocket);
        WSACleanup();
        return -1;
    }

    std::thread SThread(SendThread, ClientSocket);
    std::thread RThread(RecvThread, ClientSocket);
    SThread.join();
    RThread.join();

    closesocket(ClientSocket);
    WSACleanup();
    return 0;
}
