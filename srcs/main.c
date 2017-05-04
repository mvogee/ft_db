
#include <ftdb.h>


void	print_usage(int reason)
{
	printf("useage: ./bogeedb [command]\n");
	if (reason == INVALID_COMMAND)
	{
		printf("new_table\n", );
		printf("valid commands:\n");
		printf("add_column\n"); //./bogeedb add_category [col_name] ...
		printf("add_row\n"); //./bogeedb add_row [row_name] (col-information) ...
		printf("delete_row\n"); //./bogeedb delete_row [row_name]
		printf("delete_column\n"); //./bogeedb delete_category [col_name]
		printf("modify\n");
		printf("query\n");
	}
	else if (reason == ADD_COLUMN)
		printf("add_column [table][col_name] ...\n");
	else if (reason == ADD_ROW)
		printf("new_entry [table][row_name](column data) ...\n");
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

	fd = open(filename, O_CREAT, 0664);
	if (fd == -1)
		fprintf(stderr, "an error occured opening the file %s\n", filename);
	else
	{
		printf("new table \"%s\" has been created\n", filename);
		close(fd);
	}
	// add_table(filename); // add the filename to the file with a list of tables (bogeedb_meta)
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
		delete_column(argv[2], database);
	else if (!strcmp(argv[1], "add_row")) // ./bogeedb add_row [row_name] (col-information) ...
		add_row(argc, argv, database);
	else if (!strcmp(argv[1], "delete_row")) // ./bogeedb delete_row [row_name]
	{
		if (argc > 3)
			print_usage(DELETE_ROW);
		delete_row(database, argv[2]);
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

int		main(int argc, char **argv)
{
	t_keys	*database;
	int		fd;
	struct stat st = {0};

	if (stat("~/bogeedb", &st) == -1)
    	mkdir("~/bogeedb", 0700);
	if (argc > 1)
	{
		if (!strcmp(argv[1], "new_table"))
			create_new_table(argc, argv); // make this going to have all files open in a bogeedb directory
		fd = open("bogeedb", O_RDWR | O_APPEND);
		if (fd < 0)
		{
			database = (t_keys*)(ft_memalloc(sizeof(t_keys)));
			database->header = NULL;
		}
		else
		{
			database = initialize_table(fd);
			//close(fd);
		}
		dispatch_input(argc, argv, &database);
		//print_list(database); print the list should be a selected function
		save_database(database);
	}
	else
		print_usage(INVALID_COMMAND);

	return (0);
}
