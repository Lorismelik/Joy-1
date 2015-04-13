#include "WorkingDB.h"


struct callbackData
{
	std::vector<std::string> values;
};

WorkingDB::WorkingDB(char* nameBD)
{
	int rc;
	rc = sqlite3_open(nameBD, &db);
	if (rc)
	{
		fprintf(stderr, "Невозможно открыть базу данных: %s\n", sqlite3_errmsg(db));
		std::terminate();
	}
}

int callback(void *data, int argc, char **argv, char **azColName)
{
	int i = 0;
	callbackData* tmpdb = (callbackData*) data;
	char* tmple;
	for (i; i < argc; i++)
    {
		tmple = argv[i];
		tmpdb->values.push_back(tmple);
	}
	return 0;
}

std::vector<std::string> WorkingDB::ReadDB(char* sqlcmd)
{
	char *zErrMsg = 0;
	int rc;
	callbackData data;
	char* sql = sqlcmd;
	rc = sqlite3_exec(db, sql, callback, (void*)&data, &zErrMsg);
	if (rc != SQLITE_OK)
	{
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}
	return data.values;
}
int WorkingDB::countTable()
{
	char *zErrMsg = 0;
	int rc;
	char* sql = "SELECT COUNT(*) FROM RUSSIA";
	callbackData data;
	rc = sqlite3_exec(db, sql, callback, (void*)&data, &zErrMsg);
	if (rc != SQLITE_OK)
	{
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}
	int count = stoi(data.values.back());
	return count;
}
WorkingDB::~WorkingDB()
{
	sqlite3_close(db);
}
