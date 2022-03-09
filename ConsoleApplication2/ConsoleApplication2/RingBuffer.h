#pragma once
#include <iostream>

//����buffer
//��һ������Ԫ�ر��õ�����������Ԫ�ز���Ҫ�ƶ���洢λ�á�
//�Զ����ݣ��������initsizeʱ���Զ�����

const int DEFAULT_BUFFER_SIZE = 256;

class RingBuffer
{
private:
    void initBufferSize(int size);
    void resetBufferSize(int size);
    void pushChar(const char value);
    char popChar();
public:
    RingBuffer();
    RingBuffer(int size);
    ~RingBuffer();

    void push(const char* value);
    void pop(char* outValue, int size);

    void print();

private:
    int bufferSize;
    int usedSize;

    char* memAddr;
    char* head;
    char* tail;
};

