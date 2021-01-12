#ifndef DEFINICIONES_H

#define DEFINICIONES_H

#include <iostream>

using namespace std;

/* ---------- DEFINICIONES --------- */

/*---------  Estructura del arbol  ------- */
struct nodo {
  int nro, numNodos = 0; // nummero de nodos del arbol
  struct nodo* izq, *der;
};
typedef struct nodo *ABB;

/* ---------- Nodo cola --------- */

struct _nodequeue {
  ABB ptr;
  struct _nodequeue* sgte;
};
typedef struct _nodequeue nodoCola;

/* ---------- Estructura de la cola --------- */

struct _queue{
  nodoCola* delante;
  nodoCola* atras;
};
typedef struct _queue cola;

/* ---------- Interacciones Internas --------- */

void inicializaCola( cola& );
void encola( cola&, ABB );
ABB desencola( cola& );
ABB crearNodo( int );
ABB unirABB( ABB, ABB );

/* ---------- Recorridos --------- */

void preOrden( ABB );
void enOrden( ABB );
void postOrden( ABB );

/* ---------- Interacciones externas (usuario) --------- */

void insertar( ABB&, int );
void verArbol( ABB, int );
bool busquedaRec( ABB, int );
void elimina( ABB&, int );

/* ---------- Funciones secundarias --------- */

void menu();
void menu2();

#endif
