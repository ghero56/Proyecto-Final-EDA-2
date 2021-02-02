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
  Grafo g;
  array<string, 5> vertices={"Ciencias","CU","Ing","UNAM","Metro"};

	for( auto& v : vertices ){
		g.add_vertice( Vertice( v ) );  // se añaden los vertices al grafo
	}

  g.add_estacion_dirigida( "Ciencias", "Ing" );
  g.add_estacion_dirigida( "Ciencias", "Metro" );
  g.add_estacion_dirigida( "CU", "Ciencias");
  g.add_estacion_dirigida( "UNAM", "CU" );
  g.add_estacion_dirigida( "UNAM", "Ciencias" );

  g.print(); // imprimimos

	g.bfs( "UNAM" );
  //if(strcmp(argv[1],"admin") == 0) admin( );
  //else regular( );
  //system("clear");
  return 0;
}
