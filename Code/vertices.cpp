#include "definiciones.hpp"

Vertice::Vertice( string nombre )
{
	item.id = 0;
	item.nombre = nombre;
	item.ruta = 0;
}

void Vertice::add_vecino( Vertice v )
{
	this->vecinos.push_back( v );
}

list<Vertice>* Vertice::get_vecinos()
{
	return &(vecinos);
}

string Vertice::get_nombre()
{
	return this->item.nombre;
}

void Vertice::print_vecinos()
{
	for( auto v : this->vecinos )
		cout << v.get_nombre() << "-> ";
	cout << "Null";
}

void Vertice::set_distancia( int distancia ) // in lab
{
	this->distancia = distancia;
}

void Vertice::set_color( Vertice::bandera color ) // in lab
{
	this->color = color;
}

void Vertice::set_predecesor( string predecesor ) // in lab
{
	this->predecesor = predecesor;
}

int Vertice::get_distancia() // in lab
{
	return this->distancia;
}

Vertice::bandera Vertice::get_color() // in lab
{
	return this->color;
}

string Vertice::get_predecesor() // in lab
{
	return this->predecesor;
}

void Vertice::print()
{
	string color;

	switch( this->color ){
		case Vertice::bandera::NEGRO: color = "NEGRO"; break;
		case Vertice::bandera::VISITADO: color = "VISITADO"; break;
		case Vertice::bandera::BLANCO: color = "BLANCO"; break;
	}
  cout << ".n: " << this->item.nombre << ", ";
  cout << ".d: " << this->item.id << ", ";
  cout << ".c: " << color << ", ";
  cout << ".p: " << this->predecesor << endl;
}
