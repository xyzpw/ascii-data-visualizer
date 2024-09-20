#pragma once

#include <iostream>
#include <string>
#include <regex>
#include <unordered_map>

const std::regex csvFilePattern{"^(.+?),([\\d.]+)(?=,|$)"};
const std::regex csvDelimiterPattern{"^(\\w+?):\\s*(.+?)$"};
const std::regex validFilePattern{"^[a-z0-9_-]*\\.csv$", std::regex_constants::icase};
std::vector<std::string> getFileLines(std::string filename);
