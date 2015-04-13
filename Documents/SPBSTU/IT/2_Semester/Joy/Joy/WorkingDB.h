#pragma once


#include <string>
#include <stdio.h>
#include "sqlite3.h"
#include <locale.h>
#include <iostream>
#include <vector>
#include <windows.h>


struct dataTarifs
{
	std::string nameTarif;
	std::vector<float> price;
	std::vector<int> abonpaymin;
	int count;
};
struct BetterTarif
{
	int id;
	float price;
	std::string oper;
};
class WorkingDB
{
public:
	WorkingDB(char* nameDB);
	friend static int callback(void *data, int argc, char **argv, char **azColName);
	std::vector<std::string> ReadDB(char* sqlcmd);
	int countTable();
	~WorkingDB();
private:
	sqlite3 *db;
};

