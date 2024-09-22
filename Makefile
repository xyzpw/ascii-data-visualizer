CC = g++
TARGET = ascii-data-visualizer
SOURCES = ascii-data-visualizer.cpp src/*.cpp
FLAGS = -o ascii-data-visualizer -Iinclude

$(TARGET): $(SOURCES)
	$(CC) $(FLAGS) $(SOURCES)

clean:
	rm $(TARGET)