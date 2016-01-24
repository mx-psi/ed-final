// Autores: Pablo Baeyens Fernández y José Manuel Muñoz Fuentes

#ifndef __Diccionario_h__
#define __Diccionario_h__

#include "ArbolGeneral.h"
#include "letra.h"
using namespace std;

/**
  * @brief info
  * En cada estructura \e info se almacena una letra y si esta es final.
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
  * @page repDiccionario Rep del TDA Diccionario
  *
  * @section invDiccionario Invariante de la representación
  *
  * El invariante de representación es que todo nodo sin hijos
  * es necesariamente fin de palabra y no hay nodos hijos del
  * mismo padre cuyo caracter sea el mismo.
  *
  * @section faDiccionario Función de abstracción
  *
  * Un objeto válido `d` representa un árbol cuyos nodos
  * son las letras de cada palabra. Dos palabras cuyas
  * `n` primeras letras sean las mismas tendrán en común
  * los `n` primeros nodos.
  *
  */

private:
  /**
    * @brief Árbol de datos
    *
    * Este árbol guarda las palabras del diccionario caracter a caracter
    * de forma ordenada.
    */
  ArbolGeneral<info> datos;

  /**
    * @brief Método auxiliar para PalabrasLongitud
    * @param longitud Longitud de las palabras
    * @param n Nodo desde el que se empiezan a buscar las palabras
    * @param v Vector donde se guardan las palabras
    * @pre longitud es mayor que cero
    * @see PalabrasLongitud
    */
  void PalabrasLong(int longitud, ArbolGeneral<info>::Nodo n, vector<string> &v) const;

  /**
    * @brief Método auxiliar para MejoresSoluciones
    * @param disponibles Letras que se pueden escoger
    * @param cl Puntero a conjunto de letras con puntuaciones (si se quiere longitud, debe ser 0)
    * @param prev Nodo padre de los nodos que deben explorarse
    * @param salida Referencia donde se guardan las soluciones
    * @param mejor Referencia a la mayor puntuación encontrada
    * @see MejoresSoluciones
    */
  void RellenaSoluciones(const vector<letra> &disponibles, const Conjunto_Letras* cl, ArbolGeneral<info>::Nodo prev, vector<string>& salida, int &mejor) const;

public:
  /**
    * @brief Constructor por defecto
    */
  Diccionario():datos(info()){}

  /**
    * @brief Devuelve el número de palabras válidas del diccionario
    * @return Número de palabras
    */
  int size() const;

  /**
    * @brief Obtiene las palabras de una cierta longitud
    * @param longitud Longitud de las palabras
    * @pre longitud es mayor que cero
    * @return vector con las palabras de longitud `longitud`
    */
  vector<string> PalabrasLongitud(int longitud) const;

  /**
    * @brief Obtiene las mejores soluciones
    * @param disponibles Letras que se pueden escoger
    * @param cl Puntero a conjunto de letras con puntuaciones (si se quiere longitud, puede omitirse)
    * @pre disponibles está ordenado
    * @return Un vector con las mejores soluciones
    */
  vector<string> MejoresSoluciones(const vector<letra> &disponibles, const Conjunto_Letras* cl=0) const;

  /**
    * @brief Obtiene la cadena de una palabra
    * @param n Nodo en el que termina la palabra
    *
    * Obtiene la cadena formada por un nodo y su
    * ascendencia hasta la raíz. Si se usa en un
    * nodo en el que concluye una palabra, se obtiene
    * esa palabra. Puede usarse en un nodo en el que
    * no termina ninguna palabra.
    */
  string Get(const ArbolGeneral<info>::Nodo& n) const;

  /**
    * @brief Obtiene la puntuación de una palabra
    * @param n Nodo en el que termina la palabra
    * @param cl Conjunto de letras con puntuaciones
    */
  int GetPuntuacion(const ArbolGeneral<info>::Nodo& n, const Conjunto_Letras& cl) const;

  /**
    * @brief Obtiene la longitud
    * @param n Nodo en el que termina la palabra
    * @return Número de caracteres de la palabra
    */
  int GetLongitud(const ArbolGeneral<info>::Nodo& n) const;

  /**
    * @brief Indica si una palabra está en el diccionario
    * @param palabra La palabra a comprobar
    * @return Si la palabra está en el diccionario
    */
  bool Esta(string palabra) const;

  /**
    * @brief Inserta una palabra en el diccionario
    * @param palabra Palabra a insertar
    */
  void Insertar(string palabra);

  /**
    * @brief Lee desde flujo de entrada un diccionario
    * @param is Flujo de entrada
    * @param D Diccionario
    * @return Referencia al flujo
    */
  friend istream & operator>>(istream & is, Diccionario & D);

  /**
    * @brief Escribe un diccionario en un flujo de salida
    * @param os Flujo de entrada
    * @param D Diccionario
    * @return Referencia al flujo
    */
  friend ostream & operator<<(ostream & os, Diccionario & D);

  class iterator{
    /**
      * @brief Un iterador preorden sobre un caracter final
      */
    ArbolGeneral<info>::iter_preorden it;

    /**
      * @brief Cadena formada por los caracteres del recorrido a la raíz
      */
    string cad;

  public:

    /**
      * @brief Constructor por defecto
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
      * @param i Iterador a comparar
      * @return Si son iguales
      */
    bool operator==(const iterator &i) const;

    /**
      * @brief Operador de comparación
      * @param i iterador a comparar
      * @return Si son distintos
      */
    bool operator!=(const iterator &i) const;

    friend class Diccionario;
  };

  /**
    * @brief Iterador a la primera palabra válida
    * @pre Existe al menos una palabra válida
    */
  iterator begin();

  /**
    * @brief Iterador al siguiente de la última palabra
    */
  iterator end();
};

#include "diccionario.cpp"

#endif
