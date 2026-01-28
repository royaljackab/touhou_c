TARGET = jeu
CFLAGS = -Wall

# Recherche récursive de tous les fichiers .c, en excluant ANY build/ ou include/ directories
SRC = $(shell find . -type f -name "*.c" ! -path "*/build/*" ! -path "*/include/*")

# Convertir les chemins sources en chemins objets dans le dossier build
OBJ = $(patsubst %.c, build/%.o, $(SRC))

INCLUDE_PATH = include
CFLAGS += -I$(INCLUDE_PATH)

# --- DÉTECTION AUTOMATIQUE DE L'OS ---
# On détecte le système d'exploitation pour ajuster les librairies
UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Linux)
    # CONFIGURATION LINUX
    # On lie raylib, OpenGL, Math, Pthread, et X11/Wayland
    LIBS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
else
    # CONFIGURATION WINDOWS
    # On garde ton ancienne config (assurant que libraylib.a est dans include/ ou lib/)
    LIBS = -Linclude -lraylib -lopengl32 -lgdi32 -lwinmm
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
