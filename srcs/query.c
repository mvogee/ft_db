#include <ftdb.h>

/*
 * Function will work by passing in the current version of the table.
 * will return the record based off the key value by iterating through
 * the link list, print each node, until NUll
 */

void	get_record(int argc, char **argv, t_keys **database)
{
	int		i;
	int		row_num;
	t_keys	tmp;

	i = 0;
	if (argc < 3)
		print_usage(QUERY);
	if (!database || !(*database)->header)
	{
		fprintf(stderr, "you have no categories! add some headers first using add_category\n");
		print_usage(QUERY);
	}
	tmp = **database;
	row_num = atoi(argv[3]);
	if (tmp.height < row_num + 1)
	{
		printf("%s\n", "Please select row inside the table");
		exit(0);
	}
	while (i < row_num)
	{
		tmp = *(tmp.next);
		i++;
	}
	while (tmp.header->next != NULL)
	{
		printf("%s ", tmp.header->information);
		tmp.header = tmp.header->next;
	}
	printf("%s\n", tmp.header->information);
}

void	print_column(int argc, char **argv, t_keys **database)
{
	int		i;
	int		col_num;
	char 	*col_name;
	t_keys	tmp;

	if (argc < 3)
		print_usage(QUERY);
	if (!database || !(*database)->header)
	{
		fprintf(stderr, "you have no categories! add some headers first using add_category\n");
		print_usage(QUERY);
	}
	tmp = **database;
	col_name = argv[3];
	col_num = column_number(tmp, col_name);
	if (col_num == -1)
	{
		printf("%s\n", "Please select column inside the table");
		exit(0);
	}
	while ((tmp.next) != NULL)
	{
		i = -1;
		while (++i < col_num)
			tmp.header = tmp.header->next;
		printf("%s\n", tmp.header->information);
		tmp = *(tmp.next);
	}
	i = -1;
	while (++i < col_num)
		tmp.header = tmp.header->next;
	printf("%s\n", tmp.header->information);
}

void	print_key(int argc, char **argv, t_keys **database)
{
	char 	*key_name;
	int		i;
	int		height;
	t_keys	tmp;

	if (argc < 3)
		print_usage(QUERY);
	if (!database || !(*database)->header)
	{
		fprintf(stderr, "you have no categories! add some headers first using add_category\n");
		print_usage(QUERY);
	}
	tmp = **database;
	key_name = argv[3];
	height = tmp.height;
	i = 1;
	while (ft_strcmp(tmp.header->information,key_name) != 0)
	{
		if (i > height - 1)
		{
			fprintf(stderr, "no key value in table selected\n");
			exit(0);
		}
		tmp = *(tmp.next);
		i++;
	}
	while (tmp.header->next != NULL)
	{
		tmp.header = tmp.header->next;
		printf("%s ", tmp.header->information);
	}
}

void	print_select(int argc, char **argv, t_keys **database)
{
	int		i;
	int		col_num;
	int		height;
	char 	*col_name;
	char	*key_name;
	t_keys	tmp;

	if (argc < 3)
		print_usage(QUERY);
	if (!database || !(*database)->header)
	{
		fprintf(stderr, "you have no categories! add some headers first using add_category\n");
		print_usage(QUERY);
	}
	tmp = **database;
	col_name = argv[3];
	key_name = argv[4];
	height = tmp.height;
	col_num = column_number(tmp, col_name);
	if (col_num == -1)
	{
		printf("%s\n", "Please select column inside the table");
		exit(0);
	}
	i = 1;
	while (ft_strcmp(tmp.header->information,key_name) != 0)
	{
		if (i > height - 1)
		{
			fprintf(stderr, "no key value in table selected\n");
			exit(0);
		}
		tmp = *(tmp.next);
		i++;
	}
	i = -1;
	while (++i < col_num)
		tmp.header = tmp.header->next;
	printf("%s\n", tmp.header->information);
}
