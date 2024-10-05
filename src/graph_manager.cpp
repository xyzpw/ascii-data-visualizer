#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <utility>
#include <algorithm>
#include <unordered_map>
#include <numeric>
#include "graph_manager.h"
#include "file_reader.h"
#include "data_utilities.h"

const std::regex graphAxisRePattern{"^(\\d+(?:\\.\\d+)?),(\\d+(?:\\.\\d+)?)", std::regex_constants::icase};

GraphPlotInfo getGraphInfoFromFile(std::string filename);
std::vector<std::string> getDotGraphLineStrings(int width, int height, GraphPlotInfo);
std::string getDotGraphXAxisTicks(int width, std::vector<double> xValues);

DotGraph::DotGraph(std::string filename, int width, int height)
{
    if (width < 20) width = 20;
    if (height < 10) height = 10;
    GraphPlotInfo info = getGraphInfoFromFile(filename);
    this->xLabel = info.xLabel;
    this->yLabel = info.yLabel;
    for (auto i : info.values)
        this->values.push_back(i);
    this->width = width;
    this->height = height;
}

std::string DotGraph::drawGraph()
{
    std::string graph = "";
    graph = yLabel + "\n";
    GraphPlotInfo plotInfo{
        .xLabel = xLabel, .yLabel = yLabel, .values = values
    };
    std::vector<std::string> graphLines = getDotGraphLineStrings(
        width, height, plotInfo
    );

    for (auto i : graphLines){
        graph += i + "\n";
    }
    int xLabelPaddingCount = width / 2 - xLabel.length() / 2;
    graph += "\n" + std::string(xLabelPaddingCount, ' ') + xLabel;
    return graph;
}

GraphPlotInfo getGraphInfoFromFile(std::string filename)
{
    GraphPlotInfo graphInfo{};
    std::vector<std::string> fileLines = getFileLines(filename);
    std::smatch reMatch;
    for (auto line : fileLines)
    {
        if (std::regex_search(line, reMatch, graphAxisRePattern)){
            double xValue = std::stod(reMatch[1].str());
            double yValue = std::stod(reMatch[2].str());
            std::pair<double, double> valuePair = std::make_pair(xValue, yValue);
            graphInfo.values.push_back(valuePair);
        }
        else if (std::regex_search(line, reMatch, csvDelimiterPattern)){
            bool isXLabel = strToLower(reMatch[1].str()) == "x";
            bool isYLabel = strToLower(reMatch[1].str()) == "y";
            if (isXLabel)
                graphInfo.xLabel = reMatch[2].str();
            else if (isYLabel)
                graphInfo.yLabel = reMatch[2].str();
        }
    }
    return graphInfo;
}

std::vector<std::string> getDotGraphLineStrings(
    int width, int height, GraphPlotInfo graphInfo)
{
    std::vector<std::string> dotGraphLines{};
    auto xyValues = extractVectorsFromPair(graphInfo.values);

    double lowestXValue = findMinMaxDoubleInVector(xyValues.first).first;
    double greatestXValue = findMinMaxDoubleInVector(xyValues.first).second;
    double lowestYValue = findMinMaxDoubleInVector(xyValues.second).first;
    double greatestYValue = findMinMaxDoubleInVector(xyValues.second).second;
    // Length of greatest `y` axis value when converted to a string.
    int maxYValueStrLength = std::to_string((int)greatestYValue).size();

    // Computes the (x, y) coordinates from a given value.
    auto getValueCoordinates = [=](std::pair<double, double> value){
        int xCoordinate = value.first / greatestXValue * width;
        int yCoordinate = value.second / greatestYValue * height;
        return std::make_pair(xCoordinate, yCoordinate);
    };

    // Determining where each data point will appear on our graph.
    std::vector<std::pair<int, int>> plotAppearances{};
    for (auto i : graphInfo.values){
        auto valuePair = std::make_pair(i.first, i.second);
        auto coordinates = getValueCoordinates(valuePair);
        plotAppearances.push_back(coordinates);
    }

    // Create an unordered map to store line numbers as keys and their tick labels as values.
    std::unordered_map<int, int> yAxisTicks{};
    for (int lineNumber = 0; lineNumber <= height; ++lineNumber){
        int valueAtLine = (greatestYValue - lowestYValue) / height * lineNumber;
        bool tickExists = false;
        for (auto it : yAxisTicks)
            if (it.second == valueAtLine){
                tickExists = 1;
                break;
            }
        if (!tickExists)
            yAxisTicks.insert({lineNumber, valueAtLine});
    }

    // Initialize the beginning of a string to the dot graph.
    auto initLineString = [&](int line){
        std::string result = "";
        if (!yAxisTicks.count(line))
            return result + std::string(maxYValueStrLength, ' ') + " |";
        int value = yAxisTicks.at(line);
        int valueStrLength = std::to_string(value).size();
        std::string padding(maxYValueStrLength - valueStrLength, ' ');
        result += std::to_string(value) + padding + " |";
        return result;
    };

    for (int lineNumber = height; lineNumber > 0; --lineNumber)
    {
        std::string currentLineString = initLineString(lineNumber);
        for (int columnNumber = 0; columnNumber <= width; ++columnNumber)
        {
            auto coordinates = std::make_pair(columnNumber, lineNumber);
            if (std::find(plotAppearances.begin(), plotAppearances.end(), coordinates) != plotAppearances.end())
                currentLineString += "*";
            else
                currentLineString += " ";
        }
        dotGraphLines.push_back(currentLineString);
    }
    dotGraphLines.push_back(std::string(maxYValueStrLength + 2, ' ') + std::string(width, '-'));
    std::string xTicksString(maxYValueStrLength + 2, ' ');
    xTicksString += getDotGraphXAxisTicks(width, xyValues.first);
    dotGraphLines.push_back(xTicksString);
    return dotGraphLines;
}

std::string getDotGraphXAxisTicks(int width, std::vector<double> xValues)
{
    std::string result = "";
    std::sort(xValues.begin(), xValues.end());
    std::pair<double, double> minMaxValue = findMinMaxDoubleInVector(xValues);
    int minSpacesPerTick = width / xValues.size() + static_cast<int>(width / xValues.size() == 0);

    auto getColumnValue = [minMaxValue, width](int column){
        double range = minMaxValue.second - minMaxValue.first;
        int value = range / width * column;
        return value;
    };

    std::vector<int> usedTickValues{};
    for (int columnIndex = 0; columnIndex < width; ++columnIndex)
    {
        int tickValue = getColumnValue(columnIndex);

        // Check if there is enough padding to display `x` axis tick labels.
        bool isPadded = false;
        if (result.find_last_not_of(' ') != result.size() - 1 || columnIndex == 0)
            isPadded = result.find_last_of(' ') - result.find_last_not_of(' ') >= minSpacesPerTick || columnIndex == 0;

        // Add tick label if unused and padding has enough spaces.
        if (!vectorContains(usedTickValues, tickValue) && isPadded){
            usedTickValues.push_back(tickValue);
            result += std::to_string(tickValue);
        }
        else {
            result += " ";
        }
        if (result.size() >= width)
            break;
    }
    return result;
}
