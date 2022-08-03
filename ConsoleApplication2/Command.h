#pragma once
#include <map>
#include <vector>

class Command;
struct CommandInfo;

typedef void(CallbackFunc)(CommandInfo* Info, std::vector<void*> VectorArg);

enum EValueType
{
    Int = 1,
    Double,
    String,
    Bool,
};

const char DELIMITER = ',';

struct CommandInfo
{
    CallbackFunc* Callback;
    std::vector<EValueType> ArgTypes;
    CommandInfo()
    {
        Callback = NULL;
        std::cout << "default construct" << std::endl;
    }
    CommandInfo(CallbackFunc* InCallback)
    {
        Callback = InCallback;
        std::cout << "construct" << std::endl;
    }
    CommandInfo(const CommandInfo& Opetion)
    {
        std::cout << "option copy" << std::endl;
    }
    ~CommandInfo()
    {
        std::cout << "option destructor" << std::endl;
    }
};

struct CompareCommandKey {
    bool operator () (const char* C1, const char* C2) const
    {
        return strcmp(C1, C2) < 0;
    }
};
typedef std::map<const char*, CommandInfo*, CompareCommandKey> CommandMap;

class Command
{
public:
    Command();
    Command(const Command& InCommand);
    ~Command();

    bool Register(const char* CommandName, const char* CommandArg, CallbackFunc Callback);
    bool Parse(int ArgCount, char** Args);
private:
    CommandMap Commands;
};