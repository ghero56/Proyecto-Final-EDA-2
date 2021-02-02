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

	for( auto& v : vertices ){
		g.add_estacion( Vertice( v ) );  // se añaden los vertices al grafo
	}

  g.add_estacion_dirigida( "Ciencias", "CU" );
  g.add_estacion_dirigida( "CU", "Ing");
  g.add_estacion_dirigida( "Ing", "UNAM" );
  g.add_estacion_dirigida( "UNAM", "Metro" );

  g.print(); // imprimimos

	g.bfs( "CU", "UNAM" );
  //if(strcmp(argv[1],"admin") == 0) admin( );
  //else regular( );
  return 0;
}
