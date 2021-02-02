/**
*
*
*
* para compilar usar:
*   g++ -Wall -std=c++11 -o main.out sqlite3.o main.cpp -ldl -pthread -fopenmp
*/

#include "funciones.cpp"

/* ---------- Funcion main --------- */
int main(int argc, char const *argv[])
{
  if(strcmp(argv[1],"admin") == 0) admin( );
  else regular( );
  system("clear");
  return 0;
}
