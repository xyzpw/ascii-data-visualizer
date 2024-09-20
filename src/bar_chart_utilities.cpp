#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "bar_chart_utilities.h"

std::string drawHorizontalBorder(int length)
{
    std::string border = "";
    for (int i = 0; i < length; ++i)
        border += HORIZONTAL_BORDER_CHAR;
    return border;
}

std::string drawHorizontalBar(int length)
{
    std::string bar = "";
    for (int i = 0; i < length; ++i)
        bar += HORIZONTAL_BAR_CHAR;
    return bar;
}

int getMaxStringLength(std::vector<std::string> strings)
{
    int length = 0;
    for (auto s : strings){
        if (length < s.length())
            length = s.length();
    }
    return length;
}
