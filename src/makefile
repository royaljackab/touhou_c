TARGET = jeu
CFLAGS = -Wall

# Recherche récursive de tous les fichiers .c, en excluant ANY build/ ou include/ directories
SRC = $(shell find . -type f -name "*.c" ! -path "*/build/*" ! -path "*/include/*")

# Convertir les chemins sources en chemins objets dans le dossier build
OBJ = $(patsubst %.c, build/%.o, $(SRC))

INCLUDE_PATH = include
CFLAGS += -I$(INCLUDE_PATH)

# --- DÉTECTION AUTOMATIQUE DE L'OS ---
UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Linux)
    # CONFIGURATION LINUX
    LIBS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
else ifeq ($(UNAME_S),Darwin)
    # CONFIGURATION MACOS (:p)
    # On utilise les frameworks natifs d'Apple pour OpenGL
    LIBS = -L/opt/homebrew/lib -lraylib -framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL
else
    # CONFIGURATION WINDOWS
    LIBS = -L$(INCLUDE_PATH) -lraylib -lopengl32 -lgdi32 -lwinmm
endif


all: build/$(TARGET)

build/$(TARGET): $(OBJ)
	@echo "Linking..."
	gcc $(OBJ) -o $@ $(LIBS)

# Règle générique pour compiler les fichiers .c en .o
build/%.o: %.c
	@mkdir -p $(dir $@)
	@echo "Compiling $<..."
	gcc $(CFLAGS) -c $< -o $@

# Créer le dossier build si nécessaire
build:
	mkdir -p build

run: all
	./build/$(TARGET)

clean:
	rm -rf build/

debug:
	@echo "Sources: $(SRC)"
	@echo "Objects: $(OBJ)"
