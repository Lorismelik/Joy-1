#include "user.h"
#include "searchTarifs.h"


user::user()
{
	bool checkint = 0;
	do
	{
		std::cout << "������� � ����� �� ������� (���������� �������) �� ������� �����?" << std::endl;
		std::cin >> cash;
		if (std::cin.fail())
		{
			std::cin.clear();
			std::cout << "������������ ����! ���������� ��� ���:" << std::endl;
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
		std::cout << "������� � ������� �� ������� ������� � ����?" << std::endl;
		std::cin >> calls;
		if (std::cin.fail())
		{
			std::cin.clear();
			std::cout << "������������ ����! ���������� ��� ���:" << std::endl;
		}
		else
		{
			checkint = 1;
		}
	} while (!checkint);
	checkint = 0;
	std::cout << "����� ������� ����������������� ������� ������ (� �������):" << std::endl;
	do
	{
		std::cin >> mins;
		if (std::cin.fail())
		{
			std::cin.clear();
			std::cout << "������������ ����! ���������� ��� ���:" << std::endl;
		}
		else
		{
			checkint = 1;
		}
	} while (!checkint);
	checkint = true;
	do
	{
		std::cout << "��������� ���������� ����� ������� (������: ""3241""):\n1. ������ ���� � ������ ������� \n2. �� ������ ������ ���� \n3. ��� ���� � ������ ������� \n4. �� ������ ��� ����" << std::endl;
		std::cin >> wherever;
		if ((std::cin.fail()) || (wherever < 1234) || (wherever > 4321))
		{
			std::cin.clear();
			std::cout << "������������ ����! ���������� ��� ���:" << std::endl;
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
