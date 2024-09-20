#pragma once

#include <iostream>
#include <string>
#include <regex>
#include <unordered_map>

const std::regex commandLineArgsPattern{"(?:--)(\\w+?)\\s(\\w+)"};

std::string getArgValue(
    std::unordered_map<std::string, std::string>,
    std::string argName, std::string defaultValue
);

std::string getFileNameFromArgs(int argc, char **argv);
std::unordered_map<std::string, std::string> getCommandLineArgs(int argc, char **argv);
