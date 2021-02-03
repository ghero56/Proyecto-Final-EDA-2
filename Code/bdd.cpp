#include "funciones.cpp"

sqlite3* BDD::create(){
  sqlite3* db;
  if(fileExists("bdd_unam.db")){
    system("cp ./bdd_unam.db ./bdd_unam_backup.db");
    int rc = sqlite3_open("bdd_unam.db", &db);
    char* zErrMsg = NULL;

    if (rc != SQLITE_OK) {
      cout << "Base de Datos Error: " << sqlite3_errmsg(db) << endl;
      sqlite3_close(db);
      sqlite3_free(zErrMsg);
      return NULL;
    }
  }else if(fileExists("bdd_unam_backup.db")){
    system("cp ./bdd_unam_backup.db ./bdd_unam.db");
    int rc = sqlite3_open("bdd_unam.db", &db);
    char* zErrMsg = NULL;

    if (rc != SQLITE_OK) {
      cout << "Base de Datos Error: " << sqlite3_errmsg(db) << endl;
      sqlite3_close(db);
      sqlite3_free(zErrMsg);
      return NULL;
    }
  }else{
    int rc = sqlite3_open("bdd_unam.db", &db);
    string sql;
    char* zErrMsg = crear_primer_uso(db,rc,sql,zErrMsg);
    system("cp ./bdd_unam.db ./bdd_unam_backup.db");

    if (rc != SQLITE_OK) {
      cout << "Base de Datos Error: " << sqlite3_errmsg(db) << endl;
      sqlite3_close(db);
      sqlite3_free(zErrMsg);
      return NULL;
    }
  }
  return db;
}

int BDD::start(Grafo* g){
  if(fileExists("Rutas.csv")){
    system("rm Ruta.csv");
  }
  auto db = create();
  string sql = "SELECT * FROM RutasPumabus; ";
  char* zErrMsg;
  int rc;

  rc = sqlite3_exec(db, sql.c_str(), serializar, 0, &zErrMsg);
  if (rc != SQLITE_OK)
  {
    fprintf(stderr, "SQL error: %s\n", zErrMsg);
    sqlite3_free(zErrMsg);
  }
  int i = insertar( "Ruta.csv" , g );

  system("rm Ruta.csv");
  sqlite3_close(db);
  return i;
}

void BDD::update(Grafo* g,string n, string nn, int nr){
  auto db = create();
  string sql = "UPDATE RutasPumabus SET Ubicacion = '" + nn + "' WHERE id == " +
  to_string((g->get_vertice( n ))->get_distancia()) + ";";
  char* zErrMsg = NULL;
  int rc;

  rc = sqlite3_exec(db, sql.c_str(), callback_print, 0, &zErrMsg);
  if (rc != SQLITE_OK)
  {
    fprintf(stderr, "SQL error: %s\n", zErrMsg);
    sqlite3_free(zErrMsg);
  }

  sql = "SELECT * FROM RutasPumabus; ";

  rc = sqlite3_exec(db, sql.c_str(), serializar, 0, &zErrMsg);
  if (rc != SQLITE_OK)
  {
    fprintf(stderr, "SQL error: %s\n", zErrMsg);
    sqlite3_free(zErrMsg);
  }

  insertar( "Ruta.csv" , g );

  system("rm Ruta.csv");

  sqlite3_close(db);
}

int BDD::add(Grafo* g, string nn, int nr){
  auto db = create();
  string sql = "INSERT INTO RutasPumabus(Ubicacion, Ruta) VALUES( '"+ nn +"', " + to_string(nr) + ");";
  char* zErrMsg = NULL;
  int rc;

  rc = sqlite3_exec(db, sql.c_str(), callback_print, 0, &zErrMsg);
  if (rc != SQLITE_OK)
  {
    fprintf(stderr, "SQL error: %s\n", zErrMsg);
    sqlite3_free(zErrMsg);
  }

  sql = "SELECT * FROM RutasPumabus; ";

  rc = sqlite3_exec(db, sql.c_str(), serializar, 0, &zErrMsg);
  if (rc != SQLITE_OK)
  {
    fprintf(stderr, "SQL error: %s\n", zErrMsg);
    sqlite3_free(zErrMsg);
  }

  int i = insertar( "Ruta.csv" , g );

  system("rm Ruta.csv");

  sqlite3_close(db);
  return i;
}

int BDD::erase(Grafo* g, string estacion){
  auto db = create();
  string sql = "DELETE FROM RutasPumabus WHERE id == '" +
  to_string((g->get_vertice( estacion ))->get_distancia()) + "';";
  char* zErrMsg = NULL;
  int rc;

  rc = sqlite3_exec(db, sql.c_str(), callback_print, 0, &zErrMsg);
  if (rc != SQLITE_OK)
  {
    fprintf(stderr, "SQL error: %s\n", zErrMsg);
    sqlite3_free(zErrMsg);
  }

  sql = "SELECT * FROM RutasPumabus; ";

  rc = sqlite3_exec(db, sql.c_str(), serializar, 0, &zErrMsg);
  if (rc != SQLITE_OK)
  {
    fprintf(stderr, "SQL error: %s\n", zErrMsg);
    sqlite3_free(zErrMsg);
  }

  insertar( "Ruta.csv" , g );
  int i = sqlite3_last_insert_rowid( db );

  system("rm Ruta.csv");
  sqlite3_close(db);
  return i;
}
