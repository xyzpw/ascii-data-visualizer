#pragma once

#include <iostream>
#include <string>
#include <regex>

const std::regex lastDecimalPattern{"^([\\d.]+?(?:[1-9]?$|(?=0+?$)))"};

std::string doubleToStringPrecision(double value);
