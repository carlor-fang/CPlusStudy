#include "Test.h"
#include "CustomString.h"
#include "CustomArray.h"
#include "CustomArray.cpp"
#include "CustomList.h"
#include "CustomList.cpp"
#include "RingBuffer.h"
#include "CustomStack.h"


// 实现string以下api，内部不能使用string，只能用数组存字符
void testCustomString()
{
    auto str1 = CustomString("test1fdsdfdd");
    auto str2 = CustomString("test2, test3,fsdfdsad,fdsfdssrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrr");
    str1 = "test38888888888888888888888888888888";
    str1.print();
    int len = str1.len();
    CustomString sub1 = str1.sub(1, 2);
    str1.append("append");
    str1.print();
    bool equal = str1 == str2;
    int index = str1.find("es");
    CustomString* ret = str2.split(",");
}

void testCustomArray()
{
    auto arr = new CustomArray<int>();
    arr->reserve(4);
    arr->push(1);
    arr->print();
    arr->push(2);
    arr->print();
    arr->push(6);
    arr->print();
    arr->push(7);
    arr->print();
    arr->push(8);
    arr->print();
    arr->insert(1, 3);
    arr->print();
    arr->remove(1);
    arr->print();
    arr->pop();
    arr->print();
    int index = arr->findIndex(1);
    arr->clear();
    
    auto aa = new CustomArray<TestArray>();
    aa->reserve(4);
    auto ab = new TestArray(1, "11111");
    aa->push(*ab);
    aa->print();
    aa->push(TestArray(2, "22222"));
    aa->print();
    aa->push(TestArray(6, "66666666"));
    aa->print();
    aa->push(TestArray(7, "77777777777777777777777"));
    aa->print();
    aa->push(TestArray(8, "88888"));
    aa->print();
    aa->insert(1, TestArray(3, "33333"));
    aa->remove(1);
    //aa->pop();
    int index1 = aa->findIndex(*ab);
    aa->clear();
}

//实现双向链表以下api
void testCustomList()
{
    auto list1 = new CustomList<int>();
    auto node1 = list1->push(1);
    auto node2 = list1->push(2);
    auto node3 = list1->insert(node2, 3);
    auto ret = list1->find(2);
    list1->remove(node2);
    list1->popAll();

    auto list2 = new CustomList<TestArray>();
    auto a = new TestArray(1, "1111111");
    auto node21 = list2->push(*a);
    auto node22 = list2->push(TestArray(2, "2222222222"));
    auto node23 = list2->insert(node22, TestArray(3, "3333333333"));

    auto ret1 = list2->find(*a);
    list2->remove(node22);
    list2->popAll();
}

void testRingBuffer()
{
    int initSize = 256;
    const char* data = "123456789";
    auto buffer = new RingBuffer(initSize);
    srand(time(NULL));

    for (int ii = 0; ii < 1000; ii++)
    {
        //std::cout << "start";
        //std::cout << ii << std::endl;
        int pushCount = rand() % 10;
        for (int jj = 0; jj < pushCount; jj++) {
            buffer->push(data);    // 要支持自动扩容
        }
        //buffer->print();
        char out[128] = { 0 };
        int popCount = rand() % 10;
        for (int jj = 0; jj < popCount; jj++) {
            buffer->pop(&out[0], sizeof(out));   // 要支持自动缩容
        }
        /*std::cout << "pop:";
        std::cout << popCount << std::endl;*/
        //buffer->print();
    }
}

class TestStack
{
public:
    int p1 = 1;
    bool p2 = false;
    std::string p3 = "p33333333";

    void testWithStack(CustomStack& stack)
    {
        int v1 = 0;
        std::string v2;
        TestStack v3;
        TestStack* v4 = nullptr;

        stack.pop(v1);
        stack.pop(v2);
        stack.pop(v3);
        stack.pop<TestStack*>(v4);

        std::cout << "testWithStack "
            << v1 << " "
            << v2 << " "
            << v3.p3 << " "
            << v4->p3 << std::endl;

        stack.push(1);
    }
};
void testStackInfo()
{
    TestStack t1;

    CustomStack stack;  // 实现此类，就俩模板函数，push和pop
    stack.push(111);
    stack.push<std::string>("asdfasdfasdf");

    TestStack t2;
    t2.p3 = "t2teststring";
    stack.push(t2);
    stack.push(&t1);

    t1.testWithStack(stack);

    int ret = 0;
    stack.pop(ret);
    std::cout << "testWithStack ret " << ret << std::endl;
}