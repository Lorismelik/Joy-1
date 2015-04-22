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

std::vector<dataTarifs> WorkingDB::getDataTarifs(std::string oper) 
{
	std::vector<dataTarifs> strTarif;
	strTarif.resize(countTable());
	strTarif[0].count = countTable();
	for (int i = 0; i < strTarif[0].count; i++)
	{
        strTarif[i].nameOper = oper;
		strTarif[i].price.resize(4);
		strTarif[i].abonpaymin.resize(3);
		strTarif[i].nameTarif = ReadDB("SELECT TARIF FROM NAME")[i];
		std::string s;
		s = ReadDB("SELECT INHMRG FROM RUSSIA")[i];
		std::replace(s.begin(), s.end(), '.', ',');
		strTarif[i].price[0] = (float)atof(s.c_str());
		s = ReadDB("SELECT INAN FROM RUSSIA")[i];
		std::replace(s.begin(), s.end(), '.', ',');
		strTarif[i].price[1] = (float)atof(s.c_str());
		s = ReadDB("SELECT OUTHMRG FROM RUSSIA")[i];
		std::replace(s.begin(), s.end(), '.', ',');
		strTarif[i].price[2] = (float)atof(s.c_str());
		s = ReadDB("SELECT OUTAN FROM RUSSIA")[i];
		std::replace(s.begin(), s.end(), '.', ',');
		strTarif[i].price[3] = (float)atof(s.c_str());
		strTarif[i].abonpaymin[0] = stoi(ReadDB("SELECT ABPAY FROM RUSSIA")[i]);
		strTarif[i].abonpaymin[1] = stoi(ReadDB("SELECT MINSAB FROM RUSSIA")[i]);
		strTarif[i].abonpaymin[2] = stoi(ReadDB("SELECT FROMAB FROM RUSSIA")[i]);
	}
	return strTarif;
}

WorkingDB::~WorkingDB()
{
	sqlite3_close(db);
}
