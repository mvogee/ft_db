
#include <ftdb.h>

void		print_usage(int reason)
{
	printf(ANSI_COLOR_RED "useage: ./bogeedb [command] => [command data]" ANSI_COLOR_RESET "\n");
	if (reason == INVALID_COMMAND)
	{
		printf("valid commands:\n");
		printf(ANSI_COLOR_YELLOW"new_table [table]\n");
		printf("add_column [table][col_name]\n");
		printf("add_row [table][row_name]...\n");
		printf("delete_row [table][row_name]\n");
		printf("delete_column [table][col_name]\n");
		printf("modify [table][row_id][col_name][data]\n");
		printf("query\n" ANSI_COLOR_RESET);
	}
	else if (reason == ADD_COLUMN)
		printf("add_column [table][col_name] ...\n");
	else if (reason == ADD_ROW)
		printf("add_row [table][row_name](column data) ...\n");
	else if (reason == DELETE_ROW)
		printf("delete_row [table][row_name]\n");
	else if (reason == DELETE_COLUMN)
		printf("delete_column [table][col_name]\n");
	else if (reason == MODIFY)
		printf("modify [table][row_id][col_name][new_data]\n");
	else if (reason == RETRIEVE)
		printf("retrieve (row_id)(col_name)\n");
	else if (reason == QUERY)
		printf("query (row_id)\n");
	else if (reason == NEW_TABLE)
		printf("new_table [table_name]\n");
	exit(EXIT_FAILURE);
}

void		open_new_file(char *filename)
{
	int			fd;

	fd = open(filename, O_RDWR | O_APPEND | O_CREAT, 0664);
	if (fd == -1)
		fprintf(stderr, "an error occured opening the file %s\n", filename);
	else
	{
		printf("new table \"%s\" has been created\n", filename);
		close(fd);
	}
}

int			open_file(char *filename)
{
	int fd;

	fd = open(filename, O_RDWR | O_APPEND);
	return (fd);
}

void		dispatch_input(int argc, char **argv, t_keys **database)
{
	if (!strcmp(argv[1], "add_column"))
	{
		*database = add_category(argc, argv, *database);
	}
	else if (!strcmp(argv[1], "delete_column"))
		delete_column(argv[3], database);
	else if (!strcmp(argv[1], "add_row"))
		add_row(argc, argv, database);
	else if (!strcmp(argv[1], "delete_row"))
	{
		if (argc > 4)
			print_usage(DELETE_ROW);
		delete_row(database, argv[3]);
	}
	else if(!strcmp(argv[1], "modify"))
		modify_data(argc, argv, database);
	else if (!strcmp(argv[1], "query"))
		get_record(argc, argv, database);
	else
		print_usage(INVALID_COMMAND);
}

void		print_list(t_keys *database)
{
	printf("%s\n", "printing lists");
	t_keys *tmp;
	t_header *tmp_h;

	tmp = database;
	while (tmp)
	{
		tmp_h = tmp->header;
		while (tmp_h)
		{
			printf("%s, ", tmp_h->information);
			tmp_h = tmp_h->next;
		}
		printf("\n");
		tmp = tmp->next;
	}
}

int			main(int argc, char **argv)
{
	t_keys	*database;
	char	*filepath;
	int		fd;
	struct stat st;

	if (stat("bogeedb", &st) == -1)
	{
    	mkdir("bogeedb", 0764);
		printf("created dir\n");
	}
	if (argc > 2)
	{
		if (!strcmp(argv[1], "new_table"))
			new_table(argc, argv);
		else
		{
			filepath = ft_strjoin("bogeedb/", argv[2]);
			fd = open(filepath, O_RDWR | O_APPEND);
			if (fd < 0)
			{
				fprintf(stderr, "the table \"%s\" was not found.\n", argv[2]);
				print_usage(INVALID_COMMAND);
			}
			database = initialize_table(fd, filepath);
			if (!database)
			{
				database = (t_keys*)(ft_memalloc(sizeof(t_keys)));
				database->header = NULL;
			}
			print_list(database);
			dispatch_input(argc, argv, &database);
			save_database(database, filepath);
			free(filepath);
		}
	}
	else
		print_usage(INVALID_COMMAND);

	return (0);
}
