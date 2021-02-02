#include "vertices.cpp"

Grafo::Grafo()
{
	// nada (por el momento)
}


bool Grafo::add_vertice( Vertice v )
{
	auto ret = vertices.insert( { v.get_nombre(), v } );
	// 'map' no permite duplicados, así que no hay necesidad de buscarlos

	return ret.second;
}

bool Grafo::add_estacion_dirigida( string eje1, string eje2 ){
	auto v1 = this->vertices.find( eje1 );
	auto v2 = this->vertices.find( eje2 );

	if( v1 != this->vertices.end() and v2 != this->vertices.end() ){
		v1->second.add_vecino( v2->second );
		return true;
	}
	return false;
}

/*void Grafo::print()
{
	for( auto v : this->vertices ){
		cout << "\n" << v.second.get_nombre() << ": ";
		v.second.print_neighbors();
	}
	cout << "\n\n";
}*/

map<string, Vertice>* Grafo::get_vertices()
{
	return &(this->vertices);
}

Vertice* Grafo::get_vertice( string nombre )
{
	auto v = this->vertices.find( nombre );

	return &(v->second);
}

void Grafo::bfs( string inicio ){
	for(auto v = this->vertices.begin() ; v != this->vertices.end() ; v++){
		(v->second).set_color( Vertice::bandera::NEGRO ); // sin descubir
		(v->second).set_distancia( 0 );
		(v->second).set_predecesor("Null");
	}

	get_vertice( inicio )->set_color( Vertice::bandera::VISITADO ); // iniciamos a A
	deque<string> queue;
	queue.push_back( inicio );

	while( not queue.empty() ){ // mientras tenga elementos
	// el metodo empty ya viene en la clase deque
		string next_vertex = queue.front(); // elemento siguiente
	  // obtenemos el NOMBRE asociado al vértice de trabajo ...
		queue.pop_front(); // sale el elem
	  // (desencolar toma dos operaciones: .front() y .pop_front())
		Vertice* vertex = get_vertice( next_vertex ); // creamos un vertice con el obtenido en la cola
	  // obtenemos una REFERENCIA al vértice de trabajo ...
		list<Vertice>* v = vertex->get_vecinos(); // obtenemos sus vecinos en una lista
		// obtenemos el original de la LISTA de vértices vecinos ...
		for( auto w = v->begin(); w != v->end(); ++w ){ // recorremos la lista
			Vertice* neighbor = get_vertice( w->get_nombre() );

			if( neighbor->get_color() == Vertice::bandera::NEGRO ){
			// si sigue sin ser descubierto
				neighbor->set_color( Vertice::bandera::VISITADO ); // lo ponemos en gris
				// vertice descubierto ...
				neighbor->set_distancia( vertex->get_distancia() + 1 );
				// establecemos la distancia desde 'inicio' ...
				neighbor->set_predecesor( vertex->get_nombre() ); // es v
				// establecemos al predecesor ...
				queue.push_back( neighbor->get_nombre() );
				// encolamos al vértice recién descubierto
	    }
	  }
		vertex->set_color( Vertice::bandera::BLANCO );
		// vértice visitado
	}
}
