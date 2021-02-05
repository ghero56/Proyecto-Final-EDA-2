/**
 * @file vertices.cpp
 *
 * @brief Define los metodos de la clase Vertice
 * @see definiciones.hpp
 *
 * @authors Fernando Arciga, Fernando Rosas
 * @date 04/02/2021
 * @version 1.1
 */
#include "definiciones.hpp"
/**
* @brief constructor del grafo
* @param nombre para el nuevo Vertice
* @param id para el nuevo vertice
* @param ruta del nuevo vertice
*/
Vertice::Vertice( string nombre, int id, int ruta )
{
	item.id = id;
	item.nombre = nombre;
	item.ruta = ruta;
}
/**
* @brief cambia los datos en el item
* @param nn es el nuevo nombre
* @param r es la nueva ruta
* @see grafo.cpp
*/
void Vertice::cambiar_datos(string nn, int r){
	this->item.nombre = nn;
	this->item.ruta = r;
}
/**
* @brief añade un vecino a la lista dentro del vertice actual
* @param v es el nuevo Vertice a ingresar
*/
void Vertice::add_vecino( Vertice v )
{
	this->vecinos.push_back( v );
}
/**
* @return la lista de vertices en el Vertice acutal
*/
list<Vertice>* Vertice::get_vecinos()
{
	return &(vecinos);
}
/**
* @return la ruta a la que pertenece
*/
int Vertice::get_ruta(){
	return this->item.ruta;
}
/**
* @return el nombre de la estacion
*/
string Vertice::get_nombre()
{
	return this->item.nombre;
}
/**
* @brief para cada vecino en la lista imprime su nombre y su direccion
*/
void Vertice::print_vecinos()
{
	for( auto v : this->vecinos )
		cout << v.get_nombre() << "-> ";
	cout << "Null";
}
/**
* @param distancia nueva para el Vertice
*/
void Vertice::set_distancia( int distancia )
{
	this->distancia = distancia;
}
/**
* @param color es la nueva marca para saber el estado de descubrimiento del vertice
* @see definiciones.hpp
*/
void Vertice::set_color( Vertice::bandera color )
{
	this->color = color;
}
/**
* @param predecesor es el nombre del Vertice anterior al actual (fuera de uso)
*/
void Vertice::set_predecesor( string predecesor )
{
	this->predecesor = predecesor;
}
/**
* @return el id de la estacion
*/
int Vertice::get_distancia()
{
	return this->item.id;
}
/**
* @return el estado de descubrimiento del Vertice
*/
Vertice::bandera Vertice::get_color()
{
	return this->color;
}
/**
* @return el nombre del predecesor
*/
string Vertice::get_predecesor()
{
	return this->predecesor;
}
/**
* @brief imprime el Vertice actual (fuera de uso)
*/
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
