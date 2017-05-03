
#include "includes/libft.h"
#include <stdio.h>
#include <unistd.h>

int main(void)
{
	//9 pieces of data
	char *test = "data1,data2,data3,,,data7,,data9, ";

	//5 pieces of data
	//char *test = "d,,data1,data2,,data3";
	char **array;
	int i;

	i = 0;
	array = ft_strdelim(test, ',');
	while (array[i] != NULL)
		printf("%s\n", array[i++]);
}

