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
  BDD base;  base.start( &g );

  // g.bfs(g.get_estacion_por_id(1),g.get_estacion_por_id(10));

  g.bfs("Anexo de ingenieria" , "D.G.T.I.C.");

  //if(strcmp(argv[1],"admin") == 0) admin( &g );
  //else regular( &g );

  return 0;
}
