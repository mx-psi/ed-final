// Autores: Pablo Baeyens Fernández y José Manuel Muñoz Fuentes

#ifndef __Letra_h__
#define __Letra_h__

#include <vector>
#include <string>
#include <iostream>
#include <ctime>
using namespace std;

/**
   @brief T.D.A. Letra
   \b Definición:
   Una instancia \e a del tipo de dato abstracto Letra es una tripleta (l,n,p)
   donde \e l es una letra, y \e n y \e p enteros positivos que representan
   la cantidad y puntuación.
   Para poder usar el tipo de dato Letra se debe incluir el fichero

   <tt>\#include letra.h</tt>

   El espacio requerido para el almacenamiento es O(1).
*/
struct letra{
  char l; ///<< Caracter de la letra
  int n; ///<< Cantidad de veces que puede aparecer
  int puntos; ///<< Puntuación de la letra

  letra():l('\0'),n(0),puntos(-1){}
  letra(char let, int cant, int p):l(let),n(cant),puntos(p){}

  /**
    * @brief Operador menor
    */
  bool operator<(const letra& otra) const { return l < otra.l; }

  /**
    * @brief Operador mayor
    */
  bool operator>(const letra& otra) const { return l > otra.l; }

  /**
    * @brief Operador de igualdad
    */
  bool operator==(const letra& otra) const { return l == otra.l; }

  /**
    * @brief Operador de desigualdad
    */
  bool operator!=(const letra& otra) const { return l != otra.l; }
};


/**
   @brief T.D.A. Conjunto_Letras
   \b Definición:
   Una instancia \e a del tipo de dato abstracto Conjunto_Letras es un
   conjunto de letras, sin repeticiones.
   Para poder usar el tipo de dato Conjunto_Letras se debe incluir el fichero

   <tt>\#include letra.h</tt>

   El espacio requerido para el almacenamiento es O(n), donde n es el número
   de letras.
*/
class Conjunto_Letras{
/**
  * @page repConjuntoLetras Rep del TDA Conjunto_Letras
  *
  * @section invConjuntoLetras Invariante de la representación
  *
  * El invariante de representación es que no hay letras cuyo
  * caracter coincida.
  *
  * @section faConjuntoLetras Función de abstracción
  *
  * Un objeto válido representa un conjunto de elementos del tipo
  * Letra.
  *
  */

private:
  vector<letra> letras;

public:
  typedef vector<letra>::iterator iterator;
  typedef vector<letra>::const_iterator const_iterator;

  /**
    * @brief Devuelve un iterador al primer elemento (constante)
    */
  const_iterator begin() const { return letras.begin(); }

  /**
    * @brief Devuelve un iterador al siguiente al último elemento (constante)
    */
  const_iterator end() const { return letras.end(); }

  /**
    * @brief Devuelve un iterador al primer elemento (no constante)
    */
  iterator begin() { return letras.begin(); }

  /**
    * @brief Devuelve un iterador al siguiente al último elemento (no constante)
    */
  iterator end() { return letras.end(); }

  /**
    * @brief Obtiene el iterador a una letra o donde debería insertarse
    */
  inline iterator DondeIria(char c);

  /**
    * @brief Obtiene el iterador constante a una letra o donde debería insertarse
    */
  inline const_iterator DondeIria(char c) const;

  /**
    * @brief Obtiene el iterador a una letra o end() si no está
    */
  iterator Encuentra(char c);

  /**
    * @brief Obtiene el iterador constante a una letra o end() si no está
    */
  const_iterator Encuentra(char c) const;

  /**
    * @brief Operador de lectura
    */
  friend istream & operator>>(istream & is, Conjunto_Letras & C);

  /**
    * @brief Operador de escritura
    */
  friend ostream & operator<<(ostream & os, const Conjunto_Letras & C);

  /**
    * @brief Añade una letra al conjunto
    */
  void Add(char l, int n, int puntos);

  /**
    * @brief Obtiene la puntuación de una palabra
    * @pre La palabra es correcta (todo caracter es una letra del conjunto)
    */
  unsigned Puntuacion(string palabra) const;
};

/**
   @brief T.D.A. Bolsa_Letras
   \b Definición:
   Una instancia \e a del tipo de dato abstracto Bolsa_Letras es un vector
   de letras, posiblemente repetidas.
   Para poder usar el tipo de dato Bolsa_Letras se debe incluir el fichero

   <tt>\#include letra.h</tt>

   El espacio requerido para el almacenamiento es O(n), donde n es el número
   de letras.
*/
class Bolsa_Letras{
/**
  * @page repBolsa Rep del TDA Bolsa_Letras
  *
  * @section invBolsa Invariante de la representación
  *
  * El invariante de representación es que, para todo par de
  * letras `a`, `b` de la bolsa cuyo caracter sea el mismo,
  * `a` y `b` son completamente idénticas (también coinciden en
  * el resto de sus datos) y toda letra `c` que ocupe una
  * posición intermedia a la de ambas será completamente idéntica
  * a estas.
  *
  * @section faBolsa Función de abstracción
  *
  * Un objeto válido representa un Conjunto_Letras en el que
  * cada letra `l` aparece tantas veces como indica `l.n`.
  *
  */

private:
  vector<letra> letras;

public:
  typedef vector<letra>::iterator iterator;
  typedef vector<letra>::const_iterator const_iterator;

  /**
    * @brief Devuelve un iterador al primer elemento (constante)
    */
  const_iterator begin() const { return letras.begin(); }

  /**
    * @brief Devuelve un iterador al siguiente al último elemento (constante)
    */
  const_iterator end() const { return letras.end(); }

  /**
    * @brief Devuelve un iterador al primer elemento (no constante)
    */
  iterator begin() { return letras.begin(); }

  /**
    * @brief Devuelve un iterador al siguiente al último elemento (no constante)
    */
  iterator end() { return letras.end(); }

  /**
    * @brief Constructor por defecto
    */
  Bolsa_Letras(){}

  /**
    * @brief Construye una bolsa completa a partir de c
    */
  Bolsa_Letras(Conjunto_Letras &c);

  /**
    * @brief Construye una bolsa de tamaño tam a partir de c
    */
  Bolsa_Letras(Conjunto_Letras &c, int tam);

  /**
    * @brief Devuelve el número de elementos
    */
  int Cantidad() const;

  /**
    * @brief Obtiene un subconjunto al azar
    */
  vector<letra> MuestraAleatoria(int tam) const;

  /**
    * @brief Localiza la primera aparición de una letra por su caracter o devuelve end() si no está
    */
  const_iterator Encuentra(char c) const;
};

#include "letra.cpp"

#endif
