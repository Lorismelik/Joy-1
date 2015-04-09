#pragma once


#include "user.h"


class searchTarifs : public user
{
public:
	searchTarifs(int cashtmp, int callstmp, int minstmp, int wherevertmp);
	BetterTarif CheckAbonPay(int i, std::vector<dataTarifs> tarifoper);
	dataTarifs SearchBest();
	std::string getnameBest();
	~searchTarifs();
private:
	int mininhmrg, mininan, minouthmrg, minoutan, tmpcash;
	BetterTarif bestofthebest;
	std::string bestoper;
};

