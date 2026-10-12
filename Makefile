CC = gcc
CFLAGS = -O2 -Wall
TARGET = code
SOURCE = solution.c

$(TARGET): $(SOURCE)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCE)

clean:
	rm -f $(TARGET)

.PHONY: all clean
all: $(TARGET)