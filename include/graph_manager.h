#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <utility>

struct GraphPlotInfo{
    std::string xLabel;
    std::string yLabel;
    std::vector<std::pair<double, double>> values;
};


class DotGraph{
    public:
        int width, height;
        std::string xLabel;
        std::string yLabel;
        std::vector<std::pair<double, double>> values;
        std::string drawGraph();
        DotGraph(std::string filename, int width = 20, int height = 10);
};
