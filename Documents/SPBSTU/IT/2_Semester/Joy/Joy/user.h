#pragma once


#include "WorkingDB.h"



class user
{
public:
	user();
	~user();
	std::string getnameBest();
	std::vector<dataTarifs> megafon, mts, beeline, tele2;
private:
	int cash, calls, mins, wherever;
};

