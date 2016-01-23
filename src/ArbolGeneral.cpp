template <class T>
void ArbolGeneral<T>::destruir(nodo * n){
  if(n != 0){
    destruir(n->izqda);
    destruir(n->drcha);
    delete n;
  }
}

template <class T>
void ArbolGeneral<T>::copiar(nodo *& dest, nodo * orig){
  destruir(dest);

  if(orig == 0)
    dest = 0;
  else{
    dest = new ArbolGeneral<T>::nodo;
    dest->etiqueta = orig->etiqueta;
    copiar(dest->izqda, orig->izqda);
    copiar(dest->drcha, orig->drcha);
    if (dest->izqda != 0)
      dest->izqda->padre = dest;
    if (dest->drcha != 0)
      dest->drcha->padre = dest;
  }
}

template <class T>
int ArbolGeneral<T>::contar(const nodo * n) const{
  if(n == 0)
    return 0;

  int num = 1;
  nodo* a_contar = n->izqda;

  while(a_contar != 0){
    num += contar(a_contar);
    a_contar = a_contar->drcha;
  }

  return num;
}

template <class T>
bool ArbolGeneral<T>::soniguales(const nodo * n1, const nodo * n2) const{
  if(n1 == 0 && n2 == 0) // Ambos nulos
    return true;

  if(n1 == 0 || n2 == 0) // Uno nulo y el otro no
    return false;

  bool iguales  = n1->etiqueta == n2->etiqueta;
  nodo *a_comp1 = n1->izqda, *a_comp2 = n2->izqda;

  while(iguales && a_comp1 != 0 || a_comp2 != 0){
    iguales ^= soniguales(a_comp1, a_comp2);

    if(a_comp1 != 0) a_comp1  = a_comp1->drcha;
    if(a_comp2 != 0) a_comp2  = a_comp2->drcha;
  }

  return iguales;
}

template <class T>
ArbolGeneral<T>::ArbolGeneral(){
  laraiz = 0;
}

template <class T>
ArbolGeneral<T>::ArbolGeneral(const T& e){
  laraiz = new nodo;
  laraiz->etiqueta = e;
}

template <class T>
ArbolGeneral<T>::ArbolGeneral (const ArbolGeneral<T>& v){
  copiar(laraiz, v.raiz());
}

template <class T>
ArbolGeneral<T>::~ArbolGeneral(){
  destruir(laraiz);
}

template <class T>
ArbolGeneral<T>& ArbolGeneral<T>::operator=(const ArbolGeneral<T> &v){
  if(this != &v){
  destruir(laraiz);
  copiar(laraiz,v.laraiz);
  }
}

template <class T>
void ArbolGeneral<T>::AsignaRaiz(const T& e){
  ArbolGeneral<T> nuevo(e);
  *this = nuevo;
}

typedef struct nodo * Nodo;

template <class T>
typename ArbolGeneral<T>::Nodo ArbolGeneral<T>::raiz() const{
  return laraiz;
}

template <class T>
typename ArbolGeneral<T>::Nodo ArbolGeneral<T>::hijomasizquierda(const typename ArbolGeneral<T>::Nodo n) const{
  assert(n != 0);
  return n->izqda;
}

template <class T>
typename ArbolGeneral<T>::Nodo ArbolGeneral<T>::hermanoderecha(const typename ArbolGeneral<T>::Nodo n) const{
  assert(n != 0);
  return n->drcha;
}

template <class T>
typename ArbolGeneral<T>::Nodo ArbolGeneral<T>::padre(const typename ArbolGeneral<T>::Nodo n) const{
  assert(n != 0);
  return n->padre;
}

template <class T>
T& ArbolGeneral<T>::etiqueta(const typename ArbolGeneral<T>::Nodo n){
  assert(n != 0);
  return n->etiqueta;
}

template <class T>
const T& ArbolGeneral<T>::etiqueta(const typename ArbolGeneral<T>::Nodo n) const{
  assert(n != 0);
  return n->etiqueta;
}

template <class T>
int ArbolGeneral<T>::nivel(const typename ArbolGeneral<T>::Nodo n) const{
  typename ArbolGeneral<T>::Nodo r = n;
  int s = -1;
  while (r != 0) {
    r = padre(r);
    ++s;
  }
  return s;
}

template <class T>
void ArbolGeneral<T>::asignar_subarbol(const ArbolGeneral<T>& orig, const typename ArbolGeneral<T>::Nodo nod){
 orig.copiar(laraiz,nod); // laraiz se destruye en copiar
}

template <class T>
void ArbolGeneral<T>::podar_hijomasizquierda(typename ArbolGeneral<T>::Nodo n, ArbolGeneral<T>& dest){
  dest = n->izqda;
  n->izqda = n->izqda->drcha;
}

template <class T>
void ArbolGeneral<T>::podar_hermanoderecha(typename ArbolGeneral<T>::Nodo n, ArbolGeneral<T>& dest){
  dest = n->drcha;
  n->drcha = n->drcha->drcha;
}

template <class T>
void ArbolGeneral<T>::insertar_hijomasizquierda(typename ArbolGeneral<T>::Nodo n, ArbolGeneral<T>& rama){
  rama.laraiz->drcha = n->izqda;
  rama.laraiz->padre = n;
  n->izqda = rama.laraiz;
  rama.laraiz = 0;
}

template <class T>
void ArbolGeneral<T>::insertar_hermanoderecha(typename ArbolGeneral<T>::Nodo n, ArbolGeneral<T>& rama){
  rama.laraiz->drcha = n->drcha;
  rama.laraiz->padre = n->padre;
  n->drcha = rama.laraiz;
  rama.laraiz = 0;
}

template <class T>
void ArbolGeneral<T>::clear(){
  destruir(laraiz);
  laraiz = 0;
}

template <class T>
int ArbolGeneral<T>::size() const{
  return contar(laraiz);
}

template <class T>
bool ArbolGeneral<T>::empty() const{
  return laraiz == 0;
}

template <class T>
bool ArbolGeneral<T>::operator==(const ArbolGeneral<T>& v) const{
  return soniguales(laraiz, v.laraiz);
}

template <class T>
bool ArbolGeneral<T>::operator!=(const ArbolGeneral<T>& v) const{
  return !soniguales(laraiz, v.laraiz);
}

/* Iterador preorden no constante */

template <class T>
ArbolGeneral<T>::iter_preorden::iter_preorden():it(0),raiz(0),level(-1){}

template <class T>
T & ArbolGeneral<T>::iter_preorden::operator*(){
  return it->etiqueta;
}

template <class T>
int ArbolGeneral<T>::iter_preorden::getlevel() const{
  return level;
}

template <class T>
typename ArbolGeneral<T>::iter_preorden & ArbolGeneral<T>::iter_preorden::operator ++(){
  if (it->izqda != 0){
    it = it->izqda;
    level++;
  }
  else {
    while (it->padre != 0 && it->drcha == 0){
      it = it->padre;
      level--;
    }
    if (it->padre == 0)
      it = 0;
    else
      it = it->drcha;
  }
  return *this;
}

template <class T>
bool ArbolGeneral<T>::iter_preorden::operator==(const typename ArbolGeneral<T>::iter_preorden &i) const{
  return (raiz == i.raiz || i.raiz == 0) && it == i.it;
}

template <class T>
bool ArbolGeneral<T>::iter_preorden::operator!=(const typename ArbolGeneral<T>::iter_preorden &i) const{
  return (raiz != i.raiz && i.raiz != 0) || it != i.it;
}

/* Iterador preorden constante */

template <class T>
ArbolGeneral<T>::const_iter_preorden::const_iter_preorden():it(0),raiz(0),level(-1){}

template <class T>
const T & ArbolGeneral<T>::const_iter_preorden::operator*(){
  return it->etiqueta;
}

template <class T>
int ArbolGeneral<T>::const_iter_preorden::getlevel()const{
  return level;
}

template <class T>
typename ArbolGeneral<T>::const_iter_preorden & ArbolGeneral<T>::const_iter_preorden::operator ++(){
  if (it->izqda != 0){
    it = it->izqda;
    level++;
  }
  else if (it->drcha != 0)
    it = it->drcha;

  else {
    while (it->padre != 0 && it->padre->drcha == 0){
      it = it->padre;
      level--;
    }
    if (it->padre == 0)
      it = 0;
    else
      it = it->padre->drcha;
  }
  return *this;
}

template <class T>
bool ArbolGeneral<T>::const_iter_preorden::operator==(const typename ArbolGeneral<T>::const_iter_preorden &i) const{
  return (raiz == i.raiz || i.raiz == 0) && it == i.it;
}

template <class T>
bool ArbolGeneral<T>::const_iter_preorden::operator!=(const typename ArbolGeneral<T>::const_iter_preorden &i) const{
  return (raiz != i.raiz && i.raiz != 0) || it != i.it;
}

/* Begin y end */

template <class T>
typename ArbolGeneral<T>::iter_preorden ArbolGeneral<T>::begin(){
  iter_preorden it;
  it.it = laraiz;
  it.raiz = laraiz;
  it.level = 0;
  return it;
}

template <class T>
typename ArbolGeneral<T>::const_iter_preorden ArbolGeneral<T>::begin()const{
  const_iter_preorden it;
  it.it = laraiz;
  it.raiz = laraiz;
  it.level = 0;
  return it;
}

template <class T>
typename ArbolGeneral<T>::iter_preorden ArbolGeneral<T>::end(){
  iter_preorden it;
  return it;
}

template <class T>
typename ArbolGeneral<T>::const_iter_preorden ArbolGeneral<T>::end() const{
  const_iter_preorden it;
  return it;
}
