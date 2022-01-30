//
// Created by dylan liang on 2022/1/29.
//

#include "command_printf.h"
void DemoCallback(int funcNo){
    printf("funcNo:%d called\n");
}

int main()
{
    CommandPrintf cp;
    cp.addCommand(1,"Hello World");
    cp.addCommand(2,"keep World");
    cp.setFunctionCallback([&](int funcNo){
        DemoCallback(funcNo);
        cp.pushBizData("echo: funcNo:%d\n");
    });
    cp.execAsync();
    return 0;
}

