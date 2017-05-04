
#include "ftdb.h"

void	new_table(int argc, char **argv)
{
	int		fd;
	char	*filepath;

	if (argc < 3)
		print_usage(NEW_TABLE);
	filepath = ft_strjoin("bogeedb/", argv[2]);
	fd = open(filepath, O_RDWR | O_APPEND);
	if (fd < 0)
		open_new_file(filepath);
	else
	{
		fprintf(stderr, "the table \"%s\" already exists\n", argv[2]);
		print_usage(NEW_TABLE);
	}
	free(filepath);
}
