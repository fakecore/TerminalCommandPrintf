//
// Created by dylan liang on 2022/1/29.
//

#include "command_printf.h"
#include "unistd.h"
void DemoCallback(int funcNo,CommandPrintf *cp){
    cp->pushBizData(cp->addColorsGreen(cp->genFmtMsg("funcNo: %d called test\n",funcNo)));
    cp->pushBizData(cp->addColorsRed(cp->genFmtMsg("error:test\n")));
    // cp->pushBizData();
}

int main()
{
    CommandPrintf cp;
    cp.addCommand(1,"Hello World");
    cp.addCommand(2,"keep World");
    cp.addCommand(3,"keep World");
    cp.addCommand(4,"keep World");
    cp.addCommand(5,"keep World");
    cp.addCommand(6,"keep World");
    cp.addCommand(7,"keep World");
    cp.addCommand(8,"keep World");
    cp.addCommand(9,"keep World");
    cp.addCommand(10,"keep World");
    cp.setFunctionCallback([](int funcNo,CommandPrintf* cp){
        DemoCallback(funcNo,cp);
    });
    cp.execAsync();
    return 0;
}

