#include "user.h"
#include "searchTarifs.h"


static std::vector <std::string> tempdb;


user::user()
{
	WorkingDB megafondb("megafon.dblite");
	megafon.resize(megafondb.countTable());
	megafon[0].count = megafondb.countTable();
	for (int i = 0; i < megafon[0].count; i++)
	{
		megafon[i].nameTarif = megafondb.ReadDB("SELECT TARIF FROM NAME")[i];
		megafon[i].price[0] = (float)stof(megafondb.ReadDB("SELECT INHMRG FROM RUSSIA")[i]);
		megafon[i].price[1] = (float)stof(megafondb.ReadDB("SELECT INAN FROM RUSSIA")[i]);
		megafon[i].price[2] = (float)stof(megafondb.ReadDB("SELECT OUTHMRG FROM RUSSIA")[i]);
		megafon[i].price[3] = (float)stof(megafondb.ReadDB("SELECT OUTAN FROM RUSSIA")[i]);
		megafon[i].abonpaymin[0] = stoi(megafondb.ReadDB("SELECT ABPAY FROM RUSSIA")[i]);
		megafon[i].abonpaymin[1] = stoi(megafondb.ReadDB("SELECT MINSAB FROM RUSSIA")[i]);
		megafon[i].abonpaymin[2] = stoi(megafondb.ReadDB("SELECT FROMAB FROM RUSSIA")[i]);
	}
	megafondb.~WorkingDB();
	WorkingDB beelinedb("beeline.dblite");
	beeline.resize(beelinedb.countTable());
	beeline[0].count = beelinedb.countTable();
	for (int i = 0; i < beeline[0].count; i++)
	{
		beeline[i].nameTarif = beelinedb.ReadDB("SELECT TARIF FROM NAME")[i];
		beeline[i].price[0] = (float)stof(beelinedb.ReadDB("SELECT INHMRG FROM RUSSIA")[i]);
		beeline[i].price[1] = (float)stof(beelinedb.ReadDB("SELECT INAN FROM RUSSIA")[i]);
		beeline[i].price[2] = (float)stof(beelinedb.ReadDB("SELECT OUTHMRG FROM RUSSIA")[i]);
		beeline[i].price[3] = (float)stof(beelinedb.ReadDB("SELECT OUTAN FROM RUSSIA")[i]);
		beeline[i].abonpaymin[0] = stoi(beelinedb.ReadDB("SELECT ABPAY FROM RUSSIA")[i]);
		beeline[i].abonpaymin[1] = stoi(beelinedb.ReadDB("SELECT MINSAB FROM RUSSIA")[i]);
		beeline[i].abonpaymin[2] = stoi(beelinedb.ReadDB("SELECT FROMAB FROM RUSSIA")[i]);
	}
	beelinedb.~WorkingDB();
	WorkingDB mtsdb("mts.dblite");
	mts.resize(mtsdb.countTable());
	mts[0].count = mtsdb.countTable();
	for (int i = 0; i < mts[0].count; i++)
	{
		mts[i].nameTarif = mtsdb.ReadDB("SELECT TARIF FROM NAME")[i];
		mts[i].price[0] = (float)stof(mtsdb.ReadDB("SELECT INHMRG FROM RUSSIA")[i]);
		mts[i].price[1] = (float)stof(mtsdb.ReadDB("SELECT INAN FROM RUSSIA")[i]);
		mts[i].price[2] = (float)stof(mtsdb.ReadDB("SELECT OUTHMRG FROM RUSSIA")[i]);
		mts[i].price[3] = (float)stof(mtsdb.ReadDB("SELECT OUTAN FROM RUSSIA")[i]);
		mts[i].abonpaymin[0] = stoi(mtsdb.ReadDB("SELECT ABPAY FROM RUSSIA")[i]);
		mts[i].abonpaymin[1] = stoi(mtsdb.ReadDB("SELECT MINSAB FROM RUSSIA")[i]);
		mts[i].abonpaymin[2] = stoi(mtsdb.ReadDB("SELECT FROMAB FROM RUSSIA")[i]);
	}
	mtsdb.~WorkingDB();
	WorkingDB tele2db("tele2.dblite");
	tele2.resize(tele2db.countTable());
	tele2[0].count = tele2db.countTable();
	for (int i = 0; i < tele2[0].count; i++)
	{
		tele2[i].nameTarif = tele2db.ReadDB("SELECT TARIF FROM NAME")[i];
		tele2[i].price[0] = (float)stof(tele2db.ReadDB("SELECT INHMRG FROM RUSSIA")[i]);
		tele2[i].price[1] = (float)stof(tele2db.ReadDB("SELECT INAN FROM RUSSIA")[i]);
		tele2[i].price[2] = (float)stof(tele2db.ReadDB("SELECT OUTHMRG FROM RUSSIA")[i]);
		tele2[i].price[3] = (float)stof(tele2db.ReadDB("SELECT OUTAN FROM RUSSIA")[i]);
		tele2[i].abonpaymin[0] = stoi(tele2db.ReadDB("SELECT ABPAY FROM RUSSIA")[i]);
		tele2[i].abonpaymin[1] = stoi(tele2db.ReadDB("SELECT MINSAB FROM RUSSIA")[i]);
		tele2[i].abonpaymin[2] = stoi(tele2db.ReadDB("SELECT FROMAB FROM RUSSIA")[i]);
	}
	tele2db.~WorkingDB();
	bool checkint = 0;
	do
	{
		std::cout << "Сколько в месяц вы тратите (планируете тратить) на сотовую связь?" << std::endl;
		std::cin >> cash;
		if (std::cin.fail())
		{
			std::cin.clear();
			std::cout << "Некорректный ввод! Попробуйте еще раз:" << std::endl;
			std::cin.sync();
		}
		else
		{
			checkint = 1;
		}
	} while (!checkint);
	checkint = 0;
	do
	{
		std::cout << "Сколько в среднем вы делаете звонков в день?" << std::endl;
		std::cin >> calls;
		if (std::cin.fail())
		{
			std::cin.clear();
			std::cout << "Некорректный ввод! Попробуйте еще раз:" << std::endl;
		}
		else
		{
			checkint = 1;
		}
	} while (!checkint);
	checkint = 0;
	std::cout << "Какая средняя продолжительность каждого звонка (в минутах):" << std::endl;
	do
	{
		std::cin >> mins;
		if (std::cin.fail())
		{
			std::cin.clear();
			std::cout << "Некорректный ввод! Попробуйте еще раз:" << std::endl;
		}
		else
		{
			checkint = 1;
		}
	} while (!checkint);
	checkint = true;
	do
	{
		std::cout << "Раставьте приоритеты своих звонков (пример: ""3241""):\n1. Внутри сети и внутри региона \n2. По России внутри сети \n3. Вне сети и внутри региона \n4. По России вне сети" << std::endl;
		std::cin >> wherever;
		if ((std::cin.fail()) || (wherever < 1234) || (wherever > 4321))
		{
			std::cin.clear();
			std::cout << "Некорректный ввод! Попробуйте еще раз:" << std::endl;
		}
		else
		{
			checkint = 1;
		}
	} while (!checkint);
}

std::string user::getnameBest()
{
	searchTarifs tarif(cash, calls, mins, wherever);
	return tarif.SearchBest().nameTarif;
}

user::~user()
{
	megafon.clear();
	beeline.clear();
	mts.clear();
	tele2.clear();
}
