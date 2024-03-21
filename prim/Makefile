CC = g++
CFLAGS = -std=c++11

EXECUTABLE = prim.bin
SOURCE = prim.cpp

$(EXECUTABLE): $(SOURCE)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f $(EXECUTABLE)