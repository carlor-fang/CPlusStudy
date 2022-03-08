#pragma once
#include <iostream>
#include <map>

void testCustomString();

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
void testCustomArray();

void testCustomList();

void testRingBuffer();

void testStackInfo();