#include <iostream>
#include <string>
#include <regex>
#include <algorithm>
#include <utility>
#include "data_utilities.h"

std::string doubleToStringPrecision(double value)
{
    std::string valueString = std::to_string(value);
    std::smatch valueMatch;
    if (std::regex_search(valueString, valueMatch, lastDecimalPattern)){
        valueString = valueMatch[1].str();
    }
    if (valueString.substr(valueString.length()-1) == "."){
        valueString = valueString.substr(0, valueString.length()-1);
    }
    return valueString;
}

std::string strToLower(std::string str)
{
    std::string lowerString = "";
    for (char c : str)
        lowerString += (char)std::tolower(c);
    return lowerString;
}

std::pair<double, double> findMinMaxDoubleInVector(std::vector<double> target)
{
    double minValue = *std::min_element(target.begin(), target.end());
    double maxValue = *std::max_element(target.begin(), target.end());
    auto result = std::make_pair(minValue, maxValue);
    return result;
}

std::vector<double> sortDoubleVector(std::vector<double> _vector)
{
    std::sort(_vector.begin(), _vector.end());
    return _vector;
}

std::pair<std::vector<double>, std::vector<double>> extractVectorsFromPair(
    std::vector<std::pair<double, double>> target)
{
    std::vector<double> firstValues;
    std::vector<double> secondValues;
    for (auto i : target){
        firstValues.push_back(i.first);
        secondValues.push_back(i.second);
    }
    auto myPair = std::make_pair(firstValues, secondValues);
    return myPair;
}
