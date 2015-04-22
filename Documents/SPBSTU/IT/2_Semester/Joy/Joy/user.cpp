#include "user.h"
#include "searchTarifs.h"
#include "searchTarif.h"


user::user()
{
	bool checkint = 0;
	do
	{
		std::cout << "������� � ������� �� ������� ������� � ����?" << std::endl;
		std::cin >> calls;
		if ((std::cin.fail()) || (calls <= 0))
		{
			std::cin.clear();
			std::cin.sync();
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
		if ((std::cin.fail()) || (mins <= 0))
		{
			std::cin.clear();
			std::cin.sync();
			std::cout << "������������ ����! ���������� ��� ���:" << std::endl;
		}
		else
		{
			checkint = 1;
		}
	} while (!checkint);
	checkint = 0;
    std::cout << "���� �� � ��� ������������ �� ��������� ������� �����?\n1. ��\n2. ���" << std::endl;
	do
	{
		int answer;
		std::cin >> answer;
		if ((std::cin.fail()) || ((answer != 2) && (answer != 1)))
		{
			std::cin.clear();
			std::cin.sync();
			std::cout << "������������ ����! ���������� ��� ���:" << std::endl;
		}
		else
		{
			if (answer == 1)
			{
                std::cout << "�������� �������� ������� �����:\n1. �������\n2. ������\n3. ���\n4. Tele2" << std::endl;
				do
				{
					int answer2;
					std::cin >> answer2;
					if ((std::cin.fail()) || ((answer2 != 1) && (answer2 != 2) && (answer2 != 3) && (answer2 != 4)))
					{
						std::cin.clear();
						std::cin.sync();
						std::cout << "������������ ����! ���������� ��� ���:" << std::endl;
					}
					else
					{
						switch (answer2)
						{
						case 1:
							oper = "megafon";
							break;
						case 2:
							oper = "beeline";
							break;
						case 3:
							oper = "mts";
							break;
						case 4:
							oper = "tele2";
							break;
						}
                        std::cout << "��������� ���������� ����� ������� (������: ""3241""):\n1. ������ ���� � ������ ������� \n2. �� ������ ������ ���� \n3. ��� ���� � ������ ������� \n4. �� ������ ��� ����" << std::endl;
						do
						{
							std::cin >> wherever;
							if ((std::cin.fail()) || (wherever != 1234) || (wherever != 1243) || (wherever != 1324) || (wherever != 1342) || (wherever != 1423) || (wherever != 1432) || (wherever != 2134) || (wherever != 2143) || (wherever != 2314) || (wherever != 2341) || (wherever != 2413) || (wherever != 2431) || (wherever != 3124) || (wherever != 3142) || (wherever != 3214) || (wherever != 3241) || (wherever != 3412) || (wherever != 3421) || (wherever != 4123) || (wherever != 4132) || (wherever != 4213) || (wherever != 4231) || (wherever != 4312) || (wherever != 4321))
							{
								std::cin.clear();
								std::cin.sync();
								std::cout << "������������ ����! ���������� ��� ���:" << std::endl;
							}
							else
							{
								checkint = 1;
							}
						} while (!checkint);
					}
				} while (!checkint);
			}
			else
			{
				oper = '0';
                std::cout << "���� �� ���� �������?\n1. � �������� ������������� �������\n2. �� ��� ������� ������" << std::endl;
				do
				{
					std::cin >> wherever;
					if ((std::cin.fail()) || ((wherever != 1) && (wherever != 2)))
					{
						std::cin.clear();
						std::cin.sync();
						std::cout << "������������ ����! ���������� ��� ���:" << std::endl;
					}
					else
					{
						checkint = 1;
					}
				} while (!checkint);
			}
		}
	} while (!checkint);
}

void user::getnameBest()
{
	int answer;
	if (oper == "0")
	{
		searchTarifs tarif(calls, mins, wherever);
		std::vector<dataTarifs> listtarif = tarif.SearchBest();
		if (listtarif.size() == 1)
		{
			std::cout << "\n����� �������� ����� ��� ���:\n";
		}
		else
		{

			std::cout << "\n����� �������� ������ ��� ���:\n";
		}
		while (!listtarif.empty())
		{
			std::cout << listtarif.back().nameOper << ": " << listtarif.back().nameTarif << "\n";
			listtarif.pop_back();
		}
		std::cout << "�������� ���� �� �������:\n1. ������� ������� ������� �� ����� �������.\n2. ��������� ��� ������ (����� ������).\n0. ����� �� ���������\n" << std::endl;
		std::cin >> answer;
		switch (answer)
		{
		case 1:
			std::cout << "������� ���������� ����� ��������:\n" << std::endl;
			int countstr;
			std::cin >> countstr;
			tarif.writeRates(countstr);
			std::cout << "�������� ���� �� �������:\n1. ��������� ��� ������ (����� ������).\n0. ����� �� ���������\n" << std::endl;
			std::cin >> answer;
			switch (answer)
			{
			case 1:
				return;
				break;
			case 0:
				std::exit(1);
				break;
			default:
				std::cout << "��������� ������!" << std::endl;
				return;
				break;
			}
			break;
		case 2:
			return;
			break;
		case 0:
			std::exit(1);
			break;
		default:
			std::cout << "��������� ������!" << std::endl;
			std::exit(1);
			break;
		}
	}
	else
	{
		searchTarif tarif(calls, mins, wherever, oper);
        std::vector<dataTarifs> listtarif = tarif.SearchBestTarif();
		if (listtarif.size() == 1)
		{
			std::cout << "\n����� �������� ����� ��� ���:\n";
		}
		else
		{
			std::cout << "\n����� �������� ������ ��� ���:\n";
		}
		
		while (!listtarif.empty())
		{
			std::cout << listtarif.back().nameOper << ": " << listtarif.back().nameTarif << "\n\n";
			listtarif.pop_back();
		}
		std::cout << "�������� ���� �� �������:\n1. ������� ������� ������� �� ����� �������.\n2. ��������� ��� ������ (����� ������).\n0. ����� �� ���������\n" << std::endl;
		std::cin >> answer;
		switch (answer)
		{
		case 1:
			std::cout << "������� ���������� ����� ��������:\n" << std::endl;
			int countstr;
			std::cin >> countstr;
			tarif.writeRates(countstr);
			std::cout << "�������� ���� �� �������:\n1. ��������� ��� ������ (����� ������).\n0. ����� �� ���������\n" << std::endl;
			std::cin >> answer;
			switch (answer)
			{
			case 1:
				return;
				break;
			case 0:
				std::exit(1);
				break;
			default:
				std::cout << "��������� ������!" << std::endl;
				return;
				break;
			}
			break;
		case 2:
			return;
			break;
		case 0:
			std::exit(1);
			break;
		default:
			std::cout << "��������� ������!" << std::endl;
			return;
			break;
		}
	}
}
