#include "definiciones.h"

/* ---------- MENUS ---------- */

/* ---------- menu admin --------- */
void admin(){
  int op;
  do{
    cout << "\n\n\t\t\tBienvenido a la red PUMA "
      "\n\t\t\t  (MODO ADMINISTRADOR)\n"
      "\n1) Ver rutas"
      "\n2) A\u00F1adir/Modificar estaciones"
      "\n3) Seleccionar punto de inicio y destino"
      "\n4) Guardar indicaciones"
      "\n5) Salir"
      "\n\t-> "; cin >> op;
    switch(op){
      case 1:
        cout << "Mostrando Rutas..." << '\n';
      break;
      case 2:
      break;
      case 3:
      break;
      case 4:
      break;
      case 5:
        cout << "saliendo..." << '\n';
        op = 11;
      break;
      default:
        cout << "valor fuera de rango" << '\n';
    }
  }while(op != 11);
}
/* ---------- menu usuario --------- */
void regular(){
  int op;
  do{
    cout << "\n\n\t\t\tBienvenido a la red PUMA\n"
      "\n1) Ver rutas"
      "\n2) Seleccionar punto de inicio y destino"
      "\n3) Guardar indicaciones"
      "\n4) Salir"
      "\n\t-> "; cin >> op;
    switch(op){
      case 1:
        cout << "Mostrando Rutas..." << '\n';
      break;
      case 2:
      break;
      case 3:
      break;
      case 4:
        cout << "saliendo..." << '\n';
        op = 11;
      break;
      default:
        cout << "valor fuera de rango" << '\n';
    }
  }while(op != 11);
}

void menu1(){

}
