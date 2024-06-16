CC=gcc
CFLAGS=-Ipath/to/libyaml/include
LDFLAGS=-lyaml -lcurl -lSDL2 -lSDL2_image
TARGET=engine
OBJECTS=$(wildcard *.c)

all: $(TARGET)

$(TARGET): $(OBJECTS)
    $(CC) $(OBJECTS) -o $(TARGET) $(LDFLAGS)

%.o: %.c
    $(CC) -c $< $(CFLAGS) -o $@

clean:
    rm -f $(OBJECTS:.c=.o) $(TARGET)
