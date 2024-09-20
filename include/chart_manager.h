#pragma once

#include <iostream>
#include <string>
#include <vector>

struct ChartDataPoint{
    std::string label;
    double value;
};

struct BarChartInfo{
    std::string title = "";
    std::vector<ChartDataPoint> dataPoints;
};

BarChartInfo getBarChartInfoFromFile(std::string filename);

class HorizontalBarChart{
    public:
        int maxLength;
        std::string title;
        std::vector<ChartDataPoint> dataPoints;
        std::string drawChart();
        HorizontalBarChart(std::string filename, int maxLength = 10);
};
class VerticalBarChart{
    public:
        int width, height;
        std::string title;
        std::vector<ChartDataPoint> dataPoints;
        std::string drawChart();
        VerticalBarChart(std::string filename, int width = 10, int height = 10);
};
