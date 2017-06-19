#include <fstream>
#include "../../include/Randmap.hpp"

Randmap::Randmap()
{
  std::ofstream file("maps/RANDOM", std::ios::out | std::ios::trunc);

  std::srand(std::time(0));

  int i = 0;
  int j = 0;
  map.push_back("xxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
  file << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxx" << std::endl;
  while (i < 26)
    {
      std::string tmp = "x";
      j = 1;
      while (j < 28)
	{
	  if ((i == 0 && (j == 2 || j == 1 || j == 26 || j == 27))
	      || (i == 1 && (j == 1 || j == 27))
	      || (i == 25 && (j == 2 || j == 1 || j == 26 || j == 27))
	      || (i == 24 && (j == 1 || j == 26))
	      )
	      tmp += 'n';
	  else
	    {
	      int rand = std::rand() % 10;
	      if (rand == 0)
		tmp += 'x';
	      else if (rand == 1)
		tmp += 'w';
	      else
		tmp += 'n';
	    }
	  j += 1;
	}
      tmp += 'x';
      file << tmp << std::endl;
      map.push_back(tmp);
      i += 1;
    }
  map.push_back("xxxxxxxxxxxxxxxxxxxxxxxxxxxx");
  file << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxx" << std::endl;
}
