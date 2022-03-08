
#pragma once
#include <vector>

//const int children_count = 8;
//
//class Vec3
//{
//public:
//    float x;
//    float y;
//    float z;
//
//    Vec3();
//    Vec3(float inX, float inY, float inZ);
//    Vec3(const Vec3& vec3);
//    ~Vec3();
//
//    void operator=(const Vec3& value);
//    Vec3 operator/(int value);
//    Vec3 operator-(const Vec3& value);
//    Vec3 operator+(const Vec3& value);
//};
//
//class OctreePoint
//{
//private:
//    Vec3* p;
//public:
//    OctreePoint();
//
//    void setPosition(const Vec3& vec);
//};
//
//class OctreeNode
//{
//private:
//    Vec3* minVec;
//    Vec3* maxVec;
//    OctreeNode* parent;
//    OctreeNode* children[children_count];
//    bool hasChild;
//public:
//    OctreeNode(OctreeNode* nodeParent, const Vec3& min, const Vec3& max);
//    void division();
//};
//
//class Octree
//{
//public:
//    Octree(const Vec3& origin, const Vec3& spaceSize);
//
//    void insert(const OctreePoint& point);
//
//    void getPointsInsideBox(const Vec3& minVec, const Vec3& maxVec, std::vector<OctreePoint*>& results);
//};