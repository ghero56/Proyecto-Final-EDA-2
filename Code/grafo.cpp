#include "vertices.cpp"

Grafo::Grafo()
{
	// nada (por el momento)
}

bool Grafo::cambiar(string estacion, string nuevo_nombre, int ruta){
 	BDD base;
	base.update(this,estacion,nuevo_nombre, ruta);
  this->vertices.erase( estacion );
  bfs(get_estacion_por_id(1),get_estacion_por_id(10));
	return true;
}


bool Grafo::add_estacion( Vertice v )
{
	len++;
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
		cout << "\n" << v.second.get_nombre() << "-> ";
		v.second.print_vecinos();
	}
	cout << "\n\n";
}

map<string, Vertice>* Grafo::get_vertices()
{
	return &(this->vertices);
}

int Grafo::get_len(){
	return this->len;
}

Vertice* Grafo::get_vertice( string nombre )
{
	auto v = this->vertices.find( nombre );
	return &(v->second);
}

string Grafo::get_estacion_por_id( int id ){
	for (auto v: this->vertices) {
		if (v.second.get_distancia() == id) {
			return v.first;
		}
	}
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

	cout << "\n" << get_vertice( queue.front() )->get_distancia() << ") "
	<<queue.front() << " (ruta: " << get_vertice( queue.front() )->get_ruta() << ")";
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

void Grafo::bfs_save( string inicio, string fin ){
	FILE* archivo = fopen( "indicaciones.xml" , "w");

	for(auto v = this->vertices.begin() ; v != this->vertices.end() ; v++){
		(v->second).set_color( Vertice::bandera::NEGRO ); // sin descubir
		(v->second).set_distancia( 0 );
		(v->second).set_predecesor("Null");
	}

	get_vertice( inicio )->set_color( Vertice::bandera::VISITADO );
	deque<string> queue;
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
