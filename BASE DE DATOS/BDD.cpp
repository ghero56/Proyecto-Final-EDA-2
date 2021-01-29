//Para compilar usar:
//g++ BDD.cpp sqlite3.o -Ipath\to\sqlite3
#include <iostream>
#include <string>
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

    // Crea la tabla de SQLite
    sql = "CREATE TABLE Rutas ("  \
        "Id INT PRIMARY KEY NOT NULL," \
        "Ubicacion TEXT  NOT NULL," \
        "Ruta INT NOT NULL);";

    rc = sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);

    sql = "INSERT INTO Rutas ('Id', 'Ubicacion', 'Ruta') VALUES ('1','Metro CU ESTACION PRINCIPAL', '2');";
    rc = sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);

    sql = "INSERT INTO Rutas ('Id', 'Ubicacion') VALUES ('2','Facultad de ciencias ALUMNOS', '2');";
    rc = sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);

    sql = "INSERT INTO Rutas ('Id', 'Ubicacion') VALUES ('3','Facultad de ciencias PROFESORES', '2');";
    rc = sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);

    sql = "INSERT INTO Rutas ('Id', 'Ubicacion') VALUES ('4','Facultad de ciencias ALUMNOS', '2');";
    rc = sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);

    sql = "INSERT INTO Rutas ('Id', 'Ubicacion') VALUES ('5','Anexo de ingenieria', '2');";
    rc = sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);

    sql = "INSERT INTO Rutas ('Id', 'Ubicacion') VALUES ('6','Facultad de Contaduria y Administracion', '2');";
    rc = sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);

    sql = "INSERT INTO Rutas ('Id', 'Ubicacion') VALUES ('7','Escuela de Trabajo Social', '2');";
    rc = sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);

    sql = "INSERT INTO Rutas ('Id', 'Ubicacion') VALUES ('9','Metrobus CU', '2');";
    rc = sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);

    sql = "INSERT INTO Rutas ('Id', 'Ubicacion') VALUES ('10','Educacion a Distancia', '2');";
    rc = sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);

    sql = "INSERT INTO Rutas ('Id', 'Ubicacion') VALUES ('11','D.G.T.I.C.', '2');";
    rc = sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);

    sql = "INSERT INTO Rutas ('Id', 'Ubicacion') VALUES ('12','Facultad de Ciencias', '2');";
    rc = sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);


    char* err_msg = NULL;

    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
    }
    else
    {
        fprintf(stdout, "Datos insertados!\n");
    }

    string sqli = "SELECT * FROM Rutas; ";
    rc = sqlite3_exec(db, sqli.c_str(), callback, 0, &zErrMsg);

    sqlite3_close(db);
    return 0;
}
