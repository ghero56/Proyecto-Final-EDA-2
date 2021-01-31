#include <iostream>
#include <cstring>
#include <fstream>
#include "sqlite3.h"

using namespace std;

int callback_priuso(void* NotUsed, int argc, char** argv, char** azColName)
{
  // string extension_archivo = ".txt";
  string extension_archivo = ".csv";
  // int argc: contiene el numero de resultados
  // (array) azColName: contiene las columnas devueltas
  // (array) argv: contiene el valor
  // se manejaran archivos para guardar la informacion
  ofstream archivo;
  archivo.open("Ruta" + extension_archivo, ios::app); //Archivo donde se guardara toda la informacion

  for (int i = 0; i < argc; i++) {
    // Mostrar nombre de columna y valor
    cout << azColName[i] << ": " << argv[i] << endl;
    // Escribir en archivo nombre de columna y valor
    if(strcmp( azColName[i], "Ruta") == 0) archivo << argv[i] << "\n";
    else archivo << argv[i] << ", ";
  }
  cout << endl;

  archivo.close();
  return 0;
}

char* crear_priuso( sqlite3* db, int rc, string sql, char* zErrMsg){
  sql = "DROP TABLE IF EXISTS RutasPumabus; "
      "CREATE TABLE RutasPumabus ("  \
      "id INTEGER PRIMARY KEY NOT NULL, " \
      "Ubicacion TEXT NOT NULL, " \
      "Ruta INTEGER NOT NULL );";

  rc = sqlite3_exec(db, sql.c_str(), callback_priuso, 0, &zErrMsg);

  sql = "INSERT INTO RutasPumabus ( 'Ubicacion', 'Ruta' ) VALUES ( 'Metro CU ESTACION PRINCIPAL', '3' );";
  rc = sqlite3_exec(db, sql.c_str(), callback_priuso, 0, &zErrMsg);

  sql = "INSERT INTO RutasPumabus ( 'Ubicacion', 'Ruta' ) VALUES ( 'Facultad de ciencias ALUMNOS', '3' );";
  rc = sqlite3_exec(db, sql.c_str(), callback_priuso, 0, &zErrMsg);

  sql = "INSERT INTO RutasPumabus ( 'Ubicacion', 'Ruta' ) VALUES ( 'Facultad de ciencias PROFESORES', '3' );";
  rc = sqlite3_exec(db, sql.c_str(), callback_priuso, 0, &zErrMsg);

  sql = "INSERT INTO RutasPumabus ( 'Ubicacion', 'Ruta' ) VALUES ( 'Anexo de ingenieria', '3' );";
  rc = sqlite3_exec(db, sql.c_str(), callback_priuso, 0, &zErrMsg);

  sql = "INSERT INTO RutasPumabus ( 'Ubicacion', 'Ruta' ) VALUES ( 'Facultad de Contaduria y Administracion', '3' );";
  rc = sqlite3_exec(db, sql.c_str(), callback_priuso, 0, &zErrMsg);

  sql = "INSERT INTO RutasPumabus ( 'Ubicacion', 'Ruta' ) VALUES ( 'Escuela de Trabajo Social', '3' );";
  rc = sqlite3_exec(db, sql.c_str(), callback_priuso, 0, &zErrMsg);

  sql = "INSERT INTO RutasPumabus ( 'Ubicacion', 'Ruta' ) VALUES ( 'Metrobus CU', '3' );";
  rc = sqlite3_exec(db, sql.c_str(), callback_priuso, 0, &zErrMsg);

  sql = "INSERT INTO RutasPumabus ( 'Ubicacion', 'Ruta' ) VALUES ( 'Educacion a Distancia', '3' );";
  rc = sqlite3_exec(db, sql.c_str(), callback_priuso, 0, &zErrMsg);

  sql = "INSERT INTO RutasPumabus ( 'Ubicacion', 'Ruta' ) VALUES ( 'D.G.T.I.C.', '3' );";
  rc = sqlite3_exec(db, sql.c_str(), callback_priuso, 0, &zErrMsg);

  sql = "INSERT INTO RutasPumabus ( 'Ubicacion', 'Ruta' ) VALUES ( 'Facultad de Ciencias', '3' );";
  rc = sqlite3_exec(db, sql.c_str(), callback_priuso, 0, &zErrMsg);

  return zErrMsg;
}

int main() {

  sqlite3* db;

  // Muestra mensajes de error
  char* zErrMsg = 0;
  int rc;
  string sql;

  rc = sqlite3_open("BDRuta.db", &db);

  if (rc) {
    cout << "Base de Datos Error: " << sqlite3_errmsg(db) << endl;
    sqlite3_close(db);
    return(1);
  }

  zErrMsg = crear_priuso(db , rc , sql , zErrMsg);

  if (rc != SQLITE_OK)
  {
    fprintf(stderr, "SQL error: %s\n", zErrMsg);
    sqlite3_free(zErrMsg);
  }
  else fprintf(stdout, "Datos insertados!\n");

  string sqli = "SELECT * FROM RutasPumabus; ";
  rc = sqlite3_exec(db, sqli.c_str(), callback_priuso, 0, &zErrMsg);

  sqlite3_close(db);
  return 0;
}

//Para compilar usar (Windows):
//g++ BDD.cpp sqlite3.o -Ipath\to\sqlite3
//Para compilar usar (Linux):
//g++ -Wall sqlite3.o -ldl -pthread -o salida.out BDD.cpp
