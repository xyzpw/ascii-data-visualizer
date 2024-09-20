#include <iostream>
#include <string>
#include <regex>
#include <iomanip>
#include <algorithm>
#include <utility>
#include "chart_manager.h"
#include "file_reader.h"
#include "data_utilities.h"
#include "bar_chart_utilities.h"

BarChartInfo getBarChartInfoFromFile(std::string filename);
double getMaxDataPointValue(std::vector<ChartDataPoint> dataPoints);
int getHighestValueStringLength(std::vector<ChartDataPoint> dataPoints);
std::vector<std::string> getDataPointLabels(std::vector<ChartDataPoint> dataPoints);
std::vector<double> getDataPointValues(std::vector<ChartDataPoint> dataPoints);
std::vector<std::string> getVerticalBarChartLineStrings(
    int width, int height, std::vector<ChartDataPoint> dataPoints
);

HorizontalBarChart::HorizontalBarChart(std::string filename, int maxLength)
{
    if (maxLength < 10)
        maxLength = 10;
    BarChartInfo info = getBarChartInfoFromFile(filename);
    this->title = info.title;
    this->dataPoints = info.dataPoints;
    this->maxLength = maxLength;
}

VerticalBarChart::VerticalBarChart(std::string filename, int width, int height)
{
    if (width < 10)
        width = 10;
    if (height < 10)
        height = 10;
    BarChartInfo info = getBarChartInfoFromFile(filename);
    this->title = info.title;
    this->dataPoints = info.dataPoints;
    this->width = width;
    this->height = height;
}

std::string HorizontalBarChart::drawChart()
{
    std::vector<std::string> dataPointLabels = getDataPointLabels(dataPoints);
    std::vector<double> dataPointValues = getDataPointValues(dataPoints);

    int maxLabelLength = getMaxStringLength(dataPointLabels);
    double highestValue = *std::max_element(dataPointValues.begin(), dataPointValues.end());
    int highestValueString = getHighestValueStringLength(dataPoints);

    std::string chartAscii = title + "\n";
    std::string horizontalBorder = drawHorizontalBorder(
        2 + maxLabelLength + 3 + maxLength + 3 + highestValueString + 2
    );
    chartAscii += horizontalBorder;
    chartAscii += "\n";
    for (auto i : dataPoints){
        // Creating values which are required to draw the chart.
        int barLength = i.value / highestValue * maxLength;
        std::string spacingAfterLabel( maxLabelLength - i.label.length() , ' ');
        std::string valueString = doubleToStringPrecision(i.value);
        std::string spacingAfterValueText( highestValueString - valueString.length() , ' ');
        std::string spacingAfterBar(maxLength - barLength, ' ');

        // Creating strings for each section of the chart.
        std::string labelWithSpacing = i.label + spacingAfterLabel;
        std::string barWithSpacing = drawHorizontalBar(barLength) + spacingAfterBar;
        std::string valuesWithSpacing = valueString + spacingAfterValueText;

        // Adding sections together to make a string for the current line.
        chartAscii += "| " + labelWithSpacing + " | " + barWithSpacing + " | " + valuesWithSpacing + " |";
        chartAscii += "\n";
    }
    chartAscii += horizontalBorder + "\n";
    return chartAscii;
}

std::string VerticalBarChart::drawChart()
{
    std::vector<std::string> dataPointLabels = getDataPointLabels(dataPoints);
    std::vector<double> dataPointValues = getDataPointValues(dataPoints);

    std::string chartAscii = title + "\n";
    int widthFromStartColumn = width - 2;
    std::string chartFloorAscii = drawHorizontalBar(width);

    std::vector<std::string> linesToDraw = getVerticalBarChartLineStrings(
        widthFromStartColumn, height, dataPoints
    );

    for (auto line : linesToDraw){
        chartAscii += "| ";
        chartAscii += line + "\n";
    }
    chartAscii += std::string(width - (widthFromStartColumn / dataPoints.size()), '-') + "\n";
    for (auto i : dataPointLabels){
        chartAscii += " " + i;
    }
    return chartAscii;
}

BarChartInfo getBarChartInfoFromFile(std::string filename)
{
    BarChartInfo chartInfo;
    std::smatch csvMatch;
    std::vector<std::string> fileLines = getFileLines(filename);
    for (auto line : fileLines){
        if (std::regex_search(line, csvMatch, csvFilePattern)){
            std::string label = csvMatch[1].str();
            double value = std::stod(csvMatch[2].str());
            chartInfo.dataPoints.push_back(ChartDataPoint{label, value});
        }
        else if (std::regex_search(line, csvMatch, csvDelimiterPattern)){
            std::string label = csvMatch[1].str();
            std::string value = csvMatch[2].str();
            if (label == "title")
                chartInfo.title = value;
        }
    }
    return chartInfo;
}

/*
    Calculates and returns the string to draw for each line of the
    vertical bar chart.

    @returns A vector of strings line-by-line which make the ascii chart.
*/
std::vector<std::string> getVerticalBarChartLineStrings(
        int width, int height, std::vector<ChartDataPoint> dataPoints)
{
    std::vector<std::string> lineStrings;
    int spacesBetweenBars = width / dataPoints.size();
    double maxValue = getMaxDataPointValue(dataPoints);
    std::vector<std::pair<ChartDataPoint, int>> barHeights;
    for (auto i : dataPoints){
        int currentHeight = i.value / maxValue * height;
        barHeights.push_back(std::make_pair(i, currentHeight));
    }

    for (int lineNumber = height; lineNumber > 0; --lineNumber){
        int currentDataPointIndex = 0;
        std::string currentLineString = "";
        for (int currentColumn = 0; currentColumn < width; ++currentColumn){
            if (currentColumn % spacesBetweenBars != 0){
                currentLineString += " ";
                continue;
            }
            if (lineNumber <= barHeights.at(currentDataPointIndex).second)
                currentLineString += VERTICAL_BAR_CHAR;
            else
                currentLineString += " ";
            if (currentDataPointIndex + 1 == barHeights.size())
                break;
            ++currentDataPointIndex;
        }
        lineStrings.push_back(currentLineString);
    }
    return lineStrings;
}

double getMaxDataPointValue(std::vector<ChartDataPoint> dataPoints)
{
    double greatestValue = 0.0;
    for (auto i : dataPoints){
        if (i.value > greatestValue)
            greatestValue = i.value;
    }
    return greatestValue;
}

/*
    Converts all the double values of the data points to formatted string versions
    and returns the length of the longest formatted string among them.

    @returns The length of the longest formatted string representation of a data point value.
*/
int getHighestValueStringLength(std::vector<ChartDataPoint> dataPoints)
{
    int length = 0;
    for (auto i : dataPoints){
        int iterLength = doubleToStringPrecision(i.value).length();
        if (iterLength > length)
            length = iterLength;
    }
    return length;
}

std::vector<std::string> getDataPointLabels(std::vector<ChartDataPoint> dataPoints)
{
    std::vector<std::string> labels;
    for (auto i : dataPoints){
        labels.push_back(i.label);
    }
    return labels;
}

std::vector<double> getDataPointValues(std::vector<ChartDataPoint> dataPoints)
{
    std::vector<double> values;
    for (auto i : dataPoints){
        values.push_back(i.value);
    }
    return values;
}
