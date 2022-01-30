//
// Created by dylan liang on 2022/1/29.
//

#pragma once

#include <string>
#include <list>

class LimitedContent {
public:
    LimitedContent() = default;
    LimitedContent(int32_t mLimitedSize);

    void pushData(std::string);

    std::string genContent();

    int32_t getAvailableLineSize();
    int32_t getLimitedSize();

private:
    std::list<std::string> m_data;
    int32_t m_limitedSize = 32;
};
