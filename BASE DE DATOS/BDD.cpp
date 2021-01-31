 //Para compilar usar (Windows):
 //g++ BDD.cpp sqlite3.o -Ipath\to\sqlite3
 //Para compilar usar (Linux):
 //g++ -Wall sqlite3.o -ldl -pthread -o salida.out BDD.cpp
#include <iostream>
// #include <string>
#include <fstream>
#include "sqlite3.h"


using namespace std;

int callback(void* NotUsed, int argc, char** argv, char** azColName)
{

    // int argc: contiene el numero de resultados
    // (array) azColName: contiene las columnas devueltas
    // (array) argv: contiene el valor
    // se manejaran archivos para guardar la informacion
    ofstream archivos;
    archivos.open("Ruta.txt", ios::app); //Archivo donde se guardara toda la informacion

    for (int i = 0; i < argc; i++) {

        // Mostrar nombre de columna, valor y nueva l�nea
        cout << azColName[i] << ": " << argv[i] << endl;
        archivos << azColName[i] << ": " << argv[i] << endl;

    }

    // Inserta nueva linea
    cout << endl;
    archivos.close();
    return 0;
}

char* create( sqlite3* db, int rc, string sql, char* zErrMsg){
  sql = "DROP TABLE IF EXISTS Ruta3; "
      "CREATE TABLE Ruta3 ("  \
      "id INTEGER PRIMARY KEY NOT NULL, " \
      "Ubicacion TEXT NOT NULL, " \
      "Ruta INTEGER NOT NULL );";

  rc = sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);

  sql = "INSERT INTO Ruta3 ( 'Ubicacion', 'Ruta') VALUES ('Metro CU ESTACION PRINCIPAL', '3');";
  rc = sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);

  sql = "INSERT INTO Ruta3 ( 'Ubicacion', 'Ruta') VALUES ('Facultad de ciencias ALUMNOS', '3');";
  rc = sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);

  sql = "INSERT INTO Ruta3 ( 'Ubicacion', 'Ruta') VALUES ('Facultad de ciencias PROFESORES', '3');";
  rc = sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);

  sql = "INSERT INTO Ruta3 ( 'Ubicacion', 'Ruta') VALUES ('Anexo de ingenieria', '3');";
  rc = sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);

  sql = "INSERT INTO Ruta3 ( 'Ubicacion', 'Ruta') VALUES ('Facultad de Contaduria y Administracion', '3');";
  rc = sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);

  sql = "INSERT INTO Ruta3 ( 'Ubicacion', 'Ruta') VALUES ('Escuela de Trabajo Social', '3');";
  rc = sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);

  sql = "INSERT INTO Ruta3 ( 'Ubicacion', 'Ruta') VALUES ('Metrobus CU', '3');";
  rc = sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);

  sql = "INSERT INTO Ruta3 ( 'Ubicacion', 'Ruta') VALUES ('Educacion a Distancia', '3');";
  rc = sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);

  sql = "INSERT INTO Ruta3 ( 'Ubicacion', 'Ruta') VALUES ('D.G.T.I.C.', '3');";
  rc = sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);

  sql = "INSERT INTO Ruta3 ( 'Ubicacion', 'Ruta') VALUES ('Facultad de Ciencias', '3');";
  rc = sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);

  // Crea la tabla de SQLite
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

    zErrMsg = create(db , rc , sql , zErrMsg);

    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
    else
    {
        fprintf(stdout, "Datos insertados!\n");
    }

    string sqli = "SELECT * FROM Ruta3; ";
    rc = sqlite3_exec(db, sqli.c_str(), callback, 0, &zErrMsg);

    sqlite3_close(db);
    return 0;
}
