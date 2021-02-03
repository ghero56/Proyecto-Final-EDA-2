#include "grafo.cpp"

int callback_print(void* NotUsed, int argc, char** argv, char** azColName)
{
  /*for (int i = 0; i < argc; i++) {
    cout << argv[i] << " ";
  }
  cout << endl;*/

  return 0;
}

int serializar(void* NotUsed, int argc, char** argv, char** azColName)
{
  string extension_archivo = ".csv";
  ofstream archivo;
  archivo.open("Ruta" + extension_archivo, ios::app); //Archivo donde se guardara toda la informacion

  for (int i = 0; i < argc; i++) {
    // cout << azColName[i] << ": " << argv[i] << endl;
    if(strcmp( azColName[i], "Ruta") == 0) archivo << argv[i] << "\n";
    else archivo << argv[i] << ", ";
  }

  archivo.close();
  return 0;
}

int insertar( string archivo, Grafo* g)
{
  FILE* a = fopen( archivo.c_str() , "r" );
  if (a == NULL) {
    return 0;
  }

  char nombre[80];
  int id, ruta; int i = 0;

  while(fscanf( a, "%d, %79[^,], %d\n", &id, &nombre, &ruta ) != EOF){
    g->add_estacion( Vertice( nombre , id, ruta) );
    ++i;
  }


  for(int j = 1; j < i; j++){
    g->add_estacion_dirigida(g->get_estacion_por_id(j) , g->get_estacion_por_id(j+1));
  }

  fclose(a);

  return i;
}

bool fileExists( string nombre )
{
  FILE* a = fopen( nombre.c_str() , "r" );
  if (a == NULL) {
    return false;
  }
  fclose(a);
  return true;
}

char* crear_primer_uso( sqlite3* db, int rc, string sql, char* zErrMsg)
{

  sql = "DROP TABLE IF EXISTS RutasPumabus; "
      "CREATE TABLE RutasPumabus ("  \
      "id INTEGER PRIMARY KEY NOT NULL, " \
      "Ubicacion TEXT NOT NULL, " \
      "Ruta INTEGER NOT NULL );";

  rc = sqlite3_exec(db, sql.c_str(), callback_print, 0, &zErrMsg);

  sql = "INSERT INTO RutasPumabus ( 'Ubicacion', 'Ruta' ) VALUES ( 'Metro CU ESTACION PRINCIPAL', '3' );";
  rc = sqlite3_exec(db, sql.c_str(), callback_print, 0, &zErrMsg);

  sql = "INSERT INTO RutasPumabus ( 'Ubicacion', 'Ruta' ) VALUES ( 'Facultad de ciencias ALUMNOS', '3' );";
  rc = sqlite3_exec(db, sql.c_str(), callback_print, 0, &zErrMsg);

  sql = "INSERT INTO RutasPumabus ( 'Ubicacion', 'Ruta' ) VALUES ( 'Facultad de ciencias PROFESORES', '3' );";
  rc = sqlite3_exec(db, sql.c_str(), callback_print, 0, &zErrMsg);

  sql = "INSERT INTO RutasPumabus ( 'Ubicacion', 'Ruta' ) VALUES ( 'Anexo de ingenieria', '3' );";
  rc = sqlite3_exec(db, sql.c_str(), callback_print, 0, &zErrMsg);

  sql = "INSERT INTO RutasPumabus ( 'Ubicacion', 'Ruta' ) VALUES ( 'Facultad de Contaduria y Administracion', '3' );";
  rc = sqlite3_exec(db, sql.c_str(), callback_print, 0, &zErrMsg);

  sql = "INSERT INTO RutasPumabus ( 'Ubicacion', 'Ruta' ) VALUES ( 'Escuela de Trabajo Social', '3' );";
  rc = sqlite3_exec(db, sql.c_str(), callback_print, 0, &zErrMsg);

  sql = "INSERT INTO RutasPumabus ( 'Ubicacion', 'Ruta' ) VALUES ( 'Metrobus CU', '3' );";
  rc = sqlite3_exec(db, sql.c_str(), callback_print, 0, &zErrMsg);

  sql = "INSERT INTO RutasPumabus ( 'Ubicacion', 'Ruta' ) VALUES ( 'Educacion a Distancia', '3' );";
  rc = sqlite3_exec(db, sql.c_str(), callback_print, 0, &zErrMsg);

  sql = "INSERT INTO RutasPumabus ( 'Ubicacion', 'Ruta' ) VALUES ( 'D.G.T.I.C.', '3' );";
  rc = sqlite3_exec(db, sql.c_str(), callback_print, 0, &zErrMsg);

  sql = "INSERT INTO RutasPumabus ( 'Ubicacion', 'Ruta' ) VALUES ( 'Facultad de Ciencias', '3' );";
  rc = sqlite3_exec(db, sql.c_str(), callback_print, 0, &zErrMsg);

  return zErrMsg;
}

/* ---------- menu admin --------- */
void admin( BDD b, Grafo* g, int max )
{
  int op;
  do{
    system("clear");
    cout << "\t\t\tBienvenido a la red PUMA "
      "\n\t\t\t  (MODO ADMINISTRADOR)\n"
      "\n1) Ver rutas"
      "\n2) A\u00F1adir/Modificar estaciones"
      "\n3) Seleccionar punto de inicio y destino"
      "\n4) Guardar indicaciones"
      "\n5) Salir"
      "\n\t-> "; cin >> op;
    switch(op){
      case 1:
        menu1( g, max );
      break;
      case 2:
        max = menu_add( g, max );
      break;
      case 3:
        menuPtP( g, max );
      break;
      case 4:
        menuPtP_save( g, max );
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
void regular( BDD b, Grafo* g, int max)
{
  system("clear");
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
        menu1(g, max);
      break;
      case 2:
        menuPtP(g, max);
      break;
      case 3:
        menuPtP_save( g, max);
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

void menu1( Grafo* g , int max)
{
  system("clear");
  int op;
  cout << "\nMostrando estaciones actuales: [estacion (ruta a la que pertenece)]" << '\n';
  cout << "(En caso de querer elegir punto de inicio"
        " y destino presiona 1 en otro caso presiona 2)" << '\n';
  g->bfs(g->get_estacion_por_id( 1 ),g->get_estacion_por_id(max));
  std::cout << "\n\t-> ";
  cin >> op;
  switch (op) {
    case 1:
      menuPtP(g, max);
    break;
    case 2:
    return;
  }
}

void menuPtP( Grafo* g , int max)
{
  system("clear");
  int inicio, fin;
  g->bfs(g->get_estacion_por_id( 1 ),g->get_estacion_por_id(max));
  cout << "\nIndica por indice la estacion inicial ( disponibles: "<< max <<" ) -> ";
  cin >> inicio;
  if (inicio <= max && inicio >= 0) {
    cout << "Seleccionada: " << g->get_estacion_por_id(inicio) << '\n';
  }
  cout << "\nIndica por indice la estacion final ( disponibles: "<< max-1 <<" ) -> ";
  cin >> fin;
  if (inicio <= max && inicio >= 0 && inicio != fin) {
    cout << "Seleccionada: " << g->get_estacion_por_id(fin) << '\n';
    g->bfs( g->get_estacion_por_id(inicio), g->get_estacion_por_id(fin));
  }else{
    std::cout << "\nintenta nuevamente\n";
  }
  string enter;
  cout << "\nRuta trazada"
    "\nPresiona cualquier tecla y luego enter para regresar..." << '\n';
  cin >> enter;
}

void menuPtP_save(Grafo* g, int max)
{
  system("clear");
  int inicio, fin;
  g->bfs(g->get_estacion_por_id( 1 ),g->get_estacion_por_id(max));
  cout << "\nIndica por indice la estacion inicial ( disponibles: "<< max <<" ) -> ";
  cin >> inicio;
  if (inicio <= max && inicio >= 0) {
    cout << "Seleccionada: " << g->get_estacion_por_id(inicio) << '\n';
  }
  cout << "\nIndica por indice la estacion final ( disponibles: "<< max-1 <<" ) -> ";
  cin >> fin;
  if (inicio <= max && inicio >= 0 && inicio != fin) {
    cout << "Seleccionada: " << g->get_estacion_por_id(fin) << '\n';
    g->bfs_save( g->get_estacion_por_id(inicio), g->get_estacion_por_id(fin));
  }else{
    std::cout << "\nintenta nuevamente\n";
  }
  string enter;
  cout << "\nRuta Guardada"
    "\nPresiona cualquier tecla y luego enter para regresar..." << '\n';
  cin >> enter;
}

int menu_add(Grafo* g, int max)
{
  int op;
  do{
    system("clear");
    string enter;
    cout << "\n\tAñadir/Modificar estaciones\n"
      "\n1) Ver rutas"
      "\n2) Seleccionar punto a cambiar"
      "\n3) Ingresar nueva estacion"
      "\n4) Eliminar estacion"
      "\n5) Regresar"
      "\n\t-> "; cin >> op;
    switch(op){
      case 1:
        system("clear");
        g->bfs(g->get_estacion_por_id( 1 ),g->get_estacion_por_id(max));
        cout << "\nPresiona cualquier tecla y luego enter para regresar..." << '\n';
        cin >> enter;
      break;
      case 2:{
        system("clear");
        g->bfs(g->get_estacion_por_id( 1 ),g->get_estacion_por_id(max));
        cout << "\nIndica la estacion a cambiar ( disponibles: "<< max <<" ) -> ";
        int estacion;
        cin >> estacion;
        if (estacion <= max && estacion >= 0){
          cout << "Seleccionada: " << g->get_estacion_por_id(estacion) << "\n"
          "Indica el nuevo nombre: ";
          string nuevo_nombre;
          int ruta;
          cin >> nuevo_nombre;
          cout << "Indica la ruta a la que pertenece: ";
          cin >> ruta;
          cout << "\nEstacion: " << g->get_estacion_por_id(estacion) << " cambiada por: " << nuevo_nombre
          <<'\n';
          g->cambiar(g->get_estacion_por_id(estacion), nuevo_nombre, ruta);
        }
        else
         cout << "Valor fuera de rango";
        cout << "\nPresiona cualquier tecla y luego enter para regresar..." << '\n';
        cin >> enter;
      }break;
      case 3:{
        cout << "\nIndica el nuevo nombre: ";
        string nuevo_nombre;
        int ruta;
        cin >> nuevo_nombre;
        cout << "Indica la ruta a la que pertenece: ";
        cin >> ruta;
        cout << "Nueva estacion: " << nuevo_nombre <<'\n';
        g->aniadir( nuevo_nombre , ruta);
        cout << "\nPresiona cualquier tecla y luego enter para regresar..." << '\n';
        cin >> enter;
        max++;
      }break;
      case 4:{
        system("clear");
        g->bfs(g->get_estacion_por_id( 1 ),g->get_estacion_por_id(max));
        cout << "\nIndica la estacion a ELIMINAR ( disponibles: "<< max <<" ) -> ";
        int estacion;
        cin >> estacion;
        if (estacion <= max && estacion >= 0){
          cout << "Seleccionada: " << g->get_estacion_por_id(estacion) << "\n";
          cout << "\nEstacion: " << g->get_estacion_por_id(estacion) << " eliminada " <<'\n';
          g->borrar_estacion(g->get_estacion_por_id(estacion));
          max--;
        }
        else
         cout << "Valor fuera de rango";
        cout << "\nPresiona cualquier tecla y luego enter para regresar..." << '\n';
        cin >> enter;
      }break;
      case 5:
        cout << "\nsaliendo..." << '\n';
        return max;
      break;
      default:
        cout << "valor fuera de rango" << '\n';
    }
  }while(op != 5);
  return max;
}
