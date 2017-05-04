
#include <ftdb.h>

void	print_usage(int reason)
{
	printf("useage: ./bogeedb [command]\n");
	if (reason == INVALID_COMMAND)
	{
		printf("valid commands:\n");
		printf("new_table\n"); // ./bogeedb new_table [new_table]
		printf("add_column\n"); //./bogeedb add_category [col_name] ...
		printf("add_row\n"); //./bogeedb add_row [row_name] (col-information) ...
		printf("delete_row\n"); //./bogeedb delete_row [row_name]
		printf("delete_column\n"); //./bogeedb delete_category [col_name]
		printf("modify\n"); // ./bogeedb modify [table][row][column][new_data]
		printf("query\n");
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

int		open_file(char *filename)
{
	int fd;

	fd = open(filename, O_RDWR | O_APPEND);
	return (fd);
}

// void	create_table(int argc, char **argv)
// {
// 	if (argc != 3)
// 		print_usage(CREATE_TABLE_USAGE);
// 	else
// 		open_new_file(argv[2]);
// }

void	dispatch_input(int argc, char **argv, t_keys **database)
{
	if (!strcmp(argv[1], "add_column")) //./bogeedb add_category [col_name] ...
	{
		*database = add_category(argc, argv, *database);
	}
	else if (!strcmp(argv[1], "delete_column")) // ./bogeedb delete_category [col_name]
		delete_column(argv[3], database);
	else if (!strcmp(argv[1], "add_row")) // ./bogeedb add_row [row_name] (col-information) ...
		add_row(argc, argv, database);
	else if (!strcmp(argv[1], "delete_row")) // ./bogeedb delete_row [row_name]
	{
		if (argc > 4)
			print_usage(DELETE_ROW);
		delete_row(database, argv[3]);
	}
	else if(!strcmp(argv[1], "modify"))
		modify_data(argc, argv, database);
	else if (!strcmp(argv[1], "query"))
	{
		get_record(argc, argv, database);
		//get_record(*database, atoi(argv[2]));
	}
	else
		print_usage(INVALID_COMMAND);
}

void	print_list(t_keys *database)
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

//create or open file bogeebd.text
// from file create linked list
// modify list based on user input request
// write the linekd list contents back to a recreated bogeedb.txt file

// remember to after doing this inciment all argv calls by 1 to get correct info
int		main(int argc, char **argv)
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
			fd = open(filepath, O_RDWR | O_APPEND); // this will need to be changed to open specified file
			if (fd < 0)
			{
				fprintf(stderr, "the table \"%s\" was not found.\n", argv[2]);
				print_usage(INVALID_COMMAND);
			}
			database = initialize_table(fd, filepath); // segfault
			if (!database)
			{
				database = (t_keys*)(ft_memalloc(sizeof(t_keys)));
				database->header = NULL;
			}
			dispatch_input(argc, argv, &database);
			//print_list(database); print the list should be a selected function
			save_database(database, filepath);
			free(filepath);
		}
	}
	else
		print_usage(INVALID_COMMAND);

	return (0);
}
