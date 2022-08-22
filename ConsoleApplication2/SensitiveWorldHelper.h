#pragma once
#include <string>

using namespace std;

struct CharNode
{
    char Data;
    //bool Last;
    CharNode* Sibling;
    CharNode* Next;
};

class SensitiveWorldHelper
{
public:
    SensitiveWorldHelper();
    ~SensitiveWorldHelper();

    void Load(string FileName);
    bool Check(const char* World);
private:
    CharNode* NodeHasExist(CharNode* Cur, char Data);
    void BuildNodes(const char* Line);
    void ReleaseNode(CharNode* Cur);

    CharNode* RootNode;
};

