#include <fstream>
#include <iostream>
#include <string>
#include "diccionario.h"

int main(int argc, char * argv[]){
  if (argc != 5) {
	 cerr << "Uso: " << argv[0] << " diccionario letras tamaño modo" << endl;
	 return 1;
  }

  string dict = argv[1], letras = argv[2], modo = argv[4];
  int tam = stoi(argv[3]);

  if(tam <= 0){
    cerr << "El tamaño debe ser un entero positivo" << endl;
    return 1;
  }

  if(modo != "L" && modo != "P"){
    cerr << "Los modos posibles son longitud (L) y puntuación (P)" << endl;
    return 1;
  }

  ifstream fd(dict);
  if (!fd) {
    cerr << "No se pudo cargar el diccionario" << endl;
    return 1;
  }

  Diccionario D;
  fd >> D;

  ifstream fl(letras);
  if (!fl) {
    cerr << "No se pudo cargar el fichero con las letras" << endl;
    return 1;
  }

  Conjunto_Letras cl;
  fl >> cl;
  char s_j;
  
  do{
    Bolsa_Letras bl(cl,tam);

    string s_usuario;
    cout << "Las letras son: " << bl << endl;

    cout << "Dime tu solución: ";
    do{
    cin >> s_usuario;
    } while(!bl.Correcta(s_usuario));

    cout << s_usuario << "Puntuación: " << cl.Puntuacion(s_usuario) << endl;

    cout << "Mis Soluciones son: ";
    vector<string> sols = D.MejoresSoluciones(bl,modo);

    for (vector<string>::iterator it = sols.begin(); it != sols.end(); ++it)
      cout << *it << "Puntuación: " << cl.Puntuacion(*it) << endl;

    cout << "Mejor Solución:" << *sols.begin() << endl;
    cout << "¿Quieres seguir jugando [S/N]?";
    cin >> s_j;
  } while(s_j == 'S');
}
