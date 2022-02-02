//
// Created by dylan liang on 2022/1/29.
//

#include "limited_queue.h"

LimitedContent::LimitedContent(int mLimitedSize) : m_limitedSize(mLimitedSize) {}

void LimitedContent::pushData(std::string str)
{
    if (m_data.size() >= m_limitedSize)
    {
        m_data.pop_front();
    }
    m_data.push_back(str);
}

std::string LimitedContent::genContent()
{
    std::string content;
    for (auto &str : m_data)
    {
        content += str;
    }
    return content;
}

std::list<std::string> LimitedContent::genContentList()
{
    return m_data;
}

int32_t LimitedContent::getAvailableLineSize()
{
    return m_data.size();
}

int32_t LimitedContent::getLimitedSize()
{
    return m_limitedSize;
}
