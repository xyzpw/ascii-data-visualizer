#pragma once

#include <iostream>
#include <string>
#include <vector>

const std::string HORIZONTAL_BORDER_CHAR = "\u2500";
const std::string HORIZONTAL_BAR_CHAR = "#";
const std::string VERTICAL_BAR_CHAR = "\u2588";

std::string drawHorizontalBorder(int length);
std::string drawHorizontalBar(int length);
int getMaxStringLength(std::vector<std::string> strings);
