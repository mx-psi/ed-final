#include "../include/diccionario.h" // Ya lo quitaré

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

istream & operator>>(istream & is, Diccionario & D){

}
*/

bool Diccionario::Esta(string palabra){
  if(datos.raiz() == 0)
    return false;

  Nodo n = datos.hijomasizquierda(datos.raiz());
  int pos = 0;

  // Avanza por el árbol hasta la última letra
  while((pos < palabra.length() - 1) && n != 0){
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

//TODO: ¿Es más eficiente usando la pila o no hace falta?
void Diccionario::iterator::ConstruyeCadena(){
  ArbolGeneral<info>::iter_preorden p;
  stack<char> st;

  for(p = it; p != 0; p = datos.padre(p))
    st.push(p->c);

  cad.clear();
  while(!st.empty()){
    cad.push_back(st.top());
    st.pop();
  }
}

iterator& Diccionario::iterator::operator++(){
  while(it != 0 && !(it->final))
    it++;

  if(it->final)
    it.ConstruyeCadena();
  else
    it.cad = "";

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
