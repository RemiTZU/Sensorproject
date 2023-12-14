# Compilateur C++
CXX = g++

# Options de compilation
CXXFLAGS = -Wall -Werror -pedantic -fpic -g -fpermissive

# Répertoire source (où se trouvent les fichiers .cpp)
SRC_DIR = .

# Répertoire de sortie (où seront générés les fichiers objets et l'exécutable)
BUILD_DIR = build

# Liste des fichiers source C++
SOURCES_CPP = $(wildcard $(SRC_DIR)/*.cpp)

# Noms génériques pour les fichiers objets (un par fichier source)
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SOURCES_CPP))

# Nom de l'exécutable final
EXECUTABLE = main

all: $(BUILD_DIR) $(EXECUTABLE)

# Règle pour créer le répertoire de build
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Règle pour compiler les fichiers objets
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -I$(SRC_DIR) -c $< -o $@ 

# Règle pour générer l'exécutable
$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $@ -pthread

clean:
	rm -rf $(BUILD_DIR) $(EXECUTABLE)

.PHONY: all clean