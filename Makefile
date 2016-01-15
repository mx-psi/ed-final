SRC = src
INC = include
OBJ = obj
BIN = bin
CXX = g++
CPPFLAGS = -I$(INC) -I$(SRC) -std=c++11 -Wall -g -pedantic -O3

all:

# ************ Generación de documentación ******************
documentacion:
	doxygen doc/doxys/Doxyfile


# ************ Compilación de módulos ************

$(BIN)/testdiccionario: $(SRC)/testdiccionario.cpp $(INC)/diccionario.h
	$(CXX) $(CPPFLAGS) -o $@ $^

$(INC)/diccionario.h: $(SRC)/diccionario.cpp $(INC)/ArbolGeneral.h $(SRC)/ArbolGeneral.cpp

$(OBJ)/%.o: $(SRC)/%.cpp $(INC)/%.h
	$(CXX) $(CPPFLAGS) -c $< -o $@


# ************ Limpieza ************
clean :
	-rm $(OBJ)/* $(SRC)/*~ $(INC)/*~ ./*~

mrproper : clean
	-rm $(BIN)/* doc/html/*
