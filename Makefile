SRC = src
INC = include
OBJ = obj
BIN = bin
CXX = g++
CPPFLAGS = -I$(INC) -I$(SRC) -std=c++11 #-Wall -g -pedantic -O3

all: $(BIN)/testdiccionario

# ************ Generación de documentación ******************
documentacion:
	doxygen doc/doxys/Doxyfile


# ************ Compilación de módulos ************

$(BIN)/%: $(OBJ)/%.o
	$(CXX) $(CPPFLAGS) -o $@ $^

$(OBJ)/%.o: $(SRC)/%.cpp
	$(CXX) $(CPPFLAGS) -c $< -o $@


# ************ Limpieza ************
clean :
	-rm $(OBJ)/* $(SRC)/*~ $(INC)/*~ ./*~

mrproper : clean
	-rm $(BIN)/* doc/html/*
