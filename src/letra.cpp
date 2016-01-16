Conjunto_Letras::iterator Conjunto_Letras::Encuentra(char c) {
  iterator pos = lower_bound(letras.begin(), letras.end(), letra(c, 0, 0));
  if ((*pos).l != c)
    return letras.end();

  return pos;
}

Conjunto_Letras::const_iterator Conjunto_Letras::Encuentra(char c) const {
  const_iterator pos = lower_bound(letras.begin(), letras.end(), letra(c, 0, 0));
  if ((*pos).l != c)
    return letras.end();

  return pos;
}

// TODO: ¿Debería borrarse previamente el contenido de C?
// TODO: Es posible que falle al final del fichero
istream& operator>>(istream & is, Conjunto_Letras & C) {
  is.ignore(256, '\n');
  char l;
  int n, p;
  while(is) {
    is.get(l);
    is.ignore();
    is >> n;
    is.ignore();
    is >> p;
    is.ignore();
    Conjunto_Letras.Add(letra(l, n, p));
  }
  return is;
}

ostream& operator<<(ostream & os, const Conjunto_Letras & C) {
  os << "#Letra Cantidad Puntos";
  for (Conjunto_Letras::const_iterator i = C.begin(); i != C.end(); ++i)
    os << '\n' << (*i).l << '\t' << (*i).n << '\t' << (*i).puntos;

  return os;
}