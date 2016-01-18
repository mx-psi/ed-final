Conjunto_Letras::iterator Conjunto_Letras::DondeIria(char c) {
  return lower_bound(letras.begin(), letras.end(), letra(c, 0, 0));
}

Conjunto_Letras::const_iterator Conjunto_Letras::DondeIria(char c) const {
  return lower_bound(letras.begin(), letras.end(), letra(c, 0, 0));
}

Conjunto_Letras::iterator Conjunto_Letras::Encuentra(char c) {
  iterator it = DondeIria(c);
  if (it != end() && (*it).l != c)
    return end();

  return it;
}

Conjunto_Letras::const_iterator Conjunto_Letras::Encuentra(char c) const {
  const_iterator it = DondeIria(c);
  if (it != end() && (*it).l != c)
    return end();

  return it;
}

void Conjunto_Letras::Add(char l, int n, int puntos) {
  letras.insert(DondeIria(l), letra(l, n, puntos));
}

unsigned Conjunto_Letras::Puntuacion(string palabra) const{
  unsigned puntuacion = 0;
  for (string::const_iterator it = palabra.begin(); it != palabra.end(); ++it)
    puntuacion += Encuentra(*it)->puntos;
}


// TODO: ¿Debería borrarse previamente el contenido de C?
istream& operator>>(istream & is, Conjunto_Letras & C) {
  is.ignore(256, '\n');
  char l;
  int n, p;
  while(is.good()) {
    is.get(l);
    l = tolower(l);
    is.ignore();
    is >> n;
    is.ignore();
    is >> p;
    is.ignore();
    C.Add(l, n, p);
  }
  return is;
}

ostream& operator<<(ostream & os, const Conjunto_Letras & C) {
  os << "#Letra Cantidad Puntos";
  for (Conjunto_Letras::const_iterator i = C.begin(); i != C.end(); ++i)
    os << '\n' << (char) toupper((*i).l) << '\t' << (*i).n << '\t' << (*i).puntos;

  return os;
}

bool Bolsa_Letras::Correcta(string palabra) const{
  vector<letra> v = letras;
  vector<letra>::iterator v_it;

  for(string::const_iterator s_it = palabra.begin(); s_it != palabra.end(); ++s_it){
    for(v_it = v.begin(); v_it != v.end(); ++v_it)
      if(v_it->l == *s_it){
        if(v_it->n > 0)
          v_it->n--;
        else
          return false;
        break;
      }

    if(v_it == v.end())
      return false;
  }
  return true;
}

ostream& operator<<(ostream & os, const Bolsa_Letras & B) {
  for(Bolsa_Letras::const_iterator i = B.begin(); i != B.end(); ++i)
    os << (i != B.begin()?'\t':' ') << (*i).l << endl;

  return os;
}

bool BolsaLetras::Esta(letra l) const {
  return letras.Encuentra(l.c) != letras.end();
}
