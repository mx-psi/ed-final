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

// TODO: ¿Debería borrarse previamente el contenido de C?
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
    C.Add(l, n, p);
  }
  return is;
}

ostream& operator<<(ostream & os, const Conjunto_Letras & C) {
  os << "#Letra Cantidad Puntos";
  for (Conjunto_Letras::const_iterator i = C.begin(); i != C.end(); ++i)
    os << '\n' << (*i).l << '\t' << (*i).n << '\t' << (*i).puntos;

  return os;
}