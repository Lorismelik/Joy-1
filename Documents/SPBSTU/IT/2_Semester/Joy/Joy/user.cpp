#include "user.h"
#include "searchTarifs.h"


user::user()
{
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
}
