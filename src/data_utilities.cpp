#include <iostream>
#include <string>
#include <regex>
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
