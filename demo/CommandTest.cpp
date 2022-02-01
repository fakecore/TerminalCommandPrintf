//
// Created by dylan liang on 2022/1/29.
//

#include "command_printf.h"
void DemoCallback(int funcNo,CommandPrintf *cp){
    cp->pushBizData("funcNo: %d called test\n",funcNo);
}

int main()
{
    CommandPrintf cp;
    cp.addCommand(1,"Hello World");
    cp.addCommand(2,"keep World");
    cp.setFunctionCallback([](int funcNo,CommandPrintf* cp){
        DemoCallback(funcNo,cp);
        // cp.pushBizData("echo: funcNo:" + std::to_string(funcNo) + "\n");
    });
    cp.execAsync();
    return 0;
}

