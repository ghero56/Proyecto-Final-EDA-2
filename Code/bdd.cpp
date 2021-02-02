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

void BDD::start(Grafo* g){
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

  insertar( "Ruta.csv" , g );

  system("rm Ruta.csv");
  sqlite3_close(db);
}

void BDD::update(){
  /*auto db = create();
  string sql;
  char* zErrMsg = NULL;
  int rc;

  sqlite3_close(db);*/
}

void BDD::erase(){
  /*auto db = create();
  string sql;
  char* zErrMsg = NULL;
  int rc;

  sqlite3_close(db);*/
}

void BDD::add(){
  /*auto db = create();
  string sql;
  char* zErrMsg = NULL;
  int rc;

  sqlite3_close(db);*/
}
