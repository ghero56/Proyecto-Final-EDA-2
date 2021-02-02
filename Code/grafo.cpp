#include "vertices.cpp"

Grafo::Grafo()
{
	// nada (por el momento)
}


bool Grafo::add_estacion( Vertice v )
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

void Grafo::print()
{
	for( auto v : this->vertices ){
		if ( strcmp(v.second.get_nombre().c_str() , "Null") == 1) {
			cout << "\n" << v.second.get_nombre() << "-> ";
			v.second.print_vecinos();
		}
	}
	cout << "\n\n";
}

map<string, Vertice>* Grafo::get_vertices()
{
	return &(this->vertices);
}

Vertice* Grafo::get_vertice( string nombre )
{
	auto v = this->vertices.find( nombre );

	return &(v->second);
}

void Grafo::bfs( string inicio, string fin ){
	for(auto v = this->vertices.begin() ; v != this->vertices.end() ; v++){
		(v->second).set_color( Vertice::bandera::NEGRO ); // sin descubir
		(v->second).set_distancia( 0 );
		(v->second).set_predecesor("Null");
	}


	get_vertice( inicio )->set_color( Vertice::bandera::VISITADO );
	deque<string> queue;
	queue.push_back( inicio );

	cout << queue.front();
	// vertice->get_nombre() << dentro del if dentro del while

	while( !queue.empty() ){
		string next_vertice = queue.front();
		queue.pop_front();
		Vertice* vertice = get_vertice( next_vertice );
		list<Vertice>* v = vertice->get_vecinos();
		for( auto w = v->begin(); w != v->end(); ++w ){
			Vertice* vecino = get_vertice( w->get_nombre() );

			if( vecino->get_color() == Vertice::bandera::NEGRO ){
				if (strcmp(vecino->get_nombre().c_str(), fin.c_str()) == 0) {
					cout << " -> "<< vecino->get_nombre() << " ";
					break;
				}
				cout << " -> "<< vecino->get_nombre();
				vecino->set_color( Vertice::bandera::VISITADO );
				vecino->set_distancia( vertice->get_distancia() + 1 );
				vecino->set_predecesor( vertice->get_nombre() );
				queue.push_back( vecino->get_nombre() );
	    }
	  }
		vertice->set_color( Vertice::bandera::BLANCO );
	}

	cout << '\n';
}
