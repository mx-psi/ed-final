#include "../include/diccionario.h"

int Diccionario::size() const{
  int n = 0;

  for(Diccionario::const_iterator it = begin(); it != end(); it++)
    if(it->final)
      n++;

  return n;
}

/* TODO:
vector<string> Diccionario::PalabrasLongitud(int longitud){
}

bool Diccionario::Esta(string palabra){
}

istream & operator>>(istream & is, Diccionario & D){

}
*/

ostream & operator<<(ostream & os, Diccionario & D){
  for(Diccionario::const_iterator it = begin(); it != end(); it++)
    os << it->cad << "\n";
}

//TODO: No sé si las comparaciones con 0 son válidas.
iterator& Diccionario::iterator::operator++(){
  // Avanza hasta la siguiente palabra válida
  while(it != 0 && !(it->final))
    it++;

  // Si es caracter final, construye la cadena
  ArbolGeneral<info>::iter_preorden p = it.it;
  it.cad = "";

  while(p != 0){
    it.cad = p->c + it.cad;
    p = p->padre;
  }

  return *this;
}

bool Diccionario::iterator::operator==(const iterator &i){
  return i.it == it;
}

bool Diccionario::iterator::operator!=(const iterator &i){
  return i.it != it;
}

iterator Diccionario::begin(){
  iterator beg;
  beg.it = datos.begin();
  beg++; //Avanza hasta la primera palabra válida
  return beg;
}

iterator Diccionario::end(){
  iterator end;
  end.it = datos.end();
  end.cad = "";
  return end;
}
