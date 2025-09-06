
CC = clang
CFLAGS = -Wall -Wextra -O2
TARGET = futoshiki_c
SOURCE = futoshiki.c

all: $(TARGET)

$(TARGET): $(SOURCE)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCE)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)
