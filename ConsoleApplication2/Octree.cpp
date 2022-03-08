#include "Octree.h"

//Vec3::Vec3()
//    : x(0)
//    , y(0)
//    , z(0)
//{
//}
//
//Vec3::Vec3(float inX, float inY, float inZ)
//    : x(inX)
//    , y(inY)
//    , z(inZ)
//{
//}
//
//Vec3::Vec3(const Vec3& vec3)
//{
//    *this = vec3;
//}
//
//Vec3::~Vec3()
//{
//
//}
//
//void Vec3::operator=(const Vec3& value)
//{
//    x = value.x;
//    y = value.y;
//    z = value.z;
//}
//
//Vec3 Vec3::operator/(int value)
//{
//    return Vec3(x / value, y / value, z / value);
//}
//
//Vec3 Vec3::operator-(const Vec3& value)
//{
//    return Vec3(x - value.x, y - value.y, z - value.z);
//}
//
//Vec3 Vec3::operator+(const Vec3& value)
//{
//    return Vec3(x + value.x, y + value.y, z + value.z);
//}
//
//OctreePoint::OctreePoint()
//{
//    p = new Vec3();
//}
//
//OctreePoint::~OctreePoint()
//{
//
//}
//
//void OctreePoint::setPosition(const Vec3& vec)
//{
//    *p = vec;
//}
//
//OctreeNode::OctreeNode(OctreeNode* nodeParent, const Vec3& min, const Vec3& max)
//{
//    parent = nodeParent;
//    minVec = new Vec3(min);
//    maxVec = new Vec3(max);
//    for (int i = 0; i < children_count;i++) {
//        children[i] = nullptr;
//    }
//    hasChild = false;
//}
//
//void OctreeNode::division()
//{
//    hasChild = true;
//    
//    Vec3 size = (*maxVec - *minVec) / 2;
//    
//    children[0] = new OctreeNode(this, *minVec, Vec3(minVec->x + size.x, minVec->y + size.y, minVec->z + size.z));
//    children[1] = new OctreeNode(this, Vec3(minVec->x + size.x, minVec->y, minVec->z), Vec3(maxVec->x, minVec->y + size.y, minVec->z + size.z));
//    children[2] = new OctreeNode(this, Vec3(minVec->x, minVec->y, minVec->z + size.z), Vec3(minVec->x + size.x, minVec->y + size.y, maxVec->z));
//    children[3] = new OctreeNode(this, Vec3(minVec->x + size.x, minVec->y, minVec->z + size.z), Vec3(maxVec->x, minVec->y + size.y, maxVec->z));
//    //children[4] = new OctreeNode(this, Vec3(minVec->x + size.x, minVec->y, minVec->z + size.z), Vec3(maxVec->x, minVec->y + size.y, maxVec->z));
//}
//
//Octree::Octree(const Vec3& origin, const Vec3& spaceSize)
//{
//}
//
//void Octree::insert(const OctreePoint& point)
//{
//
//}
//
//void Octree::getPointsInsideBox(const Vec3& minVec, const Vec3& maxVec, std::vector<OctreePoint*>& results)
//{
//
//}