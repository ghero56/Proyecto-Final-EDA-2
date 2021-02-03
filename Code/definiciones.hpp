#ifndef DEFINICIONES_H
#define DEFINICIONES_H

#pragma once
/* ---------- Librerias ---------- */
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

/* ---------- Clases y Estructuras ----------*/
typedef struct _estacion{
  int id;
  string nombre;
  int ruta; // a la que pertenece
} estacion;

class Vertice{
	public:
		enum class bandera { NEGRO, VISITADO, BLANCO };

	private:
		mutable estacion item;

		mutable list<Vertice> vecinos;
		int distancia{ 0 };
		bandera color{ bandera::NEGRO };
		mutable string predecesor{ "Null" };

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

class Grafo{
	private:
		mutable map<string, Vertice> vertices;
		mutable map<string, int> weights;

    int len = 0;

	public:
		Grafo();

		bool add_estacion( Vertice v );
		bool add_estacion_dirigida( string, string );
    bool cambiar(string, string, int);

		map<string, Vertice> *get_vertices();

		Vertice* get_vertice( string );
    string get_estacion_por_id( int );
    int get_len();

		void print();
		void bfs( string, string );
    void bfs_save( string, string );
};

/* ---------- Base de datos ---------- */
class BDD{
  private:
    sqlite3* create();
  public:
    int start(Grafo*);
    void update();
    void erase();
    void add();
    void update(Grafo*, string, string, int);
};

int insertar( string , Grafo* );
int serializar(void*, int, char**, char**);
/* ---------- MENUS ---------- */
void admin( BDD, Grafo* , int );
void regular( BDD , Grafo* , int );
void menu1( Grafo* , int );
void menuPtP( Grafo* , int );
void menuPtP_save( Grafo* , int );
int menu_add( Grafo* , int );

#endif
