/**
 * @file grafo.cpp
 *
 * @brief Define los metodos de la clase Grafo, despues de importar los metodos definidos en vertices
 * @see definiciones.hpp
 *
 * @authors Fernando Arciga, Fernando Rosas
 * @date 04/02/2021
 * @version 1.1
 */
#include "vertices.cpp"
/**
* @brief constructor del Grafo
*/
Grafo::Grafo(){

}
/**
* @brief cambia una estacion en la base de datos y luego la borra de entre los vertices
* @return true, ya que el valor siempre esta en la lista
* @see funciones.cpp
*/
bool Grafo::cambiar(string estacion, string nuevo_nombre, int ruta){
  BDD base;
  #pragma omp sections
  {
    #pragma omp section
    base.update(this,estacion,nuevo_nombre, ruta);
    #pragma omp section
    this->vertices.erase( estacion );
  }
  bfs(get_estacion_por_id(1),get_estacion_por_id(10));
	return true;
}
/**
* @brief Borra una estacion del grafo y de la base de datos
* @return true, ya que el valor siempre esta en la lista
* @see funciones.cpp
*/
bool Grafo::borrar_estacion(string estacion){
 	BDD base;
  #pragma omp sections
  {
    #pragma omp section
  	base.erase(this , estacion);
    #pragma omp section
    this->vertices.erase( estacion );
  }
  bfs(get_estacion_por_id(1),get_estacion_por_id(10));
	return true;
}
/**
* @brief Añade una estacion nueva en el grafo y la base
* @return true, ya siempre se agrega el valor
*/
int Grafo::aniadir( string nuevo_nombre, int ruta ){
 	BDD base;
	int i = base.add(this , nuevo_nombre , ruta);
  bfs(get_estacion_por_id(1),get_estacion_por_id(i));
	return true;
}
/**
* @brief crea un nuevo vertice en el grafo y por ende aumenta su tamaño
* @see vertices.cpp
*/
bool Grafo::add_estacion( Vertice v )
{
	len++;
	auto ret = vertices.insert( { v.get_nombre(), v } );
	return ret.second;
}
/**
* @brief crea una ruta entre punto a y b (eje1 -> eje2)
* @see vertices.cpp
* @return true si se logro localizar el objetivo
*/
bool Grafo::add_estacion_dirigida( string eje1, string eje2 ){
	auto v1 = this->vertices.find( eje1 );
	auto v2 = this->vertices.find( eje2 );

	if( v1 != this->vertices.end() and v2 != this->vertices.end() ){
		v1->second.add_vecino( v2->second );
		return true;
	}
	return false;
}
/**
* @brief imprime en pantalla cada uno de los valores en los vertices, comenzando por el incial
*/
void Grafo::print()
{
	for( auto v : vertices ){
		cout << "\n" << v.second.get_nombre() << "-> ";
		v.second.print_vecinos();
	}
	cout << "\n\n";
}
/**
* @return el mapa con los vertices actuales
*/
map<string, Vertice>* Grafo::get_vertices()
{
	return &(this->vertices);
}
/**
* return el tamaño del grafo (poco uso)
*/
int Grafo::get_len(){
	return this->len;
}
/**
* @brief obtiene un apuntador a un vertice en el grafo con el nombre especificado
* @return el apuntador a dicho vertice
*/
Vertice* Grafo::get_vertice( string nombre )
{
	auto v = this->vertices.find( nombre );
	return &(v->second);
}
/**
* @brief busca por un indice en el mapa de vertices
* @return la cadena que compone el nombre del vertice
*/
string Grafo::get_estacion_por_id( int id ){
	for (auto v: this->vertices) {
		if (v.second.get_distancia() == id) {
			return v.first;
		}
	}
  return 0;
}
/**
* @brief busqueda en anchura utilizada para un grafo dirigido
* su principal uso es buscar en los vecinos desde un punto inicial a un punto final
* en el grafo e imprimirlo en pantalla
*/
void Grafo::bfs( string inicio, string fin ){
  for(auto v = vertices.begin() ; v != vertices.end() ; v++){
    (v->second).set_color( Vertice::bandera::NEGRO ); // sin descubir
    (v->second).set_distancia( 0 );
    (v->second).set_predecesor("Null");
  }

  deque<string> queue;
  get_vertice( inicio )->set_color( Vertice::bandera::VISITADO );
	queue.push_back( inicio );

	cout << "\n" << get_vertice( queue.front() )->get_distancia() << ") "
	<<queue.front() << " (ruta: " << get_vertice( queue.front() )->get_ruta() << ")";

	while( !queue.empty() ){
		string next_vertice = queue.front();
		queue.pop_front();
		Vertice* vertice = get_vertice( next_vertice );
		list<Vertice>* v = vertice->get_vecinos();
		for( auto w = v->begin(); w != v->end(); ++w ){
			Vertice* vecino = get_vertice( w->get_nombre() );
			if( vecino->get_color() == Vertice::bandera::NEGRO ){
				if (strcmp(vecino->get_nombre().c_str(), fin.c_str()) == 0) {
					cout << "\n\t\t|\n\t\tV\n" << vecino->get_distancia() <<") "
						<< vecino->get_nombre() << " (ruta: " << vecino->get_ruta()
						<< ")" << '\n';
					break;
				}
				cout << "\n\t\t|\n\t\tV\n" << vecino->get_distancia() <<") "
					<< vecino->get_nombre() << " (ruta: "<< vecino->get_ruta() << ")";
				vecino->set_color( Vertice::bandera::VISITADO );
				vecino->set_distancia( vertice->get_distancia() + 1 );
				vecino->set_predecesor( vertice->get_nombre() );
				queue.push_back( vecino->get_nombre() );
	    }
	  }
		vertice->set_color( Vertice::bandera::BLANCO );
	}
}
/**
* @brief busqueda en anchura utilizada para un grafo dirigido
* su principal uso es buscar en los vecinos desde un punto inicial a un punto final
* en el grafo e imprimirlo en pantalla y generar dos archivos
* @see indicaciones.*
*/
void Grafo::bfs_save( string inicio, string fin ){
	FILE* archivo = fopen( "indicaciones.xml" , "w");
  FILE* archivo2 = fopen( "indicaciones.txt" , "w");

	for(auto v = this->vertices.begin() ; v != this->vertices.end() ; v++){
		(v->second).set_color( Vertice::bandera::NEGRO ); // sin descubir
		(v->second).set_distancia( 0 );
		(v->second).set_predecesor("Null");
	}

	deque<string> queue;
  get_vertice( inicio )->set_color( Vertice::bandera::VISITADO );
	queue.push_back( inicio );

	fputs( "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n" , archivo);
	fputs( "  <Estaciones_a_seguir>\n", archivo);
	fputs("    <estacion>\n" , archivo);
	fputs("      <nombre>", archivo);
	fputs(queue.front().c_str(), archivo);
	fputs("</nombre>\n", archivo);
	fputs("      <ruta>", archivo);
	fprintf(archivo , "%d", get_vertice( queue.front() )->get_ruta());
	fputs("</ruta>\n", archivo);
	fputs("      <id>", archivo);
	fprintf(archivo, "%d", get_vertice( queue.front() )->get_distancia());
	fputs("</id>\n", archivo);
	fputs("    </estacion>\n", archivo);

  fprintf(archivo2, "\n%d) %s (ruta: %d)", get_vertice( queue.front() )->get_distancia(),
  queue.front().c_str(),get_vertice( queue.front() )->get_ruta());

	while( !queue.empty() ){
		string next_vertice = queue.front();
		queue.pop_front();
		Vertice* vertice = get_vertice( next_vertice );
		list<Vertice>* v = vertice->get_vecinos();
		for( auto w = v->begin(); w != v->end(); ++w ){
			Vertice* vecino = get_vertice( w->get_nombre() );

			if( vecino->get_color() == Vertice::bandera::NEGRO ){
				if (strcmp(vecino->get_nombre().c_str(), fin.c_str()) == 0) {
					fputs("    <estacion>\n" , archivo);
					fputs("      <nombre>", archivo);
					fputs(vecino->get_nombre().c_str(), archivo);
					fputs("</nombre>\n", archivo);
					fputs("      <ruta>", archivo);
					fprintf(archivo , "%d", vecino->get_ruta());
					fputs("</ruta>\n", archivo);
					fputs("      <id>", archivo);
					fprintf(archivo, "%d", vecino->get_distancia());
					fputs("</id>\n", archivo);
					fputs("    </estacion>\n", archivo);
          fprintf(archivo2, "\n\t\t|\n\t\tV\n%d) %s (ruta: %d)", vecino->get_distancia()
          ,vecino->get_nombre().c_str() ,vecino->get_ruta());
					break;
				}
				fputs("    <estacion>\n" , archivo);
				fputs("      <nombre>", archivo);
				fputs(vecino->get_nombre().c_str(), archivo);
				fputs("</nombre>\n", archivo);
				fputs("      <ruta>", archivo);
				fprintf(archivo , "%d", vecino->get_ruta());
				fputs("</ruta>\n", archivo);
				fputs("      <id>", archivo);
				fprintf(archivo, "%d", vecino->get_distancia());
				fputs("</id>\n", archivo);
				fputs("    </estacion>\n", archivo);
        fprintf(archivo2, "\n\t\t|\n\t\tV\n%d) %s (ruta: %d)", vecino->get_distancia()
        ,vecino->get_nombre().c_str() ,vecino->get_ruta());
				vecino->set_color( Vertice::bandera::VISITADO );
				vecino->set_distancia( vertice->get_distancia() + 1 );
				vecino->set_predecesor( vertice->get_nombre() );
				queue.push_back( vecino->get_nombre() );
	    }
	  }
		vertice->set_color( Vertice::bandera::BLANCO );
	}
	fputs( "  </Estaciones_a_seguir>", archivo);
	fclose( archivo );
}
