CC				 = gcc
CFLAGS			+= -I../../include -DUSE_STDC -D_internal_version_us
CFLAGS			+= -O0 -g
LDFLAGS			+= -lm -lSDL2 -lSDL2_image -lSDL2_ttf

TARGET = simulator
SOURCE = main.c sotn.c ovl.c mock.c draw.c
SOURCE += entitybreakable.c entityprizedrop.c entitygaibon.c

all: $(TARGET)

$(TARGET): $(SOURCE)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCE) $(LDFLAGS)

clean:
	rm -f $(TARGET)
