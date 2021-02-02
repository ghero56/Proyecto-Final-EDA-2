#include "grafo.cpp"

int callback_print(void* NotUsed, int argc, char** argv, char** azColName)
{
  for (int i = 0; i < argc; i++) {
    cout << azColName[i] << ": " << argv[i] << endl;
  }
  cout << endl;

  return 0;
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
void admin(){
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
        cout << "Mostrando Rutas..." << '\n';
        menu1();
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
void regular( ){
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
        cout << "Mostrando Rutas..." << '\n';
        menu1();
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
  system("clear");
  int op;
  cout << "Mostrando estaciones actuales" << '\n';
  cout << "(En caso de querer elegir punto de inicio"
        " y destino presiona 1 en otro caso presiona 2)" << '\n';
  cin >> op;
  switch (op) {
    case 1:
      menuPtP();
    break;
    case 2:
    return;
  }
}

void menuPtP(){
  system("clear");

}

void menu_add(){
  system("clear");

}
