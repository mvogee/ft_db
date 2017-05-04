
#include "ftdb.h"

void	new_table(int argc, char **argv)
{
	struct stat st = {0};

	if (stat("~/bogeedb", &st) == -1)
    	mkdir("~/bogeedb", 0700);

}
