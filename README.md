# TerminalCommandPrintf

又快又好用的命令行交互工具,支持上内容输出,下命令交互形式.

## 说明

下载

```shell
git clone https://github.com/planetPocket/TerminalCommandPrintf
```

![terminalCommandDemo.gif](https://github.com/planetPocket/TerminalCommandPrintf/blob/main/resources/terminalCommandDemo.gif)

终端页面组成

```c++
/*
 * output example
 * output panel layout
 * -----------------------
 * title
 * -----------------------
 * Content Area
 * -----------------------
 * Function List
 * -----------------------
 * <0 1 2...N>
 * prev (h) next(l)
 */
```

## 使用教程

```c++
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
        cp.pushContentArea("echo: funcNo:%d\n");
    });
    cp.execAsync();
    return 0;
}

```

## TODO

- [x] 命令行功能解析
- [ ] 支持写文件
- [ ] 性能优化
- [x] 命令解析支持
- [x] 终端涂色
- [ ] Content Area 支持回滚显示
