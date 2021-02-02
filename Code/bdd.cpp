#include "funciones.cpp"

sqlite3* BDD::create(){
  try{
    system("cp ./bdd_unam.db ./bdd_unam_backup.db");
    sqlite3* db;
    int rc = sqlite3_open("bdd_unam.db", &db);

    if (rc) {
      cout << "Base de Datos Error: " << sqlite3_errmsg(db) << endl;
      sqlite3_close(db);
      return NULL;
    }
    return db;
  }catch(...){
    sqlite3* db;
    int rc = sqlite3_open("bdd_unam.db", &db);

    if (rc) {
      cout << "Base de Datos Error: " << sqlite3_errmsg(db) << endl;
      sqlite3_close(db);
      return NULL;
    }
    string sql;
    char* zErrMsg = crear_primer_uso(db,rc,sql,zErrMsg);
    sqlite3_free(zErrMsg);

    return db;
  }
}

void BDD::start(){
  auto db = create();
  string sql;
  char* zErrMsg;
  int rc;

  string sqli = "SELECT * FROM RutasPumabus; ";
  rc = sqlite3_exec(db, sqli.c_str(), callback_print, 0, &zErrMsg);
  if (rc != SQLITE_OK)
  {
    fprintf(stderr, "SQL error: %s\n", zErrMsg);
    sqlite3_free(zErrMsg);
  }

  sqlite3_close(db);
}

void BDD::update(){
  auto db = create();
  string sql;
  char* zErrMsg;
  int rc;

  sqlite3_close(db);
}
void BDD::erase(){
  auto db = create();
  string sql;
  char* zErrMsg;
  int rc;

  sqlite3_close(db);
}
void BDD::add(){
  auto db = create();
  string sql;
  char* zErrMsg;
  int rc;

  sqlite3_close(db);
}
