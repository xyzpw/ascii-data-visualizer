#pragma once

#include <iostream>
#include <string>
#include <regex>
#include <vector>

const std::regex lastDecimalPattern{"^([\\d.]+?(?:[1-9]?$|(?=0+?$)))"};

std::string doubleToStringPrecision(double value);
std::string strToLower(std::string str);
std::vector<double> sortDoubleVector(std::vector<double> _vector);
std::pair<std::vector<double>, std::vector<double>> extractVectorsFromPair(
    std::vector<std::pair<double, double>> target
);
std::pair<double, double> findMinMaxDoubleInVector(std::vector<double> target);
template<typename vecType>
bool vectorContains(const std::vector<vecType> target, const vecType value)
{
    return std::find(target.begin(), target.end(), value) != target.end();
}
