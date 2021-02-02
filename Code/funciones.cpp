#include "grafo.cpp"

int callback_print(void* NotUsed, int argc, char** argv, char** azColName)
{
  for (int i = 0; i < argc; i++) {
    cout << argv[i] << " ";
  }
  cout << endl;

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

void insertar( string archivo, Grafo* g){
  FILE* a = fopen( archivo.c_str() , "r" );
  if (a == NULL) {
    fclose(a);
    return;
  }

  char nombre[80];
  int id, ruta, i = 0;
  while(fscanf( a, "%d, %79[^,], %d\n", &id, &nombre, &ruta ) != EOF){
    g->add_estacion( Vertice( nombre , id, ruta) );
    i++;
  }

  for(int j = 1; j < i; j++){
    g->add_estacion_dirigida(g->get_estacion_por_id(j) , g->get_estacion_por_id(j+1));
  }

  g->bfs(g->get_estacion_por_id(1),g->get_estacion_por_id(i));

  fclose(a);
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

char* crear_primer_uso( sqlite3* db, int rc, string sql, char* zErrMsg){
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
void admin( Grafo* g ){
  int op;
  do{
    system("clear");
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
        menu1( g );
      break;
      case 2:
      break;
      case 3:
        menuPtP( g );
      break;
      case 4:
        cout << "Guardadas correctamente" << '\n';
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
void regular( Grafo* g ){
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
        menu1( g );
      break;
      case 2:
        system("clear");
        cout << "Mostrando estaciones actuales: [estacion(ruta a la que pertenece)]" << '\n';
        g->bfs(g->get_estacion_por_id( 0 ),g->get_estacion_por_id(g->get_len()-1));
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

void menu1( Grafo* g ){
  system("clear");
  int op;
  cout << "Mostrando estaciones actuales: [estacion(ruta a la que pertenece)]" << '\n';
  cout << "(En caso de querer elegir punto de inicio"
        " y destino presiona 1 en otro caso presiona 2)" << '\n';
  g->bfs(g->get_estacion_por_id( 0 ),g->get_estacion_por_id(g->get_len()-1));
  std::cout << "\n\t-> ";
  cin >> op;
  switch (op) {
    case 1:
      menuPtP(g);
    break;
    case 2:
    return;
  }
}

void menuPtP( Grafo* g ){
  int inicio, fin, len = g->get_len();
  cout << "Indica por indice la estacion inicial ( disponibles: "<< len <<")-> ";
  cin >> inicio;
  inicio--;
  if (inicio <= len && inicio >= 0) {
    cout << "Seleccionada: " << g->get_estacion_por_id(inicio) << '\n';
  }
  cout << "Indica por indice la estacion final ( disponibles: "<< len-1 <<")-> ";
  cin >> fin;
  fin--;
  if (inicio <= len && inicio >= 0 && inicio != fin) {
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

void menuPtP_save(){

}

void menu_add(){
  system("clear");

}
