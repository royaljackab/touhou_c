TARGET = jeu
CFLAGS = -Wall
SRC = $(wildcard *.c)
OBJ = $(patsubst %.c, build/%.o, $(SRC))

INCLUDE_PATH = include
CFLAGS += -I$(INCLUDE_PATH)
LIBS = -L$(INCLUDE_PATH) -lraylib -lopengl32 -lgdi32 -lwinmm

all: build/$(TARGET)

build/$(TARGET): $(OBJ)
	gcc $(OBJ) -o $@ $(LIBS)

build/%.o: %.c | build
	gcc $(CFLAGS) -c $< -o $@

build:
	mkdir -p build

run: all
	./build/$(TARGET)
