# ascii-graph
A terminal application which visualizes statistical data via ascii characters.

![ascii-data-visualizer-preview](https://github.com/user-attachments/assets/c3198118-09e4-4f85-982e-d8ee3fc6a2c3)

## Requirements
- g++
- Support for `make` command (which compiles c++ code)
- c++17



## Installation
To build/execute the file, `cd` into the directory of the repo and use the `make` command.<br>
After compiling the file, it will create an executable file.<br>

Build and execute example:
```bash
$ make
$ ./ascii-data-visualizer file.csv
```

## Usage
To visualize data, you must first specify a csv file to read.<br>
The first command line argument will be the file, e.g.:
```bash
$ ./ascii-data-visualizer file.csv
```

### Arguments
Command line arguments can be used to change how you visualize your data.<br>
If you want your chart to be vertical, you can use the `orientation` argument:
```bash
$ ./ascii-data-visualizer file.csv --orientation vertical
```

### File Format
Format follows `label,value` format:
```csv
title: Programming languages used by programmers (percent)

C,20
C++,23
Python,51
```
