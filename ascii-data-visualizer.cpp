#include <iostream>
#include <string>
#include <fstream>
#include <regex>
#include <filesystem>
#include <cmath>
#include <unordered_map>
#include "chart_manager.h"
#include "file_reader.h"
#include "arg_handler.h"

int main(int argc, char **argv)
{
    std::string fileName = getFileNameFromArgs(argc, argv);
    auto cmdArgs = getCommandLineArgs(argc, argv);

    std::string orientation = getArgValue(cmdArgs, "orientation", "horizontal");
    int length = std::stoi(getArgValue(cmdArgs, "length", "10"));
    std::string chartString = "";
    if (orientation == "vertical"){
        int height = std::stoi(getArgValue(cmdArgs, "height", "10"));
        VerticalBarChart myChart(fileName, length, height);
        chartString = myChart.drawChart();
    } else{
        HorizontalBarChart myChart(fileName, length);
        chartString = myChart.drawChart();
    }
    std::cout << chartString;
    return 0;
}
