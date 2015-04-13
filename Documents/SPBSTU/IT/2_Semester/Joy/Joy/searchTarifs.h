#pragma once


#include "user.h"


class searchTarifs
{
public:
	searchTarifs(int cashtmp, int callstmp, int minstmp, int wherevertmp);
	BetterTarif CheckAbonPay(int i, std::vector<dataTarifs> tarifoper);
	dataTarifs SearchBest();
	void SearchGood();
	~searchTarifs();
private:
	int mininhmrg, mininan, minouthmrg, minoutan, tmpcash;
	BetterTarif bestofthebest;
	std::vector<dataTarifs> megafon, mts, beeline, tele2;
	std::vector<BetterTarif> ArrGoodTarif;
	std::string bestoper;
};

