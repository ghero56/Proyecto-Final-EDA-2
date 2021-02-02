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
  array<string, 11> vertices={"K","J","I","H","G","F","E","D","C","B","A"};

	array<string, 11> edges={"AE","AB","BC","BF","DH","EI","FG","FI","GJ","GK","HK"};


	for( auto& v : vertices ){
		g.add_vertice( Vertice( v ) );  // se añaden los vertices al grafo
	}

	for( auto& e : edges ){ // el auto& indica que el tipo a usar debe identificarlo el compilador (solo c++11)
		g.add_estacion_dirigida( e.substr( 0, 1 ), e.substr( 1, 1 ) );
		// .substr( a_partir_de_dónde, cuántos_queremos_leer )
	}
	g.print(); // imprimimos

	g.bfs( "A" );
  //if(strcmp(argv[1],"admin") == 0) admin( );
  //else regular( );
  //system("clear");
  return 0;
}
