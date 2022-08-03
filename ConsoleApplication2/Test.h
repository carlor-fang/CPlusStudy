#pragma once
#include <iostream>
#include <map>

void TestCustomString();

class TestArray {
public:
    int a = 0;
    std::string b = "";
    TestArray() = default;
    TestArray(int av, std::string bv)
        : a(av)
        , b(bv) {

    };
    TestArray(const TestArray& ta) = default;

    bool operator==(TestArray& ta) const {
        return this->a == ta.a && this->b == ta.b;
    }
};
void TestCustomArray();

void TestCustomList();

void TestRingBuffer();

void TestStackInfo();

void TestOctree();

void TestSkipList();

void TestJson();

void TestCommander(int argc, char* argv[]);

void TestPosManager();

void TestSocket(int argc, char* argv[]);

void TestBinder();