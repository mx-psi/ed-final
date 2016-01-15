#include "../include/diccionario.h"

int Diccionario::size() const{
  int n = 0;
  for(ArbolGeneral<info>::const_iter_preorden it = datos.begin(); it != datos.end(); ++it)
    if((*it).final)
      n++;
  return n;
}

void Diccionario::PalabrasLong(int longitud, ArbolGeneral<info>::Nodo n, vector<string> &v) const{
 if(longitud == 1){
   for(ArbolGeneral<info>::Nodo m = datos.hijomasizquierda(n); m != 0; m = datos.hermanoderecha(m))
    if(datos.etiqueta(m).final){
      string palabra;

      for(ArbolGeneral<info>::Nodo k = m; datos.padre(k) != 0; k = datos.padre(k))
        palabra = datos.etiqueta(k).c + palabra;

      v.push_back(palabra);
    }
 }
 else{
   for(ArbolGeneral<info>::Nodo m = datos.hijomasizquierda(n); m != 0; m = datos.hermanoderecha(m))
    PalabrasLong(longitud -1, m, v);
 }
}

vector<string> Diccionario::PalabrasLongitud(int longitud) const{
  vector<string> v;
  PalabrasLong(longitud, datos.raiz(), v);
  return v;
}

void Diccionario::Insertar(string palabra){
  ArbolGeneral<info>::Nodo n = datos.raiz(), ant;
  bool encontrado = false;
  for(unsigned i = 0; i < palabra.length(); ++i){
    ant = n;
    n = datos.hijomasizquierda(n);

    if(n == 0){
      info c(palabra[i],i == palabra.length() -1);
      ArbolGeneral<info> a(c);
      datos.insertar_hijomasizquierda(ant,a);
      n = datos.hijomasizquierda(ant);
    }
    else{
      encontrado = false;
      while(n != 0 && !encontrado){
        if(datos.etiqueta(n).c == palabra[i]){
          encontrado = true;
          if(i == palabra.length() -1)
            datos.etiqueta(n).final = true;
        }

        if(!encontrado){
          ant = n;
          n = datos.hermanoderecha(n);
        }
      }

      if(n == 0){
        info c(palabra[i],i == palabra.length() -1);
        ArbolGeneral<info> a(c);
        datos.insertar_hermanoderecha(ant,a);
        n = datos.hermanoderecha(ant);
      }
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

  ArbolGeneral<info>::Nodo n = datos.hijomasizquierda(datos.raiz());
  int pos = 0;

  // Avanza por el árbol hasta la última letra
  while((pos < palabra.size() - 1) && n != 0){
    if(palabra[pos] == datos.etiqueta(n).c){
      pos++;
      n = datos.hijomasizquierda(n);
    }
    else
      n = datos.hermanoderecha(n);
  }

  // Comprueba que la última letra sea final
  while(n != 0){
    if(palabra[pos] == datos.etiqueta(n).c && datos.etiqueta(n).final)
      return true;
    n = datos.hermanoderecha(n);
  }

  // n == 0
  return false;
}

Diccionario::iterator& Diccionario::iterator::operator++(){
  int ant, post = it.getlevel();

  // Avanza hasta la siguiente palabra válida
  do {
    ant = post;
    ++it;
    post = it.getlevel();

    if(it != 0){
      for(int i = 0; i <= ant-post; i++)
        cad.pop_back();

      cad.push_back((*it).c);
    }
  }while (it != 0 && !(*it).final);

  return *this;
}

bool Diccionario::iterator::operator==(const iterator &i){
  return it == i.it;
}

bool Diccionario::iterator::operator!=(const iterator &i){
  return it != i.it;
}

Diccionario::iterator Diccionario::begin(){
  iterator beg;
  beg.it = datos.begin();
  if(beg != end())
    ++beg; //Avanza hasta la primera palabra válida
  return beg;
}

Diccionario::iterator Diccionario::end(){
  iterator end;
  end.it = datos.end();
  end.cad = "";
  return end;
}

ostream & operator<<(ostream & os, Diccionario & D){
  for(Diccionario::iterator it = D.begin(); it != D.end(); ++it)
    os << *it << "\n";
  return os;
}
