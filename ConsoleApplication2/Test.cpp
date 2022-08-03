#include "Test.h"
#include "CustomString.h"
#include "CustomArray.h"
#include "CustomArray.cpp"
#include "CustomList.h"
#include "CustomList.cpp"
#include "RingBuffer.h"
#include "CustomStack.h"
#include <vector>
#include "Octree.h"
#include "SkipList.h"
#include "JsonExample.h"
#include "CommandTest.hpp"
#include "PosManager.h"
#include "Binder.h"
#include "ClientSocket.h"
#include "ServerSocket.h"

// 实现string以下api，内部不能使用string，只能用数组存字符
void TestCustomString()
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

void TestCustomArray()
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
void TestCustomList()
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

void TestRingBuffer()
{
    int initSize = 10;
    const char* data = "0123456789";
    auto buffer = new RingBuffer(initSize);
    srand(time(NULL));

    for (int ii = 0; ii < 1000; ii++)
    {
        //std::cout << ii << std::endl;
        int pushCount = rand() % 10;;
        std::cout << "push:";
        std::cout << pushCount * 10;
        std::cout << "" << std::endl;
        for (int jj = 0; jj < pushCount; jj++) {
            buffer->push(data);    // 要支持自动扩容
        }
        //buffer->print();
        char out[11] = { 0 };
        int popCount = rand() % 10;
        std::cout << "pop:";
        std::cout << popCount * 8;
        std::cout << "" << std::endl;
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
void TestStackInfo()
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



/*
* octree test
*/
std::vector<Vec3> points;
Octree* octree;
OctreePoint* octreePoints;
Vec3 qmin, qmax;

float rand11() // Random number between [-1,1]
{
    return -1.f + (2.f * rand()) * (1.f / RAND_MAX);
}

Vec3 randVec3() // Random vector with components in the range [-1,1]
{
    return Vec3(rand11(), rand11(), rand11());
}

// Determine if 'point' is within the bounding box [bmin, bmax]
bool naivePointInBox(const Vec3& point, const Vec3& bmin, const Vec3& bmax) {
    return
        point.x >= bmin.x &&
        point.y >= bmin.y &&
        point.z >= bmin.z &&
        point.x <= bmax.x &&
        point.y <= bmax.y &&
        point.z <= bmax.z;
}

#include <windows.h>
double stopwatch()
{
    unsigned long long ticks;
    unsigned long long ticks_per_sec;
    QueryPerformanceFrequency((LARGE_INTEGER*)&ticks_per_sec);
    QueryPerformanceCounter((LARGE_INTEGER*)&ticks);
    return ((float)ticks) / (float)ticks_per_sec;
}

// Query using Octree
void TestOctree() {

    /*
    * init
    */ 
    octree = new Octree(Vec3(0, 0, 0), Vec3(1, 1, 1));

    // Create a bunch of random points
    const int nPoints = 1 * 1000 * 1000;
    for (int i = 0; i < nPoints; ++i) {
        points.push_back(randVec3());
    }
    printf("Created %ld points\n", points.size()); fflush(stdout);

    // Insert the points into the octree
    octreePoints = new OctreePoint[nPoints];
    for (int i = 0; i < nPoints; ++i) {
        octreePoints[i].setPosition(points[i]);
        //std::cout << points[i].x;
        //std::cout << ",";
        //std::cout << points[i].y;
        //std::cout << ",";
        //std::cout << points[i].z << std::endl;
        octree->insert(octreePoints[i]);
    }
    printf("Inserted points to octree\n"); fflush(stdout);

    // Create a very small query box. The smaller this box is
    // the less work the octree will need to do. This may seem
    // like it is exagerating the benefits, but often, we only
    // need to know very nearby objects.
    qmin = Vec3(-.05, -.05, -.05);
    qmax = Vec3(.05, .05, .05);

    // Remember: In the case where the query is relatively close
    // to the size of the whole octree space, the octree will
    // actually be a good bit slower than brute forcing every point!




    double start1 = stopwatch();
    std::vector<int> results;
    for (int i = 0; i < points.size(); ++i) {
        if (naivePointInBox(points[i], qmin, qmax)) {
            results.push_back(i);
        }
    }
    double T1 = stopwatch() - start1;
    printf("testNaive found %ld points in %.5f sec.\n", results.size(), T1);


    // 
    double start2 = stopwatch();
    std::vector<OctreePoint*> results2;
    octree->getPointsInsideBox(qmin, qmax, results2);
    double T2 = stopwatch() - start2;
    printf("testOctree found %ld points in %.5f sec.\n", results.size(), T2);
}

void TestSkipList()
{
    //输入
    //    ["Skiplist", "add", "add", "add", "search", "add", "search", "erase", "erase", "search"]
    //[[], [1], [2], [3], [0], [4], [1], [0], [1], [1]]
    //输出
    //    [null, null, null, null, false, null, true, false, true, false]

    int count = 100;
    std::vector<int> test;
    SkipList skiplist = SkipList();
    for (int i = 0; i < count; i++) {
        int value = rand() % count;
        skiplist.add(value);
        test.push_back(value);
        std::cout << "add:";
        std::cout << value << std::endl;;

    }

    //for (int i = test.size() - 1; i >= 0; i--)
    //{
    //    bool finded = skiplist.erase(test[i]);
    //    std::cout << "find:";
    //    std::cout << finded << std::endl;
    //}


    std::cout << "ddd";
}

void TestJson()
{
    example1();
    example2();
    example3();
    example4();
}

void TestCommander(int argc, char* argv[])
{
    CommandTest(argc, argv);
}

void TestPosManager()
{
    auto m = new PosManager();
    int blockSize = 100;
    int mapSize = 10000;
    m->Init(blockSize, mapSize);

    int poseId1 = 1;
    int poseId2 = 2;
    m->Add(poseId1, 100, 200);  // 100是横坐标，200纵坐标
    m->Add(poseId2, 200, 300);
    m->Add(3, 0, 110);
    m->Add(4, 0, 210);
    m->Add(5, 0, 300);
    m->Add(6, 100, 300);
    std::vector<int> Ids;
    m->Find(poseId1, Ids);    // 找到poseid1脚下以及周围8格的所有id
    m->Update(poseId1, 300, 400);
    m->Find(poseId1, Ids);    // 找到poseid1脚下以及周围8格的所有id
    m->Remove(poseId2);
    m->Find(poseId1, Ids);
    delete m;
}

void TestSocket(int argc, char* argv[])
{
    if (argc > 1)
    {
        client();
    }
    else
    {
        server();
    }
}



void TestBinder()
{
    Binder<TestClassA> binder;
    binder.BindVar("p1", offsetof(TestClassA, p1));
    binder.BindVar("p2", offsetof(TestClassA, p2));
    binder.BindVar("p3", offsetof(TestClassA, p3));

    binder.BindFunc("Test1", &TestClassA::Test1);
    binder.BindStaticFunc("Test2", TestClassA::Test2);
    TestClassA t1;
    int* p1 = binder.FindVar<int>(&t1, "p1");
    bool* p2 = binder.FindVar<bool>(&t1, "p2");
    string* p3 = binder.FindVar<string>(&t1, "p3");
    std::cout << *p1 << std::endl;
    std::cout << *p2 << std::endl;
    std::cout << *p3 << std::endl;
    binder.CallFunc(&t1, "Test1", nullptr);
    binder.CallStaticFunc("Test2", nullptr);
}