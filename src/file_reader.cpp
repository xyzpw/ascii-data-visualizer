#include <iostream>
#include <string>
#include <filesystem>
#include <fstream>
#include <regex>
#include <unordered_map>
#include "file_reader.h"
#include "chart_manager.h"

bool checkFileNameMatches(std::string filename);
bool checkFileExists(std::string filename);

std::vector<std::string> getFileLines(std::string filename)
{
    std::vector<std::string> fileLines;
    if (!checkFileNameMatches(filename))
        throw std::runtime_error("file name contains invalid characters");
    else if (!checkFileExists(filename))
        throw std::runtime_error("file does not exist");
    std::ifstream fileStream(filename);
    for (std::string line; std::getline(fileStream, line);){
        fileLines.push_back(line);
    }; fileStream.close();
    return fileLines;
}

bool checkFileNameMatches(std::string filename)
{
    if (std::regex_search(filename, validFilePattern)){
        return true;
    } return false;
}

bool checkFileExists(std::string filename)
{
    return std::filesystem::exists(filename);
}
