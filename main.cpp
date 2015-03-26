#include <stdio.h>
#include "sqlite3.h"
#include <locale.h>


static int callback(void *data, int argc, char **argv, char **azColName){
	int i;
	fprintf(stderr, "%s: ", (const char*)data);
	for (i = 0; i<argc; i++){
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}
	printf("\n");
	return 0;
}


int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "Russian");
	sqlite3 *db;
   char *zErrMsg = 0;
   int rc;
   char *sql;
   const char* data = "Callback function called";
   rc = sqlite3_open("megafon.dblite", &db);
   if (rc)
   {
	   fprintf(stderr, "Невозможно открыть базу данных: %s\n", sqlite3_errmsg(db));
	   return 0;
   }
  /* sql = "SELECT name FROM COMPANY where ID = 1";
   rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);*/
   if (rc != SQLITE_OK){
	   fprintf(stderr, "SQL error: %s\n", zErrMsg);
	   sqlite3_free(zErrMsg);
   }
   sqlite3_close(db);
   return 0;
}
