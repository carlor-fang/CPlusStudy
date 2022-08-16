#include "RingBuffer.h"
#include <assert.h>

RingBuffer::RingBuffer()
{
    initBufferSize(DEFAULT_BUFFER_SIZE);
}

RingBuffer::RingBuffer(int size)
{
    initBufferSize(size);
}

RingBuffer::~RingBuffer()
{
    free(memAddr);
}

void RingBuffer::initBufferSize(int size)
{
    char* p = (char*)malloc(sizeof(char) * (size));
    assert(p);
    bufferSize = size;
    memAddr = p;
    memset(memAddr, 0, sizeof(char) * (size));
    head = memAddr;
    tail = memAddr;
}

void RingBuffer::resetBufferSize(int size)
{
    char* p;
    if (usedSize > 0) 
    {
        p = (char*)malloc(sizeof(char) * (size));
        assert(p);
        if (tail > head)
        {
            memcpy(p, head, tail - head);
        }
        else
        {
            memcpy(p, head, memAddr + bufferSize - head);
            memcpy(p + (memAddr + bufferSize - head), memAddr, tail - memAddr);
        }
        free(memAddr);
    }
    else
    {
        p = (char*)realloc(memAddr, sizeof(char) * (size));
        assert(p);
    }
    bufferSize = size;
    memAddr = p;
    head = memAddr;
    tail = memAddr + usedSize;

    //if (usedSize > 0)
    //{
    //    if (tail < head)
    //    {
    //        char* p = (char*)malloc(sizeof(char) * (tail - memAddr));
    //        assert(p);
    //        memcpy(p, memAddr, (tail - memAddr));
    //        memmove(memAddr, head, memAddr + bufferSize - head);
    //        memmove(memAddr + (memAddr + bufferSize - head), p, (tail - memAddr));
    //        head = memAddr;
    //        tail = memAddr + usedSize;
    //        delete p;
    //        p = nullptr;
    //    }
    //    else
    //    {
    //        memmove(memAddr, head, usedSize);
    //    }
    //}
    //char* p = (char*)realloc(memAddr, sizeof(char) * (size));
    //assert(p);
    //bufferSize = size;
    //memAddr = p;

    //head = memAddr;
    //tail = memAddr + usedSize;
}

void RingBuffer::push(const char* value)
{
    int addSize = strlen(value);
    if (usedSize + addSize > bufferSize) {
        resetBufferSize(bufferSize + addSize * 2);
    }

    usedSize += addSize;

    if (tail < head || memAddr + bufferSize >= tail + addSize)
    {
        memcpy(tail, value, addSize);
        tail += addSize;
    }
    else
    {
        memcpy(tail, value, memAddr + bufferSize - tail);
        char* temp = const_cast<char*>(&value[memAddr + bufferSize - tail]);
        int lastSize = addSize - (memAddr + bufferSize - tail);
        tail = memAddr;
        memcpy(tail, temp, lastSize);
        tail = memAddr + lastSize;
    }
    print();
}

void RingBuffer::pop(char* outValue, int size)
{
    if (size > usedSize) {
        size = usedSize;
    }
    if (size <= 0)
    {
        return;
    }
    usedSize -= size;

    if (head + size <= memAddr + bufferSize)
    {
        memcpy(outValue, head, size);
        head += size;
    }
    else
    {
        memcpy(outValue, head, memAddr + bufferSize - head);
        int lastSize = size - (memAddr + bufferSize - head);
        memcpy(&outValue[memAddr + bufferSize - head], memAddr, lastSize);
        head = memAddr + lastSize;
    }
    
    if (bufferSize - usedSize > DEFAULT_BUFFER_SIZE * 2) 
    {
        resetBufferSize(usedSize + DEFAULT_BUFFER_SIZE);
    }
    print();
}

void RingBuffer::print()
{
    std::cout << usedSize << std::endl;
    int count = 0;
    while (count < bufferSize) {
        if (head < tail)
        {
            if (count < head - memAddr || count >= tail - memAddr)
            {
                std::cout << '#';
            }
            else
            {
                std::cout << memAddr[count];
            }
        }
        else if (head > tail)
        {
            if (count < tail - memAddr || count >= head - memAddr)
            {
                std::cout << memAddr[count];
            }
            else
            {
                std::cout << '#';
            }

        }
        else
        {
            if (usedSize > 0)
            {
                std::cout << memAddr[count];
            }
            else 
            {
                std::cout << '#';
            }
        }
        count++;
    }

    std::cout << "" << std::endl;
}