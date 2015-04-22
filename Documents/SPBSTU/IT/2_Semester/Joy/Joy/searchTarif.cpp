#include "searchTarif.h"


searchTarif::searchTarif(int callstmp, int minstmp, int wherevertmp, std::string nameTarif)
{
	name = nameTarif;
	wherevertmp /= 10;
	int allminsmonth = minstmp * callstmp * 30;
	mininhmrg = 0; mininan = 0; minouthmrg = 0; minoutan = 0;
	switch ((int)wherevertmp / 100)
	{
	case 1:
		mininhmrg = (int)(mininhmrg + 0.5 * allminsmonth);
		break;
	case 2:
		mininan = (int)(mininan + 0.5 * allminsmonth);
		break;
	case 3:
		minouthmrg = (int)(minouthmrg + 0.5 * allminsmonth);
		break;
	case 4:
		minoutan = (int)(minoutan + 0.5 * allminsmonth);
		break;
	}
	switch ((int)wherevertmp / 10 - (int)wherevertmp / 100 * 10)
	{
	case 1:
		mininhmrg = (int)(mininhmrg + 0.335 * allminsmonth);
		break;
	case 2:
		mininan = (int)(mininan + 0.335 * allminsmonth);
		break;
	case 3:
		minouthmrg = (int)(minouthmrg + 0.335 * allminsmonth);
		break;
	case 4:
		minoutan = (int)(minoutan + 0.335 * allminsmonth);
		break;
	}
	switch ((int)wherevertmp - (int)wherevertmp / 10 * 10)
	{
	case 1:
		mininhmrg = (int)(mininhmrg + 0.165 * allminsmonth);
		break;
	case 2:
		mininan = (int)(mininan + 0.165 * allminsmonth);
		break;
	case 3:
		minouthmrg = (int)(minouthmrg + 0.165 * allminsmonth);
		break;
	case 4:
		minoutan = (int)(minoutan + 0.165 * allminsmonth);
		break;
	}
	const char* s = nameTarif.c_str();
	std::string temple = nameTarif;
	temple.append(".dblite");
	char* strh = new char[temple.size()];
	strcpy(strh, temple.c_str());
	WorkingDB operatorDB(strh);
	operatorM = operatorDB.getDataTarifs(s);
	operatorDB.~WorkingDB();
}

BetterTarif searchTarif::CheckAbonPay(int orderTarif)
{
	BetterTarif temple;
	float tmpprice = (float)operatorM[orderTarif].abonpaymin[0];
	int tmp[4];
	tmp[0] = mininhmrg; tmp[1] = mininan; tmp[2] = minouthmrg; tmp[3] = minoutan;
	bool checkFromAB[4] = { 0, 0, 0, 0 };
	std::vector<int> orders, numbers;
	std::vector<float> minprice = operatorM[orderTarif].price;
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
	int fromAB = operatorM[orderTarif].abonpaymin[2];
	int minsAB = operatorM[orderTarif].abonpaymin[1];
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
	tmpprice = tmpprice + tmp[0] * operatorM[orderTarif].price[0] + tmp[1] * operatorM[orderTarif].price[1] + tmp[2] * operatorM[orderTarif].price[2] + tmp[3] * operatorM[orderTarif].price[3];
	temple.price = tmpprice;
	return temple;
}

std::vector<BetterTarif> searchTarif::formSearchBest(std::vector<BetterTarif> ArrBestTarif)
{
	for (int i = 0; i < operatorM[0].count; i++)
	{
		BetterTarif ArrGood;
		ArrGood.id = i;
		ArrGood.nameTarif = operatorM[i].nameTarif;
		if (operatorM[i].abonpaymin[0] != 0)
		{
			ArrGood.price = CheckAbonPay(i).price;
		}
		else
		{
			ArrGood.price = mininhmrg * operatorM[i].price[0] + mininan * operatorM[i].price[1] + minouthmrg * operatorM[i].price[2] + minoutan * operatorM[i].price[3];
		}
		ArrRates.push_back(ArrGood);
		float tmpprice = 0;
		if (operatorM[i].abonpaymin[0] > 0)
		{
			if (CheckAbonPay(i).price <= ArrBestTarif.back().price)
			{
				if (CheckAbonPay(i).price < ArrBestTarif.back().price)
				{
					ArrBestTarif.clear();
				}
				BetterTarif theBest;
				theBest.price = CheckAbonPay(i).price;
				theBest.oper = operatorM[0].nameOper;
				theBest.id = i;
				ArrBestTarif.push_back(theBest);
			}
		}
		else
		{
			if (operatorM[i].abonpaymin[0] == 0)
			{
				tmpprice = mininhmrg * operatorM[i].price[0] + mininan * operatorM[i].price[1] + minouthmrg * operatorM[i].price[2] + minoutan * operatorM[i].price[3];
				if (tmpprice <= ArrBestTarif.back().price)
				{
					if (tmpprice < ArrBestTarif.back().price)
					{
						ArrBestTarif.clear();
					}
					BetterTarif theBest;
					theBest.price = tmpprice;
					theBest.oper = operatorM[i].nameOper;
					theBest.id = i;
					ArrBestTarif.push_back(theBest);
				}
			}
		}
	}
	return ArrBestTarif;
}

void loading()
{
	std::cout << "Подождите, идет обработка данных";
	Sleep(500);
	std::cout << ".";
	Sleep(500);
	std::cout << ".";
	Sleep(500);
	std::cout << "." << std::endl;
}

std::vector<dataTarifs> searchTarif::SearchBestTarif()
{
	std::vector<BetterTarif> ArrBestTarif;
	BetterTarif theBest;
	int z = 0;
	do
	{
		theBest.price = mininhmrg * operatorM[z].price[0] + mininan * operatorM[z].price[1] + minouthmrg * operatorM[z].price[2] + minoutan * operatorM[z].price[3];
		theBest.oper = "Not Found";
		theBest.id = z;
		z++;
	} while (operatorM[z].abonpaymin[0] != 0);
	ArrBestTarif.push_back(theBest);
	ArrBestTarif = formSearchBest(ArrBestTarif);
	std::vector<dataTarifs> listBest;
	loading();
	if (ArrBestTarif.empty())
	{
		std::cout << "Сэр, по вашим требованиям ничего не найдено. Попробуйте ввести другие данные" << std::endl;
		return listBest;
	}
	while (!ArrBestTarif.empty())
	{
		listBest.push_back(operatorM[ArrBestTarif.back().id]);
		ArrBestTarif.pop_back();
	}
	return listBest;
}

void searchTarif::writeRates(int count)
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
		std::cout << (i + 1) << ". " << name << ": " << ArrRates.back().nameTarif << " : Расход (в руб.) - " << ArrRates.back().price << std::endl;
		ArrRates.pop_back();
	}
	return;
}

searchTarif::~searchTarif()
{
	operatorM.~vector();
}
