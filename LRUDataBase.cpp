#include <iostream>
#include <sqlite3.h>

using namespace std;

//Persistent DataBase class
class LRUDataBase {
private:
    sqlite3 *db;        //SQLite3 db pointer
    char *zErrMsg;      //err message variable
    int retCode;        //return code
    char* sql;          //sql char pointer
    sqlite3_stmt *stmt;

    /*
    Method name         : callback
    Description         : callbace funtion of query exwcution
    Input parameters    : None
    Output parameters   : None
    Return value        : int
    */
    static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
        cout << "argc is: " << argc << endl;
        for(int i = 0; i < argc; i++) {
            cout << azColName[i] << ": " << argv[i] << endl;
        }

        return 0;
    }

    /*
    Method name         : checkDBErrors
    Description         : to check if any db error
    Input parameters    : None
    Output parameters   : None
    Return value        : None
    */
    void checkDBErrors() {
        if( retCode ){
            cout << "DB Error: " << sqlite3_errmsg(db) << endl;
            closeDB();
        }
    }
public:
    /*
    Method name         : LRUDataBase
    Description         : constructor
    Input parameters    : None
    Output parameters   : None
    Return value        : None
    */
    LRUDataBase() {
        // Save the result of opening the file
        retCode = sqlite3_open("LRU.db", &db);
        checkDBErrors();
    }

    /*
    Method name         : setUpDB
    Description         : This method we can use  to initialize the DB and 
                          load the recently used data from DB to LRU cache when 
                          application restarts.
    */
    void setUpDB() {
        //Future enhancement - this can be added whenever requirements are more clear.
    }

    /*
    Method name         : createTable
    Description         : This method creates a table with 2 columns (id and name)
    */
    void createTable() {
        // Save SQL to create a table
        //DROP TABLE IF EXISTS dbo.Scores 
        sql = (char *)"CREATE TABLE EMPLOYEE (ID INT PRIMARY KEY NOT NULL, NAME TEXT NOT NULL);";
        retCode = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
    }

    /*
    Method name         : createTable
    Description         : This method insert data in table
    Input parameters    : id and name
    Output parameters   : None
    Return value        : None
    */
    void insertData(int id, string name) {
        char *query = NULL;

	//currently here trying to update DB by deleting the existing record.

        asprintf(&query, "DELETE FROM EMPLOYEE WHERE ID='%d';", id);
        sqlite3_prepare(db, query, strlen(query), &stmt, NULL);
        retCode = sqlite3_step(stmt);
        sqlite3_finalize(stmt);
        free(query); 

        asprintf(&query, "INSERT INTO EMPLOYEE ('ID', 'NAME') VALUES  ('%d', '%s');", id, name.c_str());
        sqlite3_prepare(db, query, strlen(query), &stmt, NULL);
        retCode = sqlite3_step(stmt);
        sqlite3_finalize(stmt);
        free(query);     
    }

    /*
    Method name         : createTable
    Description         : This method update existing data in table
    Input parameters    : id and name
    Output parameters   : None
    Return value        : None
    */
    void updateData(int id, string name) {
        char *query = NULL;

        asprintf(&query, "UPDATE EMPLOYEE SET NAME='%s' WHERE ID='%d';", name.c_str(), id);
        sqlite3_prepare(db, query, strlen(query), &stmt, NULL);
        retCode = sqlite3_step(stmt);
        sqlite3_finalize(stmt);
        free(query);     
    }

    /*
    Method name         : createTable
    Description         : This method get value for given key
    Input parameters    : id
    Output parameters   : None
    Return value        : None
    */
    void getData(int id) {
        char *query = NULL;

        asprintf(&query, "SELECT NAME FROM EMPLOYEE WHERE ID = (%d);", id);
    	retCode = sqlite3_exec(db, query, callback, 0, &zErrMsg);
        free(query);
    }

    /*
    Method name         : createTable
    Description         : close db
    Output parameters   : None
    Return value        : None
    */
    void closeDB() {
        sqlite3_close(db);
    }
};