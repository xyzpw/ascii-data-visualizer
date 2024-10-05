#include <iostream>
#include <string>
#include <unordered_map>
#include "visualizer.h"
#include "data_utilities.h"
#include "arg_handler.h"
#include "chart_manager.h"
#include "graph_manager.h"

VisualizerTypes getVisualizerType(std::unordered_map<std::string, std::string> args)
{
    std::string typeString = getArgValue(args, "type", "chart");
    typeString = strToLower(typeString);
    if (typeString == "chart"){
        std::string orientation = getArgValue(args, "orientation", "horizontal");
        if (orientation == "vertical")
            return VisualizerTypes::VerticalBarChart;
        return VisualizerTypes::HorizontalBarChart;
    }
    else if (typeString == "graph")
        return VisualizerTypes::DotGraph;
    return VisualizerTypes::HorizontalBarChart;
}

std::string getVisualizerAscii(int argc, char** argv)
{
    std::string result = "";
    std::string fileName = getFileNameFromArgs(argc, argv);
    auto args = getCommandLineArgs(argc, argv);

    int width = std::stoi(getArgValue(args, "width", "20"));
    int height = std::stoi(getArgValue(args, "height", "10"));
    VisualizerTypes vType = getVisualizerType(args);

    switch (static_cast<int>(vType)){
        case static_cast<int>(VisualizerTypes::VerticalBarChart):{
            VerticalBarChart verticalChart = VerticalBarChart(fileName, width, height);
            result = verticalChart.drawChart();
            break;
        }
        case static_cast<int>(VisualizerTypes::DotGraph):{
            DotGraph graph = DotGraph(fileName, width, height);
            result = graph.drawGraph();
            break;
        }
        default:{
            HorizontalBarChart horizontalChart = HorizontalBarChart(fileName, width);
            result = horizontalChart.drawChart();
            break;
        }
    }
    return result;
}
