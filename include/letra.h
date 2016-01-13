#ifndef __Letra_h__
#define __Letra_h__

#include <set>
#include <vector>
#include <iostream>
using namespace std;

struct letra{
  char l; ///<< Caracter de la letra
  int n; ///<< Cantidad de veces que puede aparecer
  int puntos; ///<< Puntuación de la letra

  letra():l('\0'),n(0),puntos(-1){}
  letra(char let, int cant, int p):l(let),n(cant),puntos(p){}

  bool operator<(const letra& otra) const {
    return l < otra.l;
  }

  bool operator>(const letra& otra) const {
    return l > otra.l;
  }

  bool operator==(const letra& otra) const {
    return l == otra.l;
  }
  bool operator!=(const letra& otra) const {
    return l != otra.l;
  }
};

class Conjunto_Letras{
  set<letra> letras;

public:
  /**
  * @brief Obtiene el iterador a una letra
  */
  iterator Encuentra(char c);

  /**
  * @brief Obtiene el iterador constante a una letra
  */
  const_iterator Encuentra(char c) const;

  /**
  * @brief Operador de lectura
  */
  friend istream & operator>>(istream & is, Conjunto_Letras & C);

  /**
  * @brief Operador de escritura
  */
  friend ostream & operator<<(ostream & is, Conjunto_Letras & C);

  /**
  * @brief Añade una letra al conjunto
  */
  void Add(char l, int n, int puntos);
};

class Bolsa_Letras{
  vector<letra> letras;
public:

  /**
  * @brief Constructor por defecto
  */
  Bolsa_Letras(){}

  /**
  * @brief Construye una bolsa de tamaño tam a partir de c
  */
  Bolsa_Letras(Conjunto_Letras &c, int tam);
};

#endif
