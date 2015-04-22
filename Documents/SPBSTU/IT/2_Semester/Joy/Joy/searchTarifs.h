#pragma once


#include "user.h"


class searchTarifs
{
public:
	searchTarifs(int callstmp, int minstmp, int wherevertmp);
	BetterTarif CheckAbonPay(int orderTarif, std::vector<dataTarifs> tarifoper);
	std::vector<BetterTarif> formSearchBest(std::vector<dataTarifs> oper, std::vector<BetterTarif> ArrBestTarif);
	friend void loading();
	std::vector<dataTarifs> SearchBest();
	void SearchGood();
	void writeRates(int count);
   ~searchTarifs();

private:
	int mininhmrg, mininan, minouthmrg, minoutan;
	std::vector<dataTarifs> megafon, mts, beeline, tele2;
	std::vector<BetterTarif> ArrRates;
};
