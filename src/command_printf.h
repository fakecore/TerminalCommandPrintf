//
// Created by dylan liang on 2022/1/28.
//

#pragma once

#include <cstdint>
#include <string>
#include <map>
#include <thread>
#include <vector>
#include <functional>
#include "limited_queue.h"

#define INIT_MODE 0
#define FUNCTION_MODE 1
#define COMMAND_MODE 2
#define EXIT_MODE 3

struct FunctionRecord
{
    int serialNo;
    std::string functionName;
};
struct CommandInput
{
    CommandInput()
    {
        mode = INIT_MODE;
        functionNo = 0;
    }
    int mode;
    int functionNo; //-1 return 0 do nothing
    std::string commandNo;
    std::string commandContent;
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
class CommandPrintf
{
public:
    CommandPrintf();

    ~CommandPrintf();

    /**
     * @brief:
     *
     * @param serialNo
     * @param functionName
     */
    void addCommand(int32_t serialNo, std::string functionName);

    /**
     * @brief:
     *
     * @param functionName
     */
    void addCommand(std::string functionName);

    /**
     * @brief:start it at current thread
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

    void setFunctionCallback(std::function<void(int, CommandPrintf *)> f);

    bool findCommand(int serialNo);

    void pushBizData(std::string str)
    {
        m_contentArea.pushData(str);
    }

    template <typename... Args>
    void pushBizData(const char *fmt, Args... args)
    {
        //TODO
        char buf[1024] = {0};
        sprintf(buf, fmt, args...);
        m_contentArea.pushData(buf);
    }

    bool matchNumber(std::string str,CommandInput &commandInput);
    bool matchCommand(std::string str,CommandInput &commandInput);
    void calPage();

    std::string addColorsGreen(std::string str);
private:
    //    std::map<int32_t , std::string> m_funcMap;
    // sorted array
    std::vector<FunctionRecord> m_funcList;

    int32_t pageIndex;

    int32_t pageLast;

    int32_t m_pageSize;

    std::function<void(int, CommandPrintf *)> m_funcCallback;

    LimitedContent m_contentArea;

    std::thread *m_workThread;

    bool m_running;
};
