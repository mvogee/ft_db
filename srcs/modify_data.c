#include "ftdb.h"

static void	find_row_and_mod(char **argv, int column, t_keys **database)
{
	t_keys		*tmp_d;
	t_header	*tmp_h;
	int			i;

	tmp_d = *database;
	i = 0;
	while (tmp_d)
	{
		tmp_h = tmp_d->header;
		if (!strcmp(tmp_h->information, argv[3]))
		{
			while (i < column)
			{
				tmp_h = tmp_h->next;
				i++;
			}
			free(tmp_h->information);
			tmp_h->information = strdup(argv[5]);
			break ;
		}
		tmp_d = tmp_d->next;
	}
	if (!tmp_d)
	{
		fprintf(stderr, "no key \"%s\" found\n", argv[3]);
		print_usage(MODIFY);
	}
}

void	modify_data(int argc, char **argv, t_keys **database)
{
	int		column;

	column = 0;
	if (!(*database))
		fprintf(stderr, "there is no data to modify! add some data first\n");
	if (!(*database) || argc != 6)
		print_usage(MODIFY);
	column = find_category(argv[4], (*database)->header); // called form delete_category
	if (column == -1)
		print_usage(MODIFY);
	find_row_and_mod(argv, column, database);
}
