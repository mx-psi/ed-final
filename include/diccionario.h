#ifndef __Diccionario_h__
#define __Diccionario_h__

#include "ArbolGeneral.h"
#include "letra.h"
using namespace std;

/**
  *@brief info
  * En cada  estructura \e info se almacena una letra y si esta es final.
  */
struct info{
  char c; ///<< caracter almacenado
  bool final; ///<< indica si es final de palabra
  info():c('\0'),final(false){}
  info(char car, bool f):c(car),final(f){}
};


/**
   @brief T.D.A. Diccionario

   \b Definición:
   Una instancia \e a del tipo de dato abstracto Diccionario es un conjunto
   de palabras válidas.

   El espacio requerido para el almacenamiento es, en el peor caso, O(n)
   donde n es el número de palabras.
*/
class Diccionario{
  /**
    * @brief Arbol de datos
    *
    * Éste árbol guarda las palabras del diccionario caracter a caracter
    * de forma ordenada.
    */
  ArbolGeneral<info> datos;

  /**
    * @brief Método auxiliar para PalabrasLongitud
    * @param longitud: Longitud de las palabras
    * @param n: Nodo desde el que se empiezan a buscar las palabras
    * @param v: Vector donde se guardan las palabras
    * @pre longitud es un entero positivo
    * @see PalabrasLongitud
    */
  void PalabrasLong(int longitud, ArbolGeneral<info>::Nodo n, vector<string> &v) const;
public:
  /**
    * @brief Constructor por defecto
    */
  Diccionario():datos(info()){}

  /**
    * @brief Devuelve el número de palabras válidas del diccionario.
    * @return Número de palabras
    */
  int size() const;

  /**
    * @brief Obtiene las palabras de una cierta longitud
    * @param longitud: Longitud de las palabras
    * @pre longitud es un entero positivo
    * @return vector con las palabras de longitud `longitud`
    */
  vector<string> PalabrasLongitud(int longitud) const;

  /**
    * @brief Obtiene las mejores soluciones
    * @param bl: Letras que se pueden escoger
    * @param modo: Modo de comparación
    * @pre modo es un modo válido
    * @return vector con las mejores soluciones
    */
  vector<string> MejoresSoluciones(const Bolsa_Letras &bl, string modo) const;

  /**
    * @brief Indica si una palabra está en el diccionario
    * @param palabra: La palabra a comprobar
    * @return Si la palabra está en el diccionario
    */
  bool Esta(string palabra) const;

  /**
    * @brief Inserta una palabra en el diccionario
    * @param palabra: Palabra a insertar
    */
  void Insertar(string palabra);

  /**
    * @brief Lee a un flujo de entrada un diccionario
    * @param is: flujo de entrada
    * @param D: Diccionario
    * @return Referencia al flujo
    */
  friend istream & operator>>(istream & is, Diccionario & D);

  /**
    * @brief Escribe un diccionario en un flujo de salida
    * @param os: flujo de entrada
    * @param D: Diccionario
    * @return Referencia al flujo
    */
  friend ostream & operator<<(ostream & os, Diccionario & D);

  class iterator{

    /**
      * @brief Un iterador preorden sobre un caracter final
      */
    ArbolGeneral<info>::iter_preorden it;

    /**
      * @brief Cadena formada por los caracteres del recorrido a la raiz
      */
    string cad;

  public:

    /**
      * @brief Constructor por defecto del iterador
      */
    iterator(){}

    /**
      * @brief Operador de acceso
      * @return Palabra a la que apunta el iterador
      */
    inline string operator *(){return cad;}

    /**
      * @brief Operador de incremento
      * @pre El iterador no está en la posición final
      * @return Referencia al iterador
      *
      * Avanza hasta la siguiente palabra (siguiente caracter válido).
      */
    iterator &operator++();

    /**
      * @brief Operador de comparación
      * @param i: iterador a comparar
      * @return Si son iguales
      */
    bool operator==(const iterator &i);

    /**
      * @brief Operador de comparación
      * @param i: iterador a comparar
      * @return Si son distintos
      */
    bool operator!=(const iterator &i);

    friend class Diccionario;
  };

  /**
    * @brief Iterador a la primera palabra válida
    * @pre Existe al menos una palabra válida
    * @return El iterador
    */
  iterator begin();

  /**
    * @brief Iterador al siguiente del último
    * @return El iterador
    */
  iterator end();
};

#include "diccionario.cpp"

#endif
