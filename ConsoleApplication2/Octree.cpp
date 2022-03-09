#include "Octree.h"

Vec3::Vec3()
    : x(0)
    , y(0)
    , z(0)
{
}

Vec3::Vec3(float inX, float inY, float inZ)
    : x(inX)
    , y(inY)
    , z(inZ)
{
}

Vec3::Vec3(const Vec3& vec3)
{
    this->x = vec3.x;
    this->y = vec3.y;
    this->z = vec3.z;
}

Vec3::~Vec3()
{

}

void Vec3::operator=(const Vec3& value)
{
    x = value.x;
    y = value.y;
    z = value.z;
}

Vec3 Vec3::operator/(int value) const
{
    return Vec3(x / value, y / value, z / value);
}

Vec3 Vec3::operator-(const Vec3& value) const
{
    return Vec3(x - value.x, y - value.y, z - value.z);
}

Vec3 Vec3::operator+(const Vec3& value) const
{
    return Vec3(x + value.x, y + value.y, z + value.z);
}

OctreePoint::OctreePoint()
{
    p = new Vec3();
}

OctreePoint::OctreePoint(const Vec3& vec)
{
    p = new Vec3(vec.x, vec.y, vec.z);
}

OctreePoint::~OctreePoint()
{
    delete p;
}

void OctreePoint::setPosition(const Vec3& vec)
{
    p->x = vec.x;
    p->y = vec.y;
    p->z = vec.z;
}

Vec3* OctreePoint::getPosition() const
{
    return p;
}

OctreeNode::OctreeNode(OctreeNode* nodeParent, const Vec3& min, const Vec3& max)
{
    parent = nodeParent;
    minVec = new Vec3(min);
    maxVec = new Vec3(max);
    for (int i = 0; i < CHILDREN_COUNT; i++) {
        children[i] = nullptr;
    }
    hasChild = false;
}

bool OctreeNode::divisionAndTranferPoint()
{
    if (!point) {
        return false;
    }
    if (hasChild) {
        return true;
    }

    hasChild = true;
    Vec3 size = (*maxVec - *minVec) / 2;
    
    children[0] = new OctreeNode(this, *minVec, Vec3(minVec->x + size.x, minVec->y + size.y, minVec->z + size.z));
    children[1] = new OctreeNode(this, Vec3(minVec->x + size.x, minVec->y, minVec->z), Vec3(maxVec->x, minVec->y + size.y, minVec->z + size.z));
    children[2] = new OctreeNode(this, Vec3(minVec->x, minVec->y, minVec->z + size.z), Vec3(minVec->x + size.x, minVec->y + size.y, maxVec->z));
    children[3] = new OctreeNode(this, Vec3(minVec->x + size.x, minVec->y, minVec->z + size.z), Vec3(maxVec->x, minVec->y + size.y, maxVec->z));
    children[4] = new OctreeNode(this, Vec3(minVec->x, minVec->y + size.y, minVec->z), Vec3(minVec->x + size.x, maxVec->y, minVec->z + size.z));
    children[5] = new OctreeNode(this, Vec3(minVec->x + size.x, minVec->y + size.y, minVec->z), Vec3(maxVec->x, maxVec->y, minVec->z + size.z));
    children[6] = new OctreeNode(this, Vec3(minVec->x, minVec->y + size.y, minVec->z + size.z), Vec3(minVec->x + size.x, maxVec->y, maxVec->z));
    children[7] = new OctreeNode(this, Vec3(minVec->x + size.x, minVec->y + size.y, minVec->z + size.z), *maxVec);

    
    for (int i = 0; i < CHILDREN_COUNT; i++) {
        auto child = children[i];
        if (child->inRange(*point)) {
            child->addPoint(*point);
            removePoint();
            break;
        }
    }

    return hasChild;
}

bool OctreeNode::inRange(const OctreePoint& p)
{
    auto vec = p.getPosition();
    return vec->x >= minVec->x && vec->y >= minVec->y && vec->z >= minVec->z
        && vec->x < maxVec->x&& vec->y < maxVec->y&& vec->z < maxVec->z;
}

bool OctreeNode::inRange(const Vec3& minVec, const Vec3& maxVec)
{
    return this->maxVec->x > minVec.x&& this->minVec->x < maxVec.x
        && this->maxVec->y > minVec.y&& this->minVec->y < maxVec.y
        && this->maxVec->z > minVec.z&& this->minVec->z < maxVec.z
        && this->maxVec->x > minVec.x&& this->minVec->x < maxVec.x
        && this->maxVec->y > minVec.y&& this->minVec->y < maxVec.y
        && this->maxVec->z > minVec.z&& this->minVec->z < maxVec.z;
}

void OctreeNode::removePoint()
{
    delete point;
    point = nullptr;
}

void OctreeNode::addPoint(const OctreePoint& p)
{
    auto addPointToChild = [&]() {
        for (int i = 0; i < CHILDREN_COUNT; i++) {
            auto child = children[i];
            if (child->inRange(p)) {
                child->addPoint(p);
                break;
            }
        }
    };
    if (hasChild) {
        addPointToChild();
    }
    else {
        if (point) {
            divisionAndTranferPoint();
            addPointToChild();
        }
        else {
            point = new OctreePoint(*p.getPosition());
        }
    }
}

void OctreeNode::getPointInRange(const Vec3& minVec, const Vec3& maxVec, std::vector<OctreePoint*>& results)
{
    if (!inRange(minVec, maxVec)) {
        return;
    }

    if (hasChild) {
        for (int i = 0; i < CHILDREN_COUNT; i++) {
            auto child = children[i];
            child->getPointInRange(minVec, maxVec, results);
        }
    }
    else {
        if (point) {
            auto vec = point->getPosition();
            if (vec->x >= minVec.x &&
                vec->y >= minVec.y &&
                vec->z >= minVec.z &&
                vec->x <= maxVec.x &&
                vec->y <= maxVec.y &&
                vec->z <= maxVec.z) {
                results.push_back(point);
            }
        }
    }
}

Octree::Octree(const Vec3& origin, const Vec3& spaceSize)
{
    rootNode = new OctreeNode(nullptr, origin - spaceSize, origin + spaceSize);
}

Octree::~Octree()
{
    delete rootNode;
}

void Octree::insert(const OctreePoint& point)
{
    rootNode->addPoint(point);
}

void Octree::getPointsInsideBox(const Vec3& minVec, const Vec3& maxVec, std::vector<OctreePoint*>& results)
{
    rootNode->getPointInRange(minVec, maxVec, results);
}