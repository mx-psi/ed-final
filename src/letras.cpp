#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>     // std::sort
#include "diccionario.h"

bool Correcta(vector<letra> disponibles, string palabra) {
  if (palabra.length() == 0)
    return true;

  for (vector<letra>::const_iterator v_it = disponibles.begin(); v_it != disponibles.end(); ++v_it)
    if (palabra.back() == (*v_it).l) {
      disponibles.erase(v_it);
      palabra.pop_back();
      return Correcta(disponibles, palabra);
    }

  return false;
}

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
  Bolsa_Letras bl(cl);
  srand(time(0));
  
  do{
    vector<letra> disponibles = bl.MuestraAleatoria(tam);

    string s_usuario;
    cout << "Las letras son: ";
    for (vector<letra>::const_iterator it = disponibles.begin(); it != disponibles.end(); ++it)
      cout << (it != disponibles.begin()?'\t':' ') << (*it).l << " ";
   
    cout << "\n" << endl;
    
    sort(disponibles.begin(), disponibles.end());

    cout << "Dime tu solución: ";
    do{
    cin >> s_usuario;
    } while(!Correcta(disponibles, s_usuario)); // TODO: Poner un mensaje en caso de incorrecta

    cout << s_usuario << " Puntuación: " << (modo == "P" ? cl.Puntuacion(s_usuario) : s_usuario.length()) << endl;

    cout << "Mis Soluciones son: " << endl;
    vector<string> sols = D.MejoresSoluciones(disponibles, modo);

    for (vector<string>::iterator it = sols.begin(); it != sols.end(); ++it)
      cout << *it << " Puntuación: " << (modo == "P" ? cl.Puntuacion(*it) : (*it).length()) << endl;

    cout << "Mejor Solución:" << *sols.begin() << endl;
    cout << "¿Quieres seguir jugando [S/N]?";
    cin >> s_j;
  } while(s_j == 'S');
}
