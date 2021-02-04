#include "bdd.cpp"
/**
* Comando para compilar:
*   g++ -Wall -std=c++11 -o main.out sqlite3.o main.cpp -ldl -pthread -fopenmp
*
* @brief Funcion principal, encargada de hacer funcionar el codigo
*/
/* ---------- Funcion main --------- */
int main(int argc, char const *argv[])
{
#pragma omp parallel //Abrimos regiones paralelas
{
  #pragma omp master
  {
    Grafo g; //Crea un grafo de nombre "g" 
    BDD base; //Creamos la base de datos esta tiene por nombre "base"
    int max = base.start( &g );
    if(strcmp(argv[1],"admin") == 0) admin( base, &g , max);    //Entramos a el programa como administradot o como refular
    else regular( base, &g , max); 
  }
}
  return 0;
}
