/**
 * @file main.cpp
 *
 * @brief driver program para ver, añadir, modificar las estaciones en una ruta del pumabus
 * Comando para compilar:
 *   g++ -Wall -std=c++11 -o main.out sqlite3.c main.cpp -ldl -pthread -fopenmp
 * Al ejecutar SIEMPRE colocar un segundo argumento
 *
 * @bug Se ha reportado un bug cuando no se colocan argumentos al ejecutar
 *
 * @authors Fernando Rosas
 * @date 04/02/2021
 * @version 1.1
 */
#include "bdd.cpp"

int main(int argc, char const *argv[])
{

#pragma omp parallel //Abrimos regiones paralelas
{
  #pragma omp master
  {
    Grafo g; ///< Crea un grafo de nombre "g"
    BDD base; ///< Creamos la base de datos
    int max = base.start( &g ); ///< recibe el tamaño maximo del grafo @see funciones.cpp
    //Entramos a el programa de acuerdo a los argumentos
    if(strcmp(argv[1],"admin") == 0) admin( base, &g , max);
    else regular( base, &g , max);
  }
}
  return 0;
}
