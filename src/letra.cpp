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

  return puntuacion;
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

Bolsa_Letras::Bolsa_Letras(Conjunto_Letras &c) {
  for (Conjunto_Letras::const_iterator it = c.begin(); it != c.end(); ++it)
    letras.insert(letras.end(), (*it).n, *it);
}

int Bolsa_Letras::Cantidad() const {
  return letras.size();
}

vector<letra> Bolsa_Letras::MuestraAleatoria(int tam) const {
  vector<letra> salida(tam);
  for (int i = 0; i < tam; i++)
    salida[i] = letras[rand()%Cantidad()];

  return salida;
}

ostream& operator<<(ostream & os, const Bolsa_Letras & B) {
  for(Bolsa_Letras::const_iterator i = B.begin(); i != B.end(); ++i)
    os << (i != B.begin()?'\t':' ') << (*i).l << endl;

  return os;
}

Bolsa_Letras::const_iterator Bolsa_Letras::Encuentra(char c) const {
  Bolsa_Letras::const_iterator it = lower_bound(letras.begin(), letras.end(), letra(c, 0, 0));
  if (it != end() && (*it).l != c)
    return end();

  return it;
}
