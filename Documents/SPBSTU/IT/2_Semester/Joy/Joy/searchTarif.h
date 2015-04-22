#pragma once


#include "user.h"


class searchTarif
{
public:
	searchTarif(int callstmp, int minstmp, int wherevertmp, std::string nameTarif);
	~searchTarif();
	friend void loading();
	BetterTarif CheckAbonPay(int orderTarif);
	std::vector<BetterTarif> formSearchBest(std::vector<BetterTarif> ArrBestTarif);
	std::vector<dataTarifs> SearchBestTarif();
	void writeRates(int count);

private:
	int mininhmrg, mininan, minouthmrg, minoutan;
	std::string name;
	std::vector<BetterTarif> ArrRates;
	std::vector<dataTarifs> operatorM;
};
