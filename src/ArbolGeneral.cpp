// Esta línea es para que el editor me muestre errores sin compilar
#include "../include/ArbolGeneral.h"

template <class T>
void ArbolGeneral<T>::destruir(nodo * n){
  if(n != 0){
    nodo* a_borrar = n->izqda, sig;

    while(a_borrar != 0){
      sig = a_borrar->drcha;
      destruir(a_borrar);
      a_borrar = sig;
    }

    delete n;
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
  if(n1 == 0 && n2 == 0) //Ambos nulos
    return true;

  if(n1 == 0 || n2 == 0) //Uno nulo y el otro no
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
  laraiz->drcha = 0;
  laraiz->izqda = 0;
  laraiz->padre = 0;
}

template <class T>
ArbolGeneral<T>::ArbolGeneral (const ArbolGeneral<T>& v){
  copiar(laraiz, v.laraiz);
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
  return n->izqda;
}

template <class T>
typename ArbolGeneral<T>::Nodo ArbolGeneral<T>::hermanoderecha(const typename ArbolGeneral<T>::Nodo n) const{
  return n->drcha;
}

template <class T>
typename ArbolGeneral<T>::Nodo ArbolGeneral<T>::padre(const typename ArbolGeneral<T>::Nodo n) const{
  return n->padre;
}

template <class T>
T& ArbolGeneral<T>::etiqueta(const typename ArbolGeneral<T>::Nodo n){
  return n->etiqueta;
}

template <class T>
const T& ArbolGeneral<T>::etiqueta(const typename ArbolGeneral<T>::Nodo n) const{
  return n->etiqueta;
}
