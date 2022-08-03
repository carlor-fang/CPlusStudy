// ConsoleApplication2.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include<string>
#include<math.h>
#include <set>
#include "Test.h"

using namespace std;

int main(int argc, char* argv[])
{
    TestSocket(argc, argv);
}

////#include <sys/types.h>
////#include <sys/socket.h>
////#include <stdio.h>
//#include <iostream>
////#include <netinet/in.h>
////#include <arpa/inet.h>//
////#include <unistd.h>
//#include <string.h>
//#include <stdlib.h>
////#include <fcntl.h>//
////#include <sys/shm.h>//
//#include <thread>
//#include <winsock2.h>
//#include<ws2tcpip.h>
//#define PORT 7000
//#define QUEUE 20//连接请求队列
//#pragma comment(lib,"ws2_32.lib")
//
//int ConnectId;
//void thread_task(int SocketId)
//{
//    char Buffer[1024];
//    //std::cout<<sizeof(buffer);
//    //printf("%s", sizeof(buffer));
//    while (1) {
//        memset(Buffer, 0, sizeof(Buffer));
//        int Len = recv(ConnectId, Buffer, sizeof(Buffer), 0);//从TCP连接的另一端接收数据。
//
//        if (strcmp(Buffer, "exit\n") == 0)//如果没有收到TCP另一端发来的数据则跳出循环不输出
//        {
//            closesocket(ConnectId);//因为accpet函数连接成功后还会生成一个新的套接字描述符，结束后也需要关闭
//            closesocket(SocketId);//关闭socket套接字描述符
//            break;
//
//        }
//        printf("len = %d  rec = %s", Len, Buffer);//如果有收到数据则输出数据
//        //必须要有返回数据， 这样才算一个完整的请求
//        send(ConnectId, Buffer, Len, 0);//向TCP连接的另一端发送数据。
//    }
//
//
//}
//
//int main()
//{
//    printf("server start waiting connection\n");//如果有收到数据则输出数据
//    int SockerId = socket(AF_INET, SOCK_STREAM, 0); // 若成功则返回一个sockfd（套接字描述符）
//    struct sockaddr_in Sockaddr; // 一般是储存地址和端口的。用于信息的显示及存储使用
//    Sockaddr.sin_family = AF_INET;
//    Sockaddr.sin_port = htons(PORT); // 将一个无符号短整型数值转换为网络字节序，即大端模式(big-endian)
//    Sockaddr.sin_addr.s_addr = htonl(INADDR_ANY); // 将主机的无符号长整形数转换成网络字节顺序。
//
//    if (bind(SockerId, (struct sockaddr*)&Sockaddr, sizeof(Sockaddr)) == -1)
//    {
//        closesocket(SockerId);//关闭socket套接字描述符
//        printf("bind %d", WSAGetLastError());
//        exit(1);
//    }
//
//    if (listen(SockerId, QUEUE) == -1)
//    {
//        perror("listen");
//        exit(1);
//    }
//
//    struct sockaddr_in client_addr;
//    socklen_t length = sizeof(client_addr);
//
//    ConnectId = accept(SockerId, (struct sockaddr*)&client_addr, &length); // 成功返回非负描述字，出错返回-1
//    if (ConnectId < 0)
//    {
//        perror("connect");
//        exit(1);
//    }
//
//    //创建另外一个线程
//    std::thread Recive(thread_task, SockerId);
//    Recive.join();
//
//    return 0;
//}