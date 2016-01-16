#include <fstream>
#include <iostream>
#include <string>
#include "diccionario.h"

int main(int argc, char * argv[]){
  if (argc != 4) {
	 cerr << "Uso: " << argv[0] << " diccionario letras salida" << endl;
	 return 1;
  }

  ifstream fd(argv[1]);
  if (!fd) {
    cerr << "No se pudo cargar el diccionario" << endl;
    return 1;
  }
  
  Diccionario D;
  fd >> D;
  
  ifstream fl(argv[2]);
  if (!fl) {
    cerr << "No se pudo cargar el fichero con las letras" << endl;
    return 1;
  }
  
  Conjunto_Letras cl;
  fl >> cl;
  
  Conjunto_Letras::iterator cli;
  for (cli = cl.begin(); cli != cl.end(); ++cli)
    (*cli).n = 0;
  
  for (Diccionario::iterator di = D.begin(); di != D.end(); ++di)
    for (unsigned int k = 0; k < (*di).length(); k++)
      (*cl.Encuentra((*di)[k])).n++;

  // TODO: normalizar las frecuencias

  ofstream fo(argv[3]);
  if (!fo) {
     cerr << "No se pudo imprimir el resultado" << endl;
     return 1;
  }
  fo << "#Letra\tCantidad\tPuntos\n";

  for (cli = cl.begin(); cli != cl.end(); ++cli)
    cout << '\n' << (*cli).l << '\t' << (*cli).n << '\t' << (*cli).puntos;

}
