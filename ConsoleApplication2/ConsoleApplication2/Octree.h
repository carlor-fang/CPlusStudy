
#pragma once
#include <iostream>
#include <vector>

const int CHILDREN_COUNT = 8;

class Vec3
{
public:
    float x;
    float y;
    float z;

    Vec3();
    Vec3(float inX, float inY, float inZ);
    Vec3(const Vec3& vec3);
    ~Vec3();

    void operator=(const Vec3& value);
    Vec3 operator/(int value) const;
    Vec3 operator-(const Vec3& value) const;
    Vec3 operator+(const Vec3& value) const;
};

class OctreePoint
{
private:
    Vec3* p;
public:
    OctreePoint();
    OctreePoint(const Vec3& vec);
    ~OctreePoint();
    
    void setPosition(const Vec3& vec);
    Vec3* getPosition() const;
};

class OctreeNode
{
private:
    Vec3* minVec;
    Vec3* maxVec;
    OctreeNode* parent;
    OctreeNode* children[CHILDREN_COUNT];
    OctreePoint* point;
    bool hasChild;
public:
    OctreeNode(OctreeNode* nodeParent, const Vec3& min, const Vec3& max);
    bool divisionAndTranferPoint();
    void removePoint();
    void addPoint(const OctreePoint& p);
    void getPointInRange(const Vec3& minVec, const Vec3& maxVec, std::vector<OctreePoint*>& results);
    
    bool inRange(const OctreePoint& p);
    bool inRange(const Vec3& minVec, const Vec3& maxVec);
};

class Octree
{
public:
    Octree(const Vec3& origin, const Vec3& spaceSize);
    ~Octree();

    void insert(const OctreePoint& point);

    void getPointsInsideBox(const Vec3& minVec, const Vec3& maxVec, std::vector<OctreePoint*>& results);
private:
    OctreeNode* rootNode;
};