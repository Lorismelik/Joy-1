#include "user.h"


int main(void)
{
   setlocale(LC_ALL, "Russian");
   int answer;
   std::cout << "Вас приветствует <<Тарификатор-3000>>!\n Выберите один из пунктов:\n\n1. Поиск выгодного тарифа.\n0. Выйти из программы" << std::endl;
   std::cin >> answer;
   int a = 0;
   while (a != 1)
   {
	   if ((answer == 1) || (answer == 0))
	   {
		   switch (answer)
		   {
		   case 0:
			   return 0;
			   break;
		   case 1:
			   user megapax;
			   megapax.getnameBest();
			   break;
		   }
	   }
	   else
	   {
		   std::cout << "Неккоректный ввод! Попробуйте еще раз:" << std::endl;
		   std::cin.clear();
		   std::cin.sync();
		   std::cout << "Выберите один из пунктов:\n\n1. Поиск выгодного тарифа.\n0. Выйти из программы" << std::endl;
		   std::cin >> answer;
		   a = 0;
	   }
   }
   system("pause");
   return 0;
}
