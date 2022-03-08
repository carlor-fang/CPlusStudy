// ConsoleApplication2.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <vector>
#include <cstdlib>
#include <cstdio>
#include <algorithm>
#include "Test.h"
#include "Octree.h"

//// Used for testing
//std::vector<Vec3> points;
//Octree* octree;
//OctreePoint* octreePoints;
//Vec3 qmin, qmax;
//
//float rand11() // Random number between [-1,1]
//{
//    return -1.f + (2.f * rand()) * (1.f / RAND_MAX);
//}
//
//Vec3 randVec3() // Random vector with components in the range [-1,1]
//{
//    return Vec3(rand11(), rand11(), rand11());
//}
//
//// Determine if 'point' is within the bounding box [bmin, bmax]
//bool naivePointInBox(const Vec3& point, const Vec3& bmin, const Vec3& bmax) {
//    return
//        point.x >= bmin.x &&
//        point.y >= bmin.y &&
//        point.z >= bmin.z &&
//        point.x <= bmax.x &&
//        point.y <= bmax.y &&
//        point.z <= bmax.z;
//}
//
//void init() {
//    // Create a new Octree centered at the origin
//    // with physical dimension 2x2x2
//    octree = new Octree(Vec3(0, 0, 0), Vec3(1, 1, 1));
//
//    // Create a bunch of random points
//    const int nPoints = 1 * 1000 * 1000;
//    for (int i = 0; i < nPoints; ++i) {
//        points.push_back(randVec3());
//    }
//    printf("Created %ld points\n", points.size()); fflush(stdout);
//
//    // Insert the points into the octree
//    octreePoints = new OctreePoint[nPoints];
//    for (int i = 0; i < nPoints; ++i) {
//        octreePoints[i].setPosition(points[i]);
//        octree->insert(octreePoints + i);
//    }
//    printf("Inserted points to octree\n"); fflush(stdout);
//
//    // Create a very small query box. The smaller this box is
//    // the less work the octree will need to do. This may seem
//    // like it is exagerating the benefits, but often, we only
//    // need to know very nearby objects.
//    qmin = Vec3(-.05, -.05, -.05);
//    qmax = Vec3(.05, .05, .05);
//
//    // Remember: In the case where the query is relatively close
//    // to the size of the whole octree space, the octree will
//    // actually be a good bit slower than brute forcing every point!
//}
//
//// Query using brute-force
//void testNaive() {
//    //double start = stopwatch();
//
//    std::vector<int> results;
//    for (int i = 0; i < points.size(); ++i) {
//        if (naivePointInBox(points[i], qmin, qmax)) {
//            results.push_back(i);
//        }
//    }
//
//    //double T = stopwatch() - start;
//    //printf("testNaive found %ld points in %.5f sec.\n", results.size(), T);
//}
//
//// Query using Octree
//void testOctree() {
//    //double start = stopwatch();
//
//    std::vector<OctreePoint*> results;
//    octree->getPointsInsideBox(qmin, qmax, results);
//
//    //double T = stopwatch() - start;
//    //printf("testOctree found %ld points in %.5f sec.\n", results.size(), T);
//}

int main()
{
    testCustomString();
    testCustomArray();
    testCustomList();
    testRingBuffer();
    testStackInfo();
    //init();
    //testNaive();
    //testOctree();

    return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
