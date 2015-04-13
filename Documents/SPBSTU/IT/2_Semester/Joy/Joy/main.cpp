#include "user.h"


int main(void)
{
   setlocale(LC_ALL, "Russian");
   user megapax;
   std::cout << "\n" << megapax.getnameBest() << std::endl;
   system("pause");
   return 0;
}