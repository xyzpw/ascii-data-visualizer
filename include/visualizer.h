#pragma once

#include <iostream>
#include <string>

enum class VisualizerTypes{
    HorizontalBarChart,
    VerticalBarChart,
    DotGraph,
};

std::string getVisualizerAscii(int argc, char** argv);
