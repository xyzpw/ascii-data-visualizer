#include <iostream>
#include <string>
#include <unordered_map>
#include <regex>
#include "arg_handler.h"

std::string getArgValue(
    std::unordered_map<std::string, std::string> args,
        std::string argName, std::string defaultValue = "")
{
    if (!args.count(argName))
        return defaultValue;
    return args.at(argName);
}

std::string getFileNameFromArgs(int argc, char **argv)
{
    if (argc > 1)
        return argv[1];
    throw std::runtime_error("no file specified");
}

std::unordered_map<std::string, std::string> getCommandLineArgs(int argc, char **argv)
{
    std::unordered_map<std::string, std::string> args;
    if (argc == 1)
        return args;
    std::smatch argMatch;
    std::string argsString("");
    for (int i = 1; i < argc; ++i){
        argsString += argv[i];
        if (i+1 < argc)
            argsString += " ";
    }
    for (std::sregex_iterator i = std::sregex_iterator(
            argsString.begin(), argsString.end(), commandLineArgsPattern);
            i != std::sregex_iterator();
            ++i)
    {
        std::smatch argMatch = *i;
        std::string arg = argMatch[1].str();
        std::string argValue = argMatch[2].str();
        args[arg] = argValue;
    }
    return args;
}
