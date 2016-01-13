#include "../include/diccionario.h" // Ya lo quitaré

int Diccionario::size() const{
  int n = 0;

  for(Diccionario::const_iterator it = begin(); it != end(); it++)
    if(it->final)
      n++;

  return n;
}

/* TODO:
vector<string> Diccionario::PalabrasLongitud(int longitud) const{
}
*/

void Diccionario::Insertar(string palabra){
  Nodo n = datos.raiz(), ant;

  for(string::iterator it = palabra.begin(); it != palabra.end(); ++it){
    for(n = datos.hijomasizquierda(n); n != 0; ant = n, n = datos.hermanoderecha(n))
      if(n->c == *it)
        break;

    if(n == 0){
      datos.insertar_hermanoderecha(ant,*it);
      n = datos.hermanoderecha(ant);
    }
  }
}

istream & operator>>(istream & is, Diccionario & D){
  string palabra;

  while(is.good()){
    getline(is, palabra);
    D.Insertar(palabra);
  }

  return is;
}

bool Diccionario::Esta(string palabra) const{
  if(datos.raiz() == 0)
    return false;

  Nodo n = datos.hijomasizquierda(datos.raiz());
  int pos = 0;

  // Avanza por el árbol hasta la última letra
  while((pos < palabra.size() - 1) && n != 0){
    if(palabra[pos] == n->c){
      pos++;
      n = datos.hijomasizquierda(n);
    }
    else
      n = datos.hermanoderecha(n);
  }

  // Comprueba que la última letra sea final
  while(n != 0){
    if(palabra[pos] == n->c && n->final)
      return true;
    n = datos.hermanoderecha(n);
  }

  // n == 0
  return false;
}

ostream & operator<<(ostream & os, Diccionario & D){
  for(Diccionario::const_iterator it = begin(); it != end(); it++)
    os << it->cad << "\n";
}

iterator& Diccionario::iterator::operator++(){
  int ant, post;

  ant = it.getlevel();

  // Avanza hasta la siguiente palabra válida
  while(it != 0 && !(it->final))
    it++;

  post = it.getlevel();


  // Actualiza la cadena (C++11)
  if(post >= ant)
    it.cad.pop_back();
  else
    for(int i = 0; i < post-ant; i++)
      it.cad.pop_back();

  it.cad.push_back(it->c);

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
  if(beg != end())
    beg++; //Avanza hasta la primera palabra válida
  return beg;
}

iterator Diccionario::end(){
  iterator end;
  end.it = datos.end();
  end.cad = "";
  return end;
}
