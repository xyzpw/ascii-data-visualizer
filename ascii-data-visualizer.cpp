#include <iostream>
#include <string>
#include "visualizer.h"

int main(int argc, char **argv)
{
    std::string visualizerAscii = getVisualizerAscii(argc, argv);
    std::cout << visualizerAscii << std::endl;
    return 0;
}
