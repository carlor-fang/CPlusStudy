#include "RingBuffer.h"

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
    if (p) {
        bufferSize = size;
        memAddr = p;
        memset(memAddr, 0, sizeof(char) * (size));
        head = memAddr;
        tail = memAddr;
    }
}

void RingBuffer::resetBufferSize(int size)
{
    int mh = head - memAddr;
    int mt = tail - memAddr;

    char* p = (char*)realloc(memAddr, sizeof(char) * (size));
    if (p) {
        bufferSize = size;
        memAddr = p;

        head = memAddr;
        tail = memAddr + usedSize;
    }
}

void RingBuffer::push(const char* value)
{
    int addSize = strlen(value);
    if (usedSize + addSize > bufferSize) {
        resetBufferSize(bufferSize + addSize * 2);
    }

    usedSize += addSize;
    int index = 0;
    const char* temp = value;

    while (index < addSize)
    {
        pushChar(temp[index]);
        index++;
    }
}

void RingBuffer::pushChar(const char value)
{
    auto pushExc = [&]() {
        tail[0] = value;
        tail++;
    };
    if (tail > head) {
        // 还没有Ring
        if (memAddr + bufferSize >= tail + 1) {
            // push后也没有Ring
            pushExc();
        }
        else {
            // 开始Ring
            tail = memAddr;
            pushExc();
        }
    }
    else if (tail < head) {
        // 已经Ring
        if (tail + 1 == head) {
            std::cout << "over range 1" << std::endl;
        }
        else {
            pushExc();
        }
    }
    else {
        pushExc();
    }
}

void RingBuffer::pop(char* outValue, int size)
{
    if (size > usedSize) {
        size = usedSize;
    }
    usedSize -= size;

    int index = 0;
    while (index < size) {
        char temp = popChar();
        outValue[index] = temp;
        index++;
    }

    if (bufferSize - usedSize > DEFAULT_BUFFER_SIZE * 2) {
        resetBufferSize(usedSize + DEFAULT_BUFFER_SIZE);
    }
}

char RingBuffer::RingBuffer::popChar()
{
    char ret = head[0];
    head[0] = 0;

    if (head + 1 >= memAddr + bufferSize) {
        head = memAddr;
    }
    else {
        head++;
    }
    return ret;
}

void RingBuffer::print()
{
    std::cout << usedSize << std::endl;
    int count = 0;
    while (count < bufferSize) {
        if (memAddr[count]) {
            std::cout << memAddr[count];
        }
        else {
            std::cout << 0;
        }
        count++;
    }

    std::cout << "" << std::endl;
}