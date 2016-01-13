int Diccionario::size() const{
  int n = 0;
  for(ArbolGeneral<info>::const_iter_preorden it = datos.begin(); it != datos.end(); ++it)
    if((*it).final)
      n++;
  return n;
}

/* TODO:
vector<string> Diccionario::PalabrasLongitud(int longitud) const{
}
*/

void Diccionario::Insertar(string palabra){
  ArbolGeneral<info>::Nodo n = datos.raiz(), ant;

  for(unsigned i = 0; i < palabra.length(); ++i){
    for(n = datos.hijomasizquierda(n); n != 0; ant = n, n = datos.hermanoderecha(n))
      if(datos.etiqueta(n).c == palabra[i])
        break;

    if(n == 0){
      info c(palabra[i],i == palabra.length() -1);
      ArbolGeneral<info> a(c);
      datos.insertar_hermanoderecha(ant,a);
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
  int ant, post;

  ant = it.getlevel();

  // Avanza hasta la siguiente palabra válida
  while(it != 0 && !(*it).final)
    ++it;

  post = it.getlevel();


  // Actualiza la cadena (C++11)
  if(post >= ant)
    cad.pop_back();
  else
    for(int i = 0; i < post-ant; i++)
      cad.pop_back();

  cad.push_back((*it).c);

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