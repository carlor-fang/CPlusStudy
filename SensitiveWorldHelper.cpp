#include "SensitiveWorldHelper.h"
#include <fstream>
#include "assert.h"
#include <iostream>

SensitiveWorldHelper::SensitiveWorldHelper()
{

}

SensitiveWorldHelper::~SensitiveWorldHelper()
{
    ReleaseNode(RootNode);
}

void SensitiveWorldHelper::ReleaseNode(CharNode* Cur)
{
    if (Cur)
    {
        ReleaseNode(Cur->Next);
        ReleaseNode(Cur->Sibling);
        delete Cur;
    }
}


void SensitiveWorldHelper::Load(string FileName)
{
    if (RootNode)
    {
        return;
    }
    ifstream WordFile(FileName);
    if (!WordFile)
    {
        return;
    }
    
    RootNode = new CharNode();
    RootNode->Next = 0;
    RootNode->Sibling = 0;
    RootNode->Data = 0;
    string Line;
    while (getline(WordFile, Line))
    {
        BuildNodes(Line.c_str());
    }
    WordFile.close();
}

void SensitiveWorldHelper::BuildNodes(const char* Line)
{
    CharNode* Cur = RootNode;
    int Index = 0; 
    while (Index < strlen(Line))
    {
        //std::cout << Line[Index] << std::endl;
        CharNode* Node = NodeHasExist(Cur->Next, Line[Index]);
        if (!Node)
        {
            Node = new CharNode();
            Node->Data = Line[Index];
            Node->Last = false;
            Node->Next = 0;
            Node->Sibling = 0;
            if (!Cur->Next)
                Cur->Next = Node;
            else
            {
                CharNode* TempNode = Cur->Next;
                while (TempNode->Sibling)
                {
                    TempNode = TempNode->Sibling;
                }
                TempNode->Sibling = Node;
            }
        }

        Index++;
        Cur = Node;
        if (Line[Index] == '\0' || Line[Index] == '\r' || Line[Index] == '\n')
        {
            break;
        }
    }
    Cur->Last = true;
}

CharNode* SensitiveWorldHelper::NodeHasExist(CharNode* Cur, char Data)
{
    while (Cur)
    {
        if (Cur->Data == Data)
            return Cur;
        Cur = Cur->Sibling;
    }

    return nullptr;
}

bool SensitiveWorldHelper::Check(const char* Word)
{
    CharNode* Cur = RootNode->Next;
    int Len = strlen(Word);
    int Start = -1;
    for (int i = 0; i < Len; i++)
    {
        bool HasFind = false;

        char C = Word[i];
        while (Cur)
        {
            if (Cur->Data == C)
            {
                HasFind = true;
                if (Start < 0)
                {
                    Start = i;
                }
                if (Cur->Last && !Cur->Next) 
                {
                    if (i < Len - 1)
                    {
                        Start = -1;
                        Cur = RootNode->Next;
                    }
                    else
                    {
                        break;
                    }
                }
                else if (Cur->Last)
                {
                    Start = i + 1;
                    Cur = Cur->Next;
                }
                else
                {
                    Cur = Cur->Next;
                }
                break;
            }
            Cur = Cur->Sibling;
        }

        if (!HasFind)
        {
            if (Start >= 0)
            {
                //start must have checked with root->next,so it was not used to be -1
                i = Start;
            }
            Start = -1;
            Cur = RootNode->Next;
        }
    }

    return Start >= 0;
}
