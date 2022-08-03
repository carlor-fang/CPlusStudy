#include <iostream>             // for cout
#include <vector>

#include "Command.h"        // the Command++ api

void PlaySound(CommandInfo* Info, std::vector<void*> VectorArg)
{
    double* DoubleValue = (double*)VectorArg[0];
    bool* BoolValue = (bool*)VectorArg[1];
    char* StringValue = (char*)VectorArg[2];
    int* IntValue = (int*)VectorArg[3];
    printf("PlaySound, ID = %d, Loop = %d, Desc = %s, Time = %f \n", *IntValue, *BoolValue, StringValue, *DoubleValue);
}

class TestCommand
{
public:
    static void StopSound(CommandInfo* Info, std::vector<void*> VectorArg)
    {
        std::cout << "StopSound" << std::endl;
    }
};

void CommandTest(int argc, char* argv[]) 
{
    Command MyCommand;
    MyCommand.Register("ps", "Double,Bool,String,Int", PlaySound);
    MyCommand.Register("ss", "Int", TestCommand::StopSound);

    MyCommand.Parse(argc, argv);
}