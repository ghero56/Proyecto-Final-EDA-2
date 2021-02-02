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

  base.start();
  array<string, 5> vertices={"Ciencias","CU","Ing","UNAM","Metro"};

  int i = 0;
	for( auto& v : vertices ){
		g.add_estacion( Vertice( v , i, 3) );  // se añaden los vertices al grafo
    ++i;
	}

  g.add_estacion_dirigida( "Ciencias", "CU" );
  g.add_estacion_dirigida( "CU", "Ing");
  g.add_estacion_dirigida( "Ing", "UNAM" );
  g.add_estacion_dirigida( "UNAM", "Metro" );
  g.add_estacion_dirigida( "Metro", "Ciencias" );

  if(strcmp(argv[1],"admin") == 0) admin( &g );
  else regular( &g );

  return 0;
}
