#include "searchTarifs.h"

searchTarifs::searchTarifs(int callstmp, int minstmp, int wherevertmp)
{
	int allminsmonth = minstmp * callstmp * 30;
	mininhmrg = 0; mininan = 0; minouthmrg = 0; minoutan = 0;
	if (wherevertmp == 2)
	{
		mininhmrg = (int)(0.1*allminsmonth);
		mininan = (int)(0.4*allminsmonth);
		minouthmrg = (int)(0.1*allminsmonth);
		minoutan = (int)(0.4*allminsmonth);
	
	}
	else
	{
		mininhmrg= (int)(0.35*allminsmonth);
		mininan = (int)(0.15*allminsmonth);
		minouthmrg = (int)(0.35*allminsmonth);
		minoutan = (int)(0.15*allminsmonth);
	}	
	WorkingDB megafondb("megafon.dblite");
	megafon = megafondb.getDataTarifs("Megafon");
	megafondb.~WorkingDB();
	WorkingDB beelinedb("beeline.dblite");
	beeline = beelinedb.getDataTarifs("Beeline");
	beelinedb.~WorkingDB();
	WorkingDB mtsdb("mts.dblite");
	mts = mtsdb.getDataTarifs("Mts");
	mtsdb.~WorkingDB();
	WorkingDB tele2db("tele2.dblite");
	tele2 = tele2db.getDataTarifs("Tele2");
	tele2db.~WorkingDB();
}

BetterTarif searchTarifs::CheckAbonPay(int orderTarif, std::vector<dataTarifs> tarifoper)
{
	BetterTarif temple;
	float tmpprice = (float)tarifoper[orderTarif].abonpaymin[0];
	int tmp[4];
	tmp[0] = mininhmrg; tmp[1] = mininan; tmp[2] = minouthmrg; tmp[3] = minoutan;
	bool checkFromAB[4] = { 0, 0, 0, 0 };
	std::vector<int> orders, numbers;
	std::vector<float> minprice = tarifoper[orderTarif].price;
	for (int i = 3; i >= 0; i--)
	{
		numbers.push_back(i);
	}
	while (!minprice.empty())
	{
		float low = minprice[0];
		int num = numbers[0];
		int count = 0;
		for (int i = 0; i < (int)minprice.size(); i++)
		{
			if (minprice[i] < low)
			{
				low = minprice[i];
				num = numbers[i];
				count = i;
			}
		}
		orders.push_back(num);
		numbers.erase(numbers.begin() + count);
		minprice.erase(minprice.begin() + count);
	}
	std::reverse(orders.begin(), orders.end());
	int fromAB = tarifoper[orderTarif].abonpaymin[2];
	int minsAB = tarifoper[orderTarif].abonpaymin[1];
	while (fromAB != 0)
	{
		int tmpfromAB = fromAB % 10;
		if (tmpfromAB != 0)
		{
			checkFromAB[tmpfromAB - 1] = 1;
		}
		fromAB /= 10;
	}
	if (checkFromAB[orders.back()])
	{
		if (tmp[orders.back()] <= minsAB)
		{
			minsAB -= tmp[orders.back()];
			tmp[orders.back()] = 0;
		}
		else
		{
			tmp[orders.back()] -= minsAB;
			minsAB = 0;
		}
	}
	orders.pop_back();
	if (checkFromAB[orders.back()])
	{
		if (tmp[orders.back()] <= minsAB)
		{
			minsAB -= tmp[orders.back()];
			tmp[orders.back()] = 0;
		}
		else
		{
			tmp[orders.back()] -= minsAB;
			minsAB = 0;
		}
	}
	orders.pop_back();
	if (checkFromAB[orders.back()])
	{
		if (tmp[orders.back()] <= minsAB)
		{
			minsAB -= tmp[orders.back()];
			tmp[orders.back()] = 0;
		}
		else
		{
			tmp[orders.back()] -= minsAB;
			minsAB = 0;
		}
	}
	orders.pop_back();
	if (checkFromAB[orders.back()])
	{
		if (tmp[orders.back()] <= minsAB)
		{
			minsAB -= tmp[orders.back()];
			tmp[orders.back()] = 0;
		}
		else
		{
			tmp[orders.back()] -= minsAB;
			minsAB = 0;
		}
	}
	

	orders.pop_back();
	tmpprice = tmpprice + tmp[0] * tarifoper[orderTarif].price[0] + tmp[1] * tarifoper[orderTarif].price[1] + tmp[2] * tarifoper[orderTarif].price[2] + tmp[3] * tarifoper[orderTarif].price[3];
	temple.price = tmpprice;
	return temple;
}

std::vector<BetterTarif> searchTarifs::formSearchBest(std::vector<dataTarifs> oper, std::vector<BetterTarif> ArrBestTarif)
{
	for (int i = 0; i < oper[0].count; i++)
	{
		BetterTarif ArrGood;
		ArrGood.oper = oper[i].nameOper;
		ArrGood.id = i;
		ArrGood.nameTarif = oper[i].nameTarif;
		if (oper[i].abonpaymin[0] != 0)
		{
			ArrGood.price = CheckAbonPay(i, oper).price;
		}
		else
		{
			ArrGood.price = mininhmrg * oper[i].price[0] + mininan * oper[i].price[1] + minouthmrg * oper[i].price[2] + minoutan * oper[i].price[3];
		}
		ArrRates.push_back(ArrGood);
		float tmpprice = 0;
		if (oper[i].abonpaymin[0] != 0)
		{
			if (CheckAbonPay(i, oper).price <= ArrBestTarif.back().price)
			{
				if (CheckAbonPay(i, oper).price < ArrBestTarif.back().price)
				{
					ArrBestTarif.clear();
				}
				BetterTarif theBest;
				theBest.price = CheckAbonPay(i, oper).price;
				theBest.oper = oper[0].nameOper;
				theBest.id = i;
				ArrBestTarif.push_back(theBest);
			}
		}
		else
		{
			if (oper[i].abonpaymin[0] == 0)
			{
				tmpprice = mininhmrg * oper[i].price[0] + mininan * oper[i].price[1] + minouthmrg * oper[i].price[2] + minoutan * oper[i].price[3];
				if (tmpprice <= ArrBestTarif.back().price)
				{
					if (tmpprice < ArrBestTarif.back().price)
					{
						ArrBestTarif.clear();
					}
					BetterTarif theBest;
					theBest.price = tmpprice;
					theBest.oper = oper[i].nameOper;
					theBest.id = i;
					ArrBestTarif.push_back(theBest);
				}
			}
		}
	}
	return ArrBestTarif;
}

std::vector<dataTarifs> searchTarifs::SearchBest()
{
	std::vector<BetterTarif> ArrBestTarif;
	BetterTarif theBest;
	int z = 0;
	do
	{
		theBest.price = mininhmrg * megafon[z].price[0] + mininan * megafon[z].price[1] + minouthmrg * megafon[z].price[2] + minoutan * megafon[z].price[3];
		theBest.oper = "Not Found";
		theBest.id = z;
		z++;
	} while (megafon[z].abonpaymin[0] != 0);
    ArrBestTarif.push_back(theBest);
	ArrBestTarif = formSearchBest(megafon, ArrBestTarif);
	ArrBestTarif = formSearchBest(beeline, ArrBestTarif);
	ArrBestTarif = formSearchBest(mts, ArrBestTarif);
	ArrBestTarif = formSearchBest(tele2, ArrBestTarif);
	std::vector<dataTarifs> listBest;
	if (ArrBestTarif.back().oper == "Megafon")
	{
		loading();
		while (!ArrBestTarif.empty())
		{
			listBest.push_back(megafon[ArrBestTarif.back().id]);
			ArrBestTarif.pop_back();
		}
		return listBest;
	}
	if (ArrBestTarif.back().oper == "Beeline")
	{
		loading();
		while (!ArrBestTarif.empty())
		{
			listBest.push_back(beeline[ArrBestTarif.back().id]);
			ArrBestTarif.pop_back();
		}
		return listBest;
	}
	if (ArrBestTarif.back().oper == "Mts")
	{
		loading();
		while (!ArrBestTarif.empty())
		{
			listBest.push_back(mts[ArrBestTarif.back().id]);
			ArrBestTarif.pop_back();
		}
		return listBest;
	}
	if (ArrBestTarif.back().oper == "Tele2")
	{
		loading();
		while (!ArrBestTarif.empty())
		{
			listBest.push_back(tele2[ArrBestTarif.back().id]);
			ArrBestTarif.pop_back();
		}
		return listBest;
	}
	else
	{
		std::cout << "Сэр, по вашим требованиям ничего не найдено. Попробуйте ввести другие данные" << std::endl;
		return listBest;
	}
}

void searchTarifs::writeRates(int count)
{
    for (int i = 0; i < (int)ArrRates.size(); i++)
	{
		for (int j = 1; j < (int)ArrRates.size(); j++)
		{
			std::sort(ArrRates.begin(), ArrRates.end(), [](BetterTarif const &a, BetterTarif const &b) {return a.price > b.price; });
		}
	}
	if (count >= (int)ArrRates.size())
	{
		std::cout << "К сожалению такого большого количества тарифов нету в нашей базе данных (максимально: " << ArrRates.size() << ").\nПопробуйте ввести другое количетсов" << std::endl;
		std::cin >> count;
		if ((std::cin.fail()) || (count <= 0) || (count > (int)ArrRates.size()))
		{
			std::cout << "Некорректный ввод!" << std::endl;
			std::exit(1);
		}
	}
	std::cout << "Рейтинг <<TOP-" << count << ">> тарифов по вашему запросу:\n" << std::endl;
	for (int i = 0; i < count; i++)
	{
		std::cout << (i + 1) << ". " << ArrRates.back().oper << ": " << ArrRates.back().nameTarif << " : Расход (в руб.) - " << ArrRates.back().price << std::endl;
		ArrRates.pop_back();
	}
	return;
}

searchTarifs::~searchTarifs()
{
	megafon.~vector();
	beeline.~vector();
	mts.~vector();
	tele2.~vector();
}
