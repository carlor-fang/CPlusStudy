#pragma once
#include <vector>

const int INIT_INDEX_LEVEL = 2; //Ë÷Òý¿ªÊ¼Level

struct SkipNode {
    SkipNode* prior = nullptr;
    SkipNode* next = nullptr;
    int value = 0;
    SkipNode* index = nullptr;
};

class SkipList
{
private:
    void randomAddIndexNode(SkipNode* node, const std::vector<SkipNode*>& path);
    bool isHeadNode(const SkipNode& node);

    bool search(int value, std::vector<SkipNode*>& outPath);
public:
    SkipList();
    ~SkipList();
    bool search(int value);
    void add(int value);
    bool erase(int value);
private:
    int level;
    SkipNode* head;
};

