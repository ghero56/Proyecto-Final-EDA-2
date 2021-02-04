/**
 * @file definiciones.hpp
 *
 * @brief Define las clases y estructuras, asi como las funciones utilizadas.
 * se incluyen librerias y se define el archivo HEAD
 *
 * @bug Se ha reportado un bug cuando se usa filesystem, no todas las distribuciones de linux lo tienen
 *
 * @authors Fernando Arciga, Fernando Rosas
 * @date 04/02/2021
 * @version 1.1
 */
#ifndef DEFINICIONES_H
#define DEFINICIONES_H

#pragma once

// Librerias utilizadas

#include <iostream>
#include <stdlib.h>
#include <cstring>
#include <string>
#include <omp.h>
#include <list>
#include <utility>
#include <map>
#include <deque>
#include <fstream>
#include "sqlite3.h"
#include <filesystem>

using namespace std;

/**
* @brief se define _estacion y se define su tipo como estacion
*/
typedef struct _estacion{
  int id; ///< lugar en la lista
  string nombre;
  int ruta;
} estacion;
/**
* @brief clase que se utilizara dentro del grafo, sus funciones son comentadas en
* @see vertices.cpp
*/
class Vertice{
	public:
		enum class bandera { NEGRO, VISITADO, BLANCO };

	private:
		mutable estacion item; ///<

		mutable list<Vertice> vecinos; ///< lista de vecinos del mismo tipo, en lugar de una DLL
		int distancia{ 0 }; ///< distancia entre id's el en grafo
		bandera color{ bandera::NEGRO }; ///< variable utilizada en el bfs @see grafo.cpp
		mutable string predecesor{ "Null" }; ///< variable sin uso de momento

	public:
		Vertice( string , int, int);
		string get_nombre();

		void  add_vecino( Vertice );
    void  mostrar();
	  void  print();
    void cambiar_datos(string, int);

		list<Vertice>* get_vecinos();

		void  set_distancia( int );
		void  set_color( Vertice::bandera );
		void  set_predecesor( string );
    int      get_ruta();
		int      get_distancia();
		bandera  get_color();
		string   get_predecesor();
    void     print_vecinos();
};
/**
* @brief clase que se utilizara para guardar los vertices que contienen las estaciones
* igual que en la definicion de vertice, sus metodos seran definidos en:
* @see grafo.cpp
*/
class Grafo{
	private:
		mutable map<string, Vertice> vertices; ///< mapa con los vertices en memoria
		mutable map<string, int> weights; ///< pesos/distancias entre vertices

    int len = 0; ///< longitud total del grafo

	public:
		Grafo();

		bool add_estacion( Vertice v );
		bool add_estacion_dirigida( string, string );

    bool cambiar(string, string, int);
    int aniadir(string, int);
    bool borrar_estacion(string);

		map<string, Vertice> *get_vertices();

		Vertice* get_vertice( string );
    string get_estacion_por_id( int );
    int get_len();

		void print();
		void bfs( string, string );
    void bfs_save( string, string );
};

/**
* @brief declaracion de los metodos de la base de datos
* @see bdd.cpp
*/
class BDD{
  private:
    sqlite3* create();
  public:
    int start(Grafo*);
    int add(Grafo*, string, int);
    int erase(Grafo*, string);
    void update(Grafo*, string, string, int);
};

int insertar( string , Grafo* );
void admin( BDD, Grafo* , int );
void regular( BDD , Grafo* , int );
void menu1( Grafo* , int );
void menuPtP( Grafo* , int );
void menuPtP_save( Grafo* , int );
int menu_add( Grafo* , int );

#endif
