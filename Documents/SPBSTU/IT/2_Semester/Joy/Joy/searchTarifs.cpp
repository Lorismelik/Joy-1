#include "searchTarifs.h"


searchTarifs::searchTarifs(int cashtmp, int callstmp, int minstmp, int wherevertmp)
{
	tmpcash = cashtmp;
	wherevertmp /= 10;
	int allminsmonth = minstmp * callstmp;
	mininhmrg = 0; mininan = 0; minouthmrg = 0; minoutan = 0;
	switch ((int)wherevertmp / 100)
	{
	case 1:
		mininhmrg = (int)0.5 * allminsmonth;
		break;
	case 2:
		mininan = (int)0.5 * allminsmonth;
		break;
	case 3:
		minouthmrg = (int)0.5 * allminsmonth;
		break;
	case 4:
		minoutan = (int)0.5 * allminsmonth;
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
		}
		else
		{
			if (megafon[i].abonpaymin[0] == 0)
			{
				tmpprice = mininhmrg * megafon[i].price[0] + mininan * megafon[i].price[1] + minouthmrg * megafon[i].price[2] + minoutan * megafon[i].price[3];
				if (tmpprice < bestofthebest.price)
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
		}
		else
		{
			if (beeline[i].abonpaymin[0] == 0)
			{
				tmpprice = mininhmrg * beeline[i].price[0] + mininan * beeline[i].price[1] + minouthmrg * beeline[i].price[2] + minoutan * beeline[i].price[3];
				if (tmpprice < bestofthebest.price)
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
		}
		else
		{
			if (mts[i].abonpaymin[0] == 0)
			{
				tmpprice = mininhmrg * mts[i].price[0] + mininan * mts[i].price[1] + minouthmrg * mts[i].price[2] + minoutan * mts[i].price[3];
				if (tmpprice < bestofthebest.price)
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
		}
		else
		{
			if (tele2[i].abonpaymin[0] == 0)
			{
				tmpprice = mininhmrg * tele2[i].price[0] + mininan * tele2[i].price[1] + minouthmrg * tele2[i].price[2] + minoutan * tele2[i].price[3];
				if (tmpprice < bestofthebest.price)
				{
					bestofthebest.id = i;
					bestofthebest.price = tmpprice;
					bestofthebest.oper = "Tele2";
				}
			}
		}
	}
	if (bestoper == "Megafon")
	{
		return megafon[bestofthebest.id];
	}
	if (bestoper == "Beeline")
	{
		return beeline[bestofthebest.id];
	}
	if (bestoper == "Mts")
	{
		return mts[bestofthebest.id];
	}
	if (bestoper == "Tele2")
	{
		return tele2[bestofthebest.id];
	}
	else
	{
		return megafon[0];
	}
}

searchTarifs::~searchTarifs()
{
}
