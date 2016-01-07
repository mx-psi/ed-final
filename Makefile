SRC = src
INC = include
OBJ = obj
BIN = bin
CXX = g++
CPPFLAGS = -Wall -g -pedantic -I$(INC)

all:

# ************ Generación de documentación ******************
documentacion:
	doxygen doc/doxys/Doxyfile


# ************ Compilación de módulos ************
$(BIN)/%: $(SRC)/%.cpp
	$(CXX) $(CPPFLAGS) -o $@ $^

$(OBJ)/%.o: $(SRC)/%.cpp $(INC)/%.h
	$(CXX) $(CPPFLAGS) -c $< -o $@


# ************ Limpieza ************
clean :
	-rm $(OBJ)/* $(SRC)/*~ $(INC)/*~ ./*~

mrproper : clean
	-rm $(BIN)/* doc/html/*
