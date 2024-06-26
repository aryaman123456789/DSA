CC = gcc

CFLAGS = -Wall -Wextra -pedantic

SOURCES = MWST.c

OBJECTS = $(SOURCES:.c=.o)

TARGET = MWST

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)

.PHONY: clean