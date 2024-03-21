CC = g++
CFLAGS = -std=c++11

EXECUTABLE = kruskal.bin
SOURCE = kruskal.cpp

$(EXECUTABLE): $(SOURCE)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f $(EXECUTABLE)