#pragma once


#include <string>
#include <stdio.h>
#include "sqlite3.h"
#include <locale.h>
#include <iostream>
#include <vector>
#include <windows.h>
#include <algorithm>
#include <list>
#include <stdlib.h>


struct dataTarifs
{
	std::string nameTarif;
	std::vector<float> price;
	std::vector<int> abonpaymin;
	int count;
	std::string nameOper;
};
struct BetterTarif
{
	int id;
	float price;
	std::string oper;
	std::string nameTarif;
};
class WorkingDB
{
public:
	WorkingDB(char* nameDB);
	friend static int callback(void *data, int argc, char **argv, char **azColName);
	std::vector<std::string> ReadDB(char* sqlcmd);
	std::vector<dataTarifs> getDataTarifs(std::string oper);
	int countTable();
	~WorkingDB();
private:
	sqlite3 *db;
};
