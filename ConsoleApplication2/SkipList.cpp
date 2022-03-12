#include <iostream>
#include "SkipList.h"



SkipList::SkipList()
{
    srand(time(NULL));

    level = 1;
    head = new SkipNode();
}

SkipList::~SkipList()
{

}

bool SkipList::isHeadNode(const SkipNode& node)
{
    //SkipNode* headNode = head;
    //while (headNode) {
    //    if (headNode == &node) {
    //        return true;
    //    }
    //    else {
    //        headNode = headNode->index;
    //    }
    //}
    return node.prior == nullptr;
}

bool SkipList::search(int value, std::vector<SkipNode*>& outPath)
{
    SkipNode* node = head;

    auto toPriorLevelOrGetResult = [&]()->bool {
        bool ret = false;
        if (node->index) {
            outPath.push_back(node);
            node = node->index;
        }
        else {
            ret = !isHeadNode(*node) && node->value == value;
            if (ret) {
                outPath.push_back(node);
            }
            node = nullptr;
        }
        return ret;
    };

    bool ret = false;
    while (node) {
        if (node->value == value && !isHeadNode(*node))
        {
            ret = toPriorLevelOrGetResult();
        }
        else if (node->next) {
            if (node->next->value > value) {
                ret = toPriorLevelOrGetResult();
            }
            else{
                outPath.push_back(node);
                node = node->next;
            }
        }
        else {
            ret = toPriorLevelOrGetResult();
        }
    }

    if (!ret) {
        outPath.clear();
    }

    return ret;
}

bool SkipList::search(int value)
{
    std::vector<SkipNode*> path;
    return search(value, path);
}

void SkipList::add(int value)
{
    std::cout << "add value:";
    std::cout << value;
    std::cout << "。。。";
    SkipNode* newNode = new SkipNode();
    newNode->value = value;

    std::vector<SkipNode*> path;
    SkipNode* node = head;

    auto toPriorLevelOrInsertNode = [&]() {
        if (node->index) {
            path.push_back(node);
            node = node->index;
        }
        else {
            auto next = node->next;
            node->next = newNode;
            newNode->prior = node;
            if (next) {
                next->prior = newNode;
                newNode->next = next;
            }
            node = nullptr;
        }
    };

    while (node) {
        if (node->next) {
            if (node->next->value >= value) {
                toPriorLevelOrInsertNode();
            }
            else {
                node = node->next;
            }
        }
        else {
            toPriorLevelOrInsertNode();
        }
    }

    randomAddIndexNode(newNode, path);
}

bool SkipList::erase(int value)
{
    std::vector<SkipNode*> path;
    if (!search(value, path)) {
        return false;
    }


    int index = path.size() - 1;
    SkipNode* node = path.at(index);
    auto deleteNode = [&]() {
        auto next = node->next;
        auto prior = node->prior;
        if (next) {
            prior->next = next;
            next->prior = prior;
        }
        else {
            prior->next = nullptr;
        }
        delete node;
        node = nullptr;
    };

    while (node && !isHeadNode(*node) && node->value == value) {
        SkipNode* lastNode = path.at(index - 1);
        if (lastNode->next == node) {
            deleteNode();
            node = lastNode;
        }
        else {
            lastNode->index = nullptr;
            deleteNode();
            node = lastNode;
        }
        index--;
    }

    return true;
}

void SkipList::randomAddIndexNode(SkipNode* node, const std::vector<SkipNode*>& path)
{
    int curLevel = INIT_INDEX_LEVEL;
    int pathNodeCount = path.size();

    auto isGenereIndex = [&]()->bool{
        return (rand() % (1 << (curLevel - 1))) == 0;
    };

    SkipNode* levelNode = node;
    while (curLevel <= level + 1) {
        if (!isGenereIndex()) {
            break;
        }
            
        SkipNode* newNode = new SkipNode();
        newNode->value = node->value;
        newNode->index = levelNode;
        levelNode = newNode;
        std::cout << "add index at level。。。";
        //std::cout << curLevel << std::endl;

        int index = pathNodeCount - 1 - (curLevel - INIT_INDEX_LEVEL);
        SkipNode* pathNode = index >= 0 ?  path.at(index) : nullptr ;
        if (pathNode) {

            SkipNode* next = pathNode->next;
            pathNode->next = newNode;
            newNode->prior = pathNode;
            if (next) {
                newNode->next = next;
                next->prior = newNode;
            }
            curLevel++;
        }
        else {
            SkipNode* newHeadNode = new SkipNode();
            newHeadNode->next = newNode;
            newNode->prior = newHeadNode;
            newHeadNode->index = head;
            head = newHeadNode;
            level++;
            break;
        }
    }

    std::cout << std::endl;
}