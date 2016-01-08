#ifndef __Diccionario_h__
#define __Diccionario_h__

#include "ArbolGeneral.h"
#include <vector>
#include <string>
using namespace std;

struct info{
  char c; ///<< caracter almacenado
  bool final; ///<< indica si es final de palabra
  info():c('\0'),final(false){}
  info(char car, bool f):c(car),final(f){}
};

class Diccionario{
  ArbolGeneral<info> datos;
public:
  int size() const;
  vector<string> PalabrasLongitud(int longitud);
  bool Esta(string palabra);
  friend istream & operator>>(istream & is, Diccionario & D);
  friend ostream & operator<<(ostream & is, Diccionario & D);

  class iterator{
    ArbolGeneral<info>::iter_preorden it;
    string cad;
  public:
    iterator();
    string operator *();
    iterator &operator++();
    bool operator==(const iterator &i);
    bool operator!=(const iterator &i);
    friend class Diccionario;
  };

  iterator begin();
  iterator end();
};

#endif
