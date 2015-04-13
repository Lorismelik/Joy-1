#include "searchTarifs.h"


searchTarifs::searchTarifs(int cashtmp, int callstmp, int minstmp, int wherevertmp)
{
	tmpcash = cashtmp;
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
	WorkingDB megafondb("megafon.dblite");
	megafon.resize(megafondb.countTable());
	megafon[0].count = megafondb.countTable();
	for (int i = 0; i < megafon[0].count; i++)
	{
		megafon[i].price.resize(4);
		megafon[i].abonpaymin.resize(3);
		megafon[i].nameTarif = megafondb.ReadDB("SELECT TARIF FROM NAME")[i];
		std::string s;
		s = megafondb.ReadDB("SELECT INHMRG FROM RUSSIA")[i];
		megafon[i].price[0] = 0.75;
		megafon[i].price[1] = 0.75;
		megafon[i].price[2] = 0.75;
		std::cout << megafondb.ReadDB("SELECT INHMRG FROM RUSSIA")[i] << "\n" << (float)atof(megafondb.ReadDB("SELECT INHMRG FROM RUSSIA")[i].c_str()) << std::endl;
		megafon[i].price[3] = 0.75;
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
		beeline[i].price.resize(4);
		beeline[i].abonpaymin.resize(3);
		beeline[i].nameTarif = beelinedb.ReadDB("SELECT TARIF FROM NAME")[i];
		beeline[i].price[0] = 0.75;
		beeline[i].price[1] = 0.75;
		beeline[i].price[2] = 0.75;
		beeline[i].price[3] = 0.75;
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
		mts[i].price.resize(4);
		mts[i].abonpaymin.resize(3);
		mts[i].nameTarif = mtsdb.ReadDB("SELECT TARIF FROM NAME")[i];
		mts[i].price[0] = 0.75;
		mts[i].price[1] = 0.75;
		mts[i].price[2] = 0.75;
		mts[i].price[3] = 0.75;
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
		tele2[i].price.resize(4);
		tele2[i].abonpaymin.resize(3);
		tele2[i].nameTarif = tele2db.ReadDB("SELECT TARIF FROM NAME")[i];
		tele2[i].price[0] = 0.75;
		tele2[i].price[1] = 0.75;
		tele2[i].price[2] = 0.75;
		tele2[i].price[3] = 0.75;
		tele2[i].abonpaymin[0] = stoi(tele2db.ReadDB("SELECT ABPAY FROM RUSSIA")[i]);
		tele2[i].abonpaymin[1] = stoi(tele2db.ReadDB("SELECT MINSAB FROM RUSSIA")[i]);
		tele2[i].abonpaymin[2] = stoi(tele2db.ReadDB("SELECT FROMAB FROM RUSSIA")[i]);
	}
	tele2db.~WorkingDB();
}

BetterTarif searchTarifs::CheckAbonPay(int i, std::vector<dataTarifs> tarifoper)
{
	BetterTarif temple;
	float tmpprice = 0;
	std::vector<bool> checkFromAB(4, 0);
	int fromAB = tarifoper[i].abonpaymin[2];
	int minsAB = tarifoper[i].abonpaymin[1];
	while (fromAB != 0)
	{
		int tmpfromAB = fromAB % 10;
		if (tmpfromAB != 0)
		{
			checkFromAB[tmpfromAB - 1] = 1;
		}
		fromAB /= 10;
	}
	if (checkFromAB[0])
	{
		int tmpmininhmrg = mininhmrg;
		if (tmpmininhmrg <= minsAB)
		{
			minsAB -= tmpmininhmrg;
			tmpmininhmrg = 0;
		}
		else
		{
			tmpmininhmrg -= minsAB;
			minsAB = 0;
			tmpprice = tmpprice + tmpmininhmrg * tarifoper[i].price[0];
		}
	}
	if (checkFromAB[1])
	{
		int tmpmininan = mininan;
		if (tmpmininan <= minsAB)
		{
			minsAB -= tmpmininan;
			tmpmininan = 0;
		}
		else
		{
			tmpmininan -= minsAB;
			minsAB = 0;
			tmpprice = tmpprice + tmpmininan * tarifoper[i].price[1];
		}
	}
	if (checkFromAB[2])
	{
		int tmpminouthmrg = minouthmrg;
		if (tmpminouthmrg <= minsAB)
		{
			minsAB -= tmpminouthmrg;
			tmpminouthmrg = 0;
		}
		else
		{
			tmpminouthmrg -= minsAB;
			minsAB = 0;
			tmpprice = tmpprice + tmpminouthmrg * tarifoper[i].price[2];
		}
	}
	if (checkFromAB[3])
	{
		int tmpminoutan = minoutan;
		if (tmpminoutan <= minsAB)
		{
			minsAB -= tmpminoutan;
			tmpminoutan = 0;
		}
		else
		{
			tmpminoutan -= minsAB;
			minsAB = 0;
			tmpprice = tmpprice + tmpminoutan * tarifoper[i].price[3];
		}
	}
	if (tmpprice < bestofthebest.price)
	{
		temple.id = i;
		temple.price = tmpprice;
	}
	return temple;
}

dataTarifs searchTarifs::SearchBest()
{
	bestofthebest.price = mininhmrg * megafon[0].price[0] + mininan * megafon[0].price[1] + minouthmrg * megafon[0].price[2] + minoutan * megafon[0].price[3];
	for (int i = 0; i < megafon[0].count; i++)
	{
		float tmpprice = 0;
		if ((megafon[i].abonpaymin[0] != 0) && (megafon[i].abonpaymin[0] <= tmpcash))
		{
			bestofthebest = CheckAbonPay(i, megafon);
			bestofthebest.oper = "Megafon";
			bestofthebest.id = i;
		}
		else
		{
			if (megafon[i].abonpaymin[0] == 0)
			{
				tmpprice = mininhmrg * megafon[i].price[0] + mininan * megafon[i].price[1] + minouthmrg * megafon[i].price[2] + minoutan * megafon[i].price[3];
				if ((tmpprice < bestofthebest.price) && (tmpprice <= tmpcash))
				{
					bestofthebest.id = i;
					bestofthebest.price = tmpprice;
					bestofthebest.oper = "Megafon";
				}
			}
		}
	}
	for (int i = 0; i < beeline[0].count; i++)
	{
		float tmpprice = 0;
		if ((beeline[i].abonpaymin[0] != 0) && (beeline[i].abonpaymin[0] <= tmpcash))
		{
			bestofthebest = CheckAbonPay(i, beeline);
			bestofthebest.oper = "Beeline";
			bestofthebest.id = i;
		}
		else
		{
			if (beeline[i].abonpaymin[0] == 0)
			{
				tmpprice = mininhmrg * beeline[i].price[0] + mininan * beeline[i].price[1] + minouthmrg * beeline[i].price[2] + minoutan * beeline[i].price[3];
				if ((tmpprice < bestofthebest.price) && (tmpprice <= tmpcash))
				{
					bestofthebest.id = i;
					bestofthebest.price = tmpprice;
					bestofthebest.oper = "Beeline";
				}
			}
		}
	}
	for (int i = 0; i < mts[0].count; i++)
	{
		float tmpprice = 0;
		if ((mts[i].abonpaymin[0] != 0) && (mts[i].abonpaymin[0] <= tmpcash))
		{
			bestofthebest = CheckAbonPay(i, mts);
			bestofthebest.oper = "Mts";
			bestofthebest.id = i;
		}
		else
		{
			if (mts[i].abonpaymin[0] == 0)
			{
				tmpprice = mininhmrg * mts[i].price[0] + mininan * mts[i].price[1] + minouthmrg * mts[i].price[2] + minoutan * mts[i].price[3];
				if ((tmpprice < bestofthebest.price) && (tmpprice <= tmpcash))
				{
					bestofthebest.id = i;
					bestofthebest.price = tmpprice;
					bestofthebest.oper = "Mts";
				}
			}
		}
	}
	for (int i = 0; i < tele2[0].count; i++)
	{
		float tmpprice = 0;
		if ((tele2[i].abonpaymin[0] != 0) && (tele2[i].abonpaymin[0] <= tmpcash))
		{
			bestofthebest = CheckAbonPay(i, tele2);
			bestofthebest.oper = "Tele2";
			bestofthebest.id = i;
		}
		else
		{
			if (tele2[i].abonpaymin[0] == 0)
			{
				tmpprice = mininhmrg * tele2[i].price[0] + mininan * tele2[i].price[1] + minouthmrg * tele2[i].price[2] + minoutan * tele2[i].price[3];
				if ((tmpprice < bestofthebest.price) && (tmpprice <= tmpcash))
				{
					bestofthebest.id = i;
					bestofthebest.price = tmpprice;
					bestofthebest.oper = "Tele2";
				}
			}
		}
	}
	if (bestofthebest.oper == "Megafon")
	{
		std::cout << "Подождите, идет обработка данных";
		Sleep(3000);
		std::cout << ".";
		Sleep(3000);
		std::cout << ".";
		Sleep(3000);
		std::cout << "." << std::endl;
		megafon[bestofthebest.id].nameTarif.append(" Megafon");
		return megafon[bestofthebest.id];
	}
	if (bestofthebest.oper == "Beeline")
	{
		std::cout << "Подождите, идет обработка данных";
		Sleep(3000);
		std::cout << ".";
		Sleep(3000);
		std::cout << ".";
		Sleep(3000);
		std::cout << "." << std::endl;
		beeline[bestofthebest.id].nameTarif.append(" Beeline");
		return beeline[bestofthebest.id];
	}
	if (bestofthebest.oper == "Mts")
	{
		std::cout << "Подождите, идет обработка данных";
		Sleep(3000);
		std::cout << ".";
		Sleep(3000);
		std::cout << ".";
		Sleep(3000);
		std::cout << "." << std::endl;
		mts[bestofthebest.id].nameTarif.append(" MTS");
		return mts[bestofthebest.id];
	}
	if (bestofthebest.oper == "Tele2")
	{
		std::cout << "Подождите, идет обработка данных";
		Sleep(3000);
		std::cout << ".";
		Sleep(3000);
		std::cout << ".";
		Sleep(3000);
		std::cout << "." << std::endl;
		tele2[bestofthebest.id].nameTarif.append(" Tele2");
		return tele2[bestofthebest.id];
	}
	else
	{
		std::cout << "Сэр, попробуйте ввести другие данные" << std::endl;
		return tele2[bestofthebest.id];
	}
}

void searchTarifs::SearchGood()
{
	if (bestofthebest.price == 0)
	{
		std::cout << "Найдите сначало лучший тариф, а потом приближенные" << std::endl;
	}
	BetterTarif tmpgoodtarif;
	bestofthebest.price = bestofthebest.price + bestofthebest.price * 0,3;
	for (int i = 0; i < megafon[0].count; i++)
	{
		float tmpprice = 0;
		if ((megafon[i].abonpaymin[0] != 0) && (megafon[i].abonpaymin[0] <= (tmpcash + tmpcash*0.3)))
		{
			tmpgoodtarif = CheckAbonPay(i, megafon);
			tmpgoodtarif.oper = "Megafon";
			ArrGoodTarif.push_back(tmpgoodtarif);
		}
		else
		{
			if (megafon[i].abonpaymin[0] == 0)
			{
				tmpprice = mininhmrg * megafon[i].price[0] + mininan * megafon[i].price[1] + minouthmrg * megafon[i].price[2] + minoutan * megafon[i].price[3];
				if ((tmpprice < bestofthebest.price) && (tmpprice <= (tmpcash + tmpcash*0.3)))
				{
					tmpgoodtarif.id = i;
					tmpgoodtarif.price = tmpprice;
					tmpgoodtarif.oper = "Megafon";
					ArrGoodTarif.push_back(tmpgoodtarif);
				}
			}
		}
	}
	for (int i = 0; i < beeline[0].count; i++)
	{
		float tmpprice = 0;
		if ((beeline[i].abonpaymin[0] != 0) && (beeline[i].abonpaymin[0] <= (tmpcash + tmpcash*0.3)))
		{
			tmpgoodtarif = CheckAbonPay(i, beeline);
			tmpgoodtarif.oper = "Beeline";
			ArrGoodTarif.push_back(tmpgoodtarif);
		}
		else
		{
			if ((beeline[i].abonpaymin[0] == 0) && (tmpcash + tmpcash*0.3))
			{
				tmpprice = mininhmrg * beeline[i].price[0] + mininan * beeline[i].price[1] + minouthmrg * beeline[i].price[2] + minoutan * beeline[i].price[3];
				if (tmpprice < bestofthebest.price)
				{
					tmpgoodtarif.id = i;
					tmpgoodtarif.price = tmpprice;
					tmpgoodtarif.oper = "Beeline";
					ArrGoodTarif.push_back(tmpgoodtarif);
				}
			}
		}
	}
	for (int i = 0; i < mts[0].count; i++)
	{
		float tmpprice = 0;
		if ((mts[i].abonpaymin[0] != 0) && (mts[i].abonpaymin[0] <= (tmpcash + tmpcash*0.3)))
		{
			tmpgoodtarif = CheckAbonPay(i, mts);
			tmpgoodtarif.oper = "Mts";
			ArrGoodTarif.push_back(tmpgoodtarif);
		}
		else
		{
			if ((mts[i].abonpaymin[0] == 0) && (tmpcash + tmpcash*0.3))
			{
				tmpprice = mininhmrg * mts[i].price[0] + mininan * mts[i].price[1] + minouthmrg * mts[i].price[2] + minoutan * mts[i].price[3];
				if (tmpprice < bestofthebest.price)
				{
					tmpgoodtarif.id = i;
					tmpgoodtarif.price = tmpprice;
					tmpgoodtarif.oper = "Mts";
					ArrGoodTarif.push_back(tmpgoodtarif);
				}
			}
		}
	}
	for (int i = 0; i < tele2[0].count; i++)
	{
		float tmpprice = 0;
		if ((tele2[i].abonpaymin[0] != 0) && (tele2[i].abonpaymin[0] <= (tmpcash + tmpcash*0.3)))
		{
			tmpgoodtarif = CheckAbonPay(i, tele2);
			tmpgoodtarif.oper = "Tele2";
			ArrGoodTarif.push_back(tmpgoodtarif);
		}
		else
		{
			if (tele2[i].abonpaymin[0] == 0)
			{
				tmpprice = mininhmrg * tele2[i].price[0] + mininan * tele2[i].price[1] + minouthmrg * tele2[i].price[2] + minoutan * tele2[i].price[3];
				if ((tmpprice < bestofthebest.price) && (tmpcash + tmpcash*0.3))
				{
					tmpgoodtarif.id = i;
					tmpgoodtarif.price = tmpprice;
					tmpgoodtarif.oper = "Tele2";
					ArrGoodTarif.push_back(tmpgoodtarif);
				}
			}
		}
	}
}

searchTarifs::~searchTarifs()
{
	megafon.clear();
	beeline.clear();
	mts.clear();
	tele2.clear();
}
