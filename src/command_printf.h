//
// Created by dylan liang on 2022/1/28.
//

#pragma once

#include <cstdint>
#include <string>
#include <map>
#include <thread>
#include <list>
#include <vector>
#include <functional>
#include <iostream>
#include <algorithm>
#include <regex>
#include <algorithm>

#define INIT_MODE 0
#define FUNCTION_MODE 1
#define COMMAND_MODE 2
#define EXIT_MODE 3

struct FunctionRecord {
    int serialNo;
    std::string functionName;
};

struct CommandInput {
    CommandInput() {
        mode = INIT_MODE;
        functionNo = 0;
    }

    int mode;
    int functionNo; //-1 return 0 do nothing
    std::string commandNo;
    std::string commandContent;
};

/**
 * inner class
 */
class LimitedContent {
public:
    LimitedContent() = default;

    LimitedContent(int32_t mLimitedSize = 32) : m_limitedSize(mLimitedSize) {};

    void pushData(std::string str) {
        if (m_data.size() >= m_limitedSize) {
            m_data.pop_front();
        }
        m_data.push_back(str);
    }

    std::string genContent() {
        std::string content;
        for (auto &str: m_data) {
            content += str;
        }
        return content;
    }

    std::list<std::string> genContentList() {
        return m_data;
    }

    int32_t getAvailableLineSize() {
        return m_data.size();
    }

    int32_t getLimitedSize() {
        return m_limitedSize;
    }

private:
    std::list<std::string> m_data;
    uint32_t m_limitedSize;
};

/*
 * output example
 * output panel struct
 * -----------------------
 * title
 * -----------------------
 * Content Area
 * -----------------------
 * Function List
 * -----------------------
 * <0 1 2...N>
 * prev (h) next(l)
 *
 */

class CommandPrintf {
public:
    CommandPrintf() : m_contentArea(30) {
        m_pageSize = 10;
        pageIndex = 0;
        pageLast = 0;
        m_running = false;
        m_workThread = nullptr;
    }

    ~CommandPrintf() {
        m_running = false;
        if (m_workThread && m_workThread->joinable()) {
            m_workThread->join();
        }
    }

    /**
     * @brief:start it at current thread
     */
    void exec() {
        m_running = true;
        std::list<std::string> store;
        while (m_running) {
            repaint();
            std::string content;
            CommandInput commandInput = parserInput(getLineInput());
            if (commandInput.mode == EXIT_MODE) {
            } else if (commandInput.mode == FUNCTION_MODE) {
                if (!m_funcCallback) {
                    static int index = 0;
                    m_contentArea.pushData(std::to_string(index++) + "请设置回调函数\n");
                } else {
                    m_funcCallback(commandInput.functionNo, this);
                }
            } else if (commandInput.mode == COMMAND_MODE) {
                if (commandInput.commandNo == "j") {
                    pageIndex = std::max(pageIndex - 1, 0);
                } else if (commandInput.commandNo == "k") {
                    pageIndex = std::min(pageIndex + 1, pageLast);
                } else {
                    pushContentArea("Unknown command:%s\n", commandInput.commandNo.c_str());
                }
            } else if (commandInput.mode == INIT_MODE) {
            }
        }
    }

    /*
     * brief:
     * start it at a new thread
     */
    void execAsync() {
        // TODO start a new thread
        m_workThread = new std::thread(std::bind(&CommandPrintf::exec, this));
    }

    void printContentArea() {
        auto data = m_contentArea.genContentList();
        m_fresh.insert(m_fresh.end(), data.begin(), data.end());
        int32_t padSize = m_contentArea.getLimitedSize() - m_contentArea.getAvailableLineSize();
        for (int i = 0; i < padSize; i++) {
            m_fresh.push_back("\n");
        }
    }

    void printTitle() {
        m_fresh.insert(m_fresh.end(), m_titleStore.begin(), m_titleStore.end());
    }

    void printFunctionList() {
        int32_t functionStartCount = (pageIndex) * m_pageSize;
        int32_t functionEndCount = (pageIndex + 1) * m_pageSize;
        int32_t size = m_funcList.size();
        functionEndCount = functionEndCount < size ? functionEndCount : size;
        char buf[1024];
        for (int i = functionStartCount; i < functionEndCount; i++) {
            auto &ele = m_funcList[i];
            sprintf(buf, "%d.%s\n", ele.serialNo, ele.functionName.c_str());
            m_fresh.push_back(std::string(buf));
        }
    }

    void printfPages() {
        std::string content = "< ";
        for (int i = 0; i <= pageLast; i++) {
            if (pageIndex == i) {
                content += addColorsGreen(std::to_string(i)) + " ";
            } else {
                content += std::to_string(i) + " ";
            }
        }
        content += ">";
        m_fresh.push_back(content);
        m_fresh.push_back("\n");
    }

    void printCommander() {
        m_fresh.push_back("Prev(j) Next(k)\n");
    }

    void prePaint() {
        printTitle();
        m_fresh.push_back("-----------------------\n");
        printContentArea();
        m_fresh.push_back("-----------------------\n");
        m_fresh.push_back("Function List:\n");
        printFunctionList();
        m_fresh.push_back("-----------------------\n");
        printfPages();
        printCommander();
        m_fresh.push_back("请输入命令:");
    }

    void paintScreen() {
        std::string content;
        for (auto &c: m_fresh) {
            content += c;
        }
        printf("%s\n", content.c_str());
    }

    void repaint() {
        clearScreen();
        prePaint();
        paintScreen();
    }

    void clearScreen() {
        for (int i = 0; i <= m_fresh.size(); i++) {
            printf("\033[K");  //清除该行
            printf("\033[1A");
        }
        m_fresh.clear();
    }

    void doExit();

    void pushContentArea(std::string str) {
        m_contentArea.pushData(str);
        repaint();
    }

    template<typename... Args>
    void pushContentArea(const char *fmt, Args... args) {
        m_contentArea.pushData(genFmtMsg(fmt, args...));
        repaint();
    }

    template<typename... Args>
    std::string genFmtMsg(const char *fmt, Args... args) {
        //TODO
        char buf[1024] = {0};
        sprintf(buf, fmt, args...);
        return std::string(buf);
    }

    //TODO implement
//    void addCommand(std::string functionName) {
//    }

    void addCommand(int32_t serialNo, std::string functionName) {
        if (findCommand(serialNo)) {
            return;
        }
        FunctionRecord functionRecord;
        functionRecord.serialNo = serialNo;
        functionRecord.functionName = functionName;
        m_funcList.push_back(functionRecord);
        std::sort(m_funcList.begin(), m_funcList.end(),
                  [](const FunctionRecord &l, const FunctionRecord &r) { return l.serialNo < r.serialNo; });
        calPage();
    }

    std::string addColorsGreen(std::string str) {
        std::string colorPrefix = "\033[32;49;1m" + str + "\033[0m";
        return colorPrefix;
    }

    std::string addColorsRed(std::string str) {
        std::string colorPrefix = "\033[31;49;1m" + str + "\033[0m";
        return colorPrefix;
    }

    std::string getTimeStamp() {
        // auto start = std::chrono::steady_clock::now();
        return "";
    }

    void setFunctionCallback(std::function<void(int, CommandPrintf *)> f) {
        m_funcCallback = f;
    }

    void setTitle(std::list<std::string> titles) {
        m_titleStore = titles;
    }

    void setPageSize(int32_t size) {
        m_pageSize = size;
    }

private:
    void calPage() {
        size_t size = m_funcList.size();
        if (size % m_pageSize != 0) {
            pageLast = size / m_pageSize;
        } else {
            pageLast = size / m_pageSize - 1;
        }
    }

    std::string getLineInput() {
        std::string content;
        std::getline(std::cin, content);
        return content;
    }

    CommandInput parserInput(std::string content) {
        CommandInput commandInput;
        if (content.empty()) {
            m_contentArea.pushData("请输入指令\n");
        } else {
            if (matchNumber(content, commandInput)) {
            } else if (matchCommand(content, commandInput)) {
            }
        }
        return commandInput;
    }

    bool matchNumber(std::string str, CommandInput &commandInput) {
        std::regex baseRegex("^\\s*[0-9]+\\s*");
        std::smatch baseMatch;
        bool state = std::regex_match(str, baseMatch, baseRegex);
        if (!state || baseMatch.size() != 1) {
            return false;
        }
        commandInput.mode = FUNCTION_MODE;
        commandInput.functionNo = std::stoi(baseMatch[0]);
        return true;
    }

    bool matchCommand(std::string str, CommandInput &commandInput) {
        std::regex baseRegex("^\\s*([a-zA-Z])\\s*([0-9]*)\\s*");
        std::smatch baseMatch;
        bool state = std::regex_match(str, baseMatch, baseRegex);
        if (!state && baseMatch.size() == 1) {
            return false;
        }
        commandInput.mode = COMMAND_MODE;
        commandInput.commandNo = baseMatch[1];
        if (baseMatch.size() == 3) {
            commandInput.commandContent = baseMatch[2];
        }
        return true;
    }

    bool findCommand(int serialNo) {
        for (auto &command: m_funcList) {
            if (command.serialNo == serialNo) {
                return true;
            }
        }
        return false;
    }

private:

    std::vector<FunctionRecord> m_funcList;

    int32_t pageIndex;

    int32_t pageLast;

    int32_t m_pageSize;

    std::function<void(int, CommandPrintf *)> m_funcCallback;

    LimitedContent m_contentArea;

    std::thread *m_workThread;

    bool m_running;

    std::list<std::string> m_fresh;

    std::list<std::string> m_titleStore;

};






