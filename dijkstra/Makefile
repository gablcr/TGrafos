CC = g++
CFLAGS = -std=c++11

EXECUTABLE = dijkstra.bin
SOURCE = dijkstra.cpp

$(EXECUTABLE): $(SOURCE)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f $(EXECUTABLE)