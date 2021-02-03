#include "bdd.cpp"
/**
*
*
*
* para compilar usar:
*   g++ -Wall -std=c++11 -o main.out sqlite3.o main.cpp -ldl -pthread -fopenmp
*/
/* ---------- Funcion main --------- */
int main(int argc, char const *argv[])
{
  Grafo g;
  BDD base;
  int max = base.start( &g );

  if(strcmp(argv[1],"admin") == 0) admin( base, &g , max);
  else regular( base, &g , max);

  return 0;
}
