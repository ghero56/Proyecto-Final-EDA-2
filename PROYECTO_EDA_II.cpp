#include "funciones.cpp"

/* ---------- Funcion main --------- */

int main(int argc, char const *argv[])
{
  ABB arbol = NULL;
  int x;
  int op, op2;

  do
  {
    menu();  cin >> op;
    cout << endl;

    switch (op)
    {
      case 1:
        cout << " Ingrese valor : ";  cin >> x;
        insertar(arbol, x);
        break;

      case 2:
        verArbol(arbol, 0);
        break;

      case 3:
        menu2();  cin >> op2;

        if (arbol != NULL)
        {
          switch (op2)
          {
            case 1:
              enOrden(arbol);
              break;
            case 2:
              preOrden(arbol);
              break;
            case 3:
              postOrden(arbol);
              break;
          }
        }
        else cout << "\n\t Arbol vacio..!";

        break;

      case 4:
        bool band;
        cout << " Valor a buscar: "; cin >> x;

        band = busquedaRec(arbol, x);

        if (band == 1) cout << "\n\tEncontrado...";
        else cout << "\n\tNo encontrado...";
        break;

      case 5:
        cout << " Valor a eliminar: "; cin >> x;
        elimina(arbol, x);
        cout << "\n\tEliminado..!";
        break;

      case 6:
        return 0;
    }

    cout << "\n\n\n";
    //system("pause");  // hacer pausa y presionar una tecla para continuar
  } while (op != 11);
  return 0;
}
