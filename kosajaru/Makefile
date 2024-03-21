CC = g++
CFLAGS = -std=c++11

EXECUTABLE = kosaraju.bin
SOURCE = kosaraju.cpp

$(EXECUTABLE): $(SOURCE)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f $(EXECUTABLE)