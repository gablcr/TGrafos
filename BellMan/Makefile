CC = g++
CFLAGS = -std=c++11

EXECUTABLE = bellman.bin
SOURCE = bellman.cpp

$(EXECUTABLE): $(SOURCE)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f $(EXECUTABLE)