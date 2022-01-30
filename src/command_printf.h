//
// Created by dylan liang on 2022/1/28.
//

#pragma once

#include <cstdint>
#include <string>
#include <map>
#include <vector>
#include <functional>
#include "limited_queue.h"

#define INIT_MODE 0
#define ACTION_MODE 2
#define FUNCTION_MODE 1
#define ACTION_MODE 2
#define EXIT_MODE 2

struct FunctionRecord{
    int serialNo;
    std::string functionName;
};
struct CommandInput{
    CommandInput(){
        mode = INIT_MODE;
        functionNo = 0;
    }
    int mode;
    int functionNo;//-1 return 0 do nothing

};

/*
 * demo: height:20 auto complete
 * output
 * -----------------------  0
 * Function:xxx             1
 * hello world
 *
 * -----------------------  20
 * Function List            21
 * -----------------------  22
 * 1. Hello World!
 * 2. Copy That
 * -----------------------  30
 * 0 1 2...10               31
 * prev (h) next(l)         32
 *
 */
class CommandPrintf {
public:
    CommandPrintf();

    ~CommandPrintf();

    void addCommand(int32_t serialNo, std::string functionName);

    void addCommand(std::string functionName);

    /*
     * brief:
     * start it at current thread
     */
    void exec();

    /*
     * brief:
     * start it at a new thread
     */
    void execAsync();

    std::string printFunctions();

    std::string printfPages();

    std::string printCommander();

    std::string getLineInput();

    CommandInput parserInput(std::string content);

    void doExit();

    std::string printMsgs();

    void addBizContent(std::string str);

    std::string getTimeStamp();

    void clearScreen();

    void setFunctionCallback(std::function<void(int)> f);

    void pushBizData(std::string str);
private:

//    std::map<int32_t , std::string> m_funcMap;
    // sorted array
    std::vector<FunctionRecord> m_funcList;

    int32_t pageIndex;
    int32_t pageMax;

    int32_t m_pageSize;

    std::function<void(int)> m_funcCallback;

    LimitedContent m_contentArea;
};

