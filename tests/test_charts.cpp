#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cassert>
#include <utility>
#include <filesystem>
#include "chart_manager.h"
#include "file_reader.h"
#include "data_utilities.h"

#define ASSERT(value, errMsg)\
    if (!value)\
        std::cerr << "[\x1b[31m" << "FAILED\x1b[39m] " << errMsg << "\n";\
    assert(value);

void testCsvParser();
bool checkDataPointsMatch(
    std::vector<ChartDataPoint>, std::vector<ChartDataPoint>
);

int main()
{
    testCsvParser();
    std::cout << "all tests passed\n";
    return 0;
}

void testCsvParser()
{
    if (std::filesystem::exists("test-csv-parser.csv"))
        throw std::runtime_error("test file already exists, remove it and try again");
    std::string CSV_TITLE = "test";
    std::string FILE_NAME = "test-csv-parser.csv";
    BarChartInfo myChartInfo;
    auto initFile = [CSV_TITLE, FILE_NAME, &myChartInfo](){
        std::vector<std::string> lines{
            "title: " + CSV_TITLE,
            "x,25", "y,12.5", "z,6.25"
        };
        std::ofstream testFile(FILE_NAME);
        for (auto i : lines)
            testFile << i + "\n";
        testFile.close();
        myChartInfo = getBarChartInfoFromFile(FILE_NAME);
    };
    initFile();

    if (std::filesystem::exists("test-csv-parser.csv"))
        std::remove("test-csv-parser.csv");

    ASSERT((bool)(myChartInfo.title == CSV_TITLE), "failed to parse csv title");
    std::vector<ChartDataPoint> validDataPoints{
        {ChartDataPoint{.label="x", .value=25}},
        {ChartDataPoint{.label="y", .value=12.5}},
        {ChartDataPoint{.label="z", .value=6.25}},
    };
    ASSERT(checkDataPointsMatch(
        myChartInfo.dataPoints, validDataPoints),
        "error validating chart data points"
    );

    std::cout << "[  " << "\x1b[32mOK" << "\x1b[39m  ] " << "csv parser complete\n";
}

bool checkDataPointsMatch(
    std::vector<ChartDataPoint> dataPoint1,
    std::vector<ChartDataPoint> dataPoint2)
{
    if (dataPoint1.size() != dataPoint2.size())
        return false;
    int dataPointsCount = dataPoint1.size();
    auto checkDataPointsMatch = [](ChartDataPoint firstDp, ChartDataPoint secondDp){
        bool labelsMatch = firstDp.label == secondDp.label;
        bool valuesMatch = firstDp.value == secondDp.value;
        return (labelsMatch && valuesMatch);
    };
    for (int i = 0; i < dataPointsCount; ++i){
        bool isValid = checkDataPointsMatch(
            dataPoint1.at(i), dataPoint2.at(i)
        );
        if (!isValid)
            return 0;
    }
    return 1;
}
