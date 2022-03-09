#pragma once
#include <iostream>

//环形buffer
//当一个数据元素被用掉后，其余数据元素不需要移动其存储位置。
//自动扩容，空余大于initsize时，自动收缩

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

