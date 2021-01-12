#include "definiciones.h"

/* ---------- Interacciones Internas --------- */

void inicializaCola(cola& q)
{
  q.delante = NULL;
  q.atras = NULL;
}

void encola(cola& q, ABB n)
{
  nodoCola* p;
  p = new(nodoCola);
  p->ptr = n;
  p->sgte = NULL;

  if (q.delante == NULL) q.delante = p;
  else (q.atras)->sgte = p;
  q.atras = p;
}

ABB desencola(cola& q)
{
  nodoCola* p;
  p = q.delante;
  ABB n = p->ptr;
  q.delante = (q.delante)->sgte;
  delete(p);
  return n;
}

ABB crearNodo(int x)
{
  ABB nuevoNodo = new(nodo);
  nuevoNodo->nro = x;
  nuevoNodo->izq = NULL;
  nuevoNodo->der = NULL;

  return nuevoNodo;
}

ABB unirABB(ABB izq, ABB der)
{
  if (izq == NULL) return der;
  if (der == NULL) return izq;

  ABB centro = unirABB(izq->der, der->izq);
  izq->der = centro;
  der->izq = izq;
  return der;
}

/* ---------- Recorridos --------- */

void preOrden( ABB arbol )
{
  if(arbol != NULL)
  {
    #pragma omp parallel
    cout << arbol->nro << " ";
    enOrden(arbol->izq);
    enOrden(arbol->der);
  }
}

void enOrden( ABB arbol )
{
  if (arbol != NULL)
  {
    enOrden(arbol->izq);
    cout << arbol->nro << " ";
    enOrden(arbol->der);
  }
}


void postOrden( ABB arbol )
{
  if(arbol != NULL)
  {
    enOrden(arbol->izq);
    enOrden(arbol->der);
    cout << arbol->nro << " ";
  }
}

/* ---------- Interacciones externas (usuario) --------- */

void insertar(ABB& arbol, int x)
{
  if (arbol == NULL)
  {
    arbol = crearNodo(x);
    cout << "\n\t  Insertado..!" << endl << endl;
  }
  else if (x < arbol->nro) insertar(arbol->izq, x);
  else if (x > arbol->nro) insertar(arbol->der, x);
}

void verArbol(ABB arbol, int n)
{
  if (arbol == NULL) return;

  verArbol(arbol->der, n + 1);
  for (size_t i = 0; i < n; i++) cout << "   ";

  arbol->numNodos++;

  cout << arbol->nro << endl;
  verArbol(arbol->izq, n + 1);
}

bool busquedaRec(ABB arbol, int dato)
{
  int r = 0;   // 0 indica que lo encontre

  if (arbol == NULL) return r;
  if (dato < arbol->nro) r = busquedaRec(arbol->izq, dato);
  else if (dato > arbol->nro) r = busquedaRec(arbol->der, dato);
  else r = 1; // son iguales, lo encontre

  return r;
}

void elimina(ABB& arbol, int x)
{
  if (arbol == NULL) return;
  else if (x < arbol->nro) elimina(arbol->izq, x);
  else if (x > arbol->nro) elimina(arbol->der, x);
  else
  {
    ABB p = arbol;
    arbol = unirABB(arbol->izq, arbol->der);
    delete p;
  }
}

/* ---------- Funciones secundarias --------- */

void menu()
{
  //system("cls");
  cout << "\n\t\t  ..[ ARBOL BINARIO DE BUSQUEDA ]..  \n\n";


  cout << "\t [1]  Insertar elemento        \n";
  cout << "\t [2]  Mostrar arbol            \n";
  cout << "\t [3]  Recorridos de profundidad\n";
  cout << "\t [4]  Buscar elemento          \n";
  cout << "\t [5]  Eliminar elemento        \n";
  cout << "\t [6]  SALIR                    \n";


  cout << "\n\t Ingrese opcion : ";
}

void menu2()
{
  //system("cls");   // para limpiar pantalla
  cout << endl;
  cout << "\t [1] En Orden  \n";
  cout << "\t [2] Pre Orden \n";
  cout << "\t [3] Post Orden\n";
  cout << "\t [4] Regresar  \n";
  cout << "\n\t     Opcion :  ";
}
