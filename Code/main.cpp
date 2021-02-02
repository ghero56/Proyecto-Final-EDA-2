#include "funciones.cpp"
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
  // Grafo g;
  if(strcmp(argv[1],"admin") == 0) admin( );
  else regular( );
  system("clear");
  return 0;
}
