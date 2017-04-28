
#include "ftdb.h"


void	print_usage(int reason)
{
	printf("useage: ./bogeedb [command]\n");
	if (reason == INVALID_COMMAND)
	{
		printf("valid commands:\n");
		printf("add_column\n"); //./bogeedb add_category [col_name] ...
		printf("add_row\n"); //./bogeedb add_row [row_name] (col-information) ...
		printf("delete_row\n"); //./bogeedb delete_row [row_name]
		printf("delete_column\n"); //./bogeedb delete_category [col_name]
		printf("modify\n");
		printf("retrieve\n");
	}
	else if (reason == ADD_COLUMN)
		printf("add_column [col_name] ...\n");
	else if (reason == ADD_ROW))
		printf("new_entry [row_name](column data) ...\n");
	else if (reason == DELETE_ROW)
		printf("delete_row [row_name]\n");
	else if (reason == DELETE_COLUMN)
		printf("delete_column [col_name]\n");
	else if (reason == MODIFY)
		printf("modify [row_id][col_name][new_data]\n");
	else if (reason == RETRIEVE)
		printf("retrieve (row_id)(col_name)\n");
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

t_entry 	init_entry(char *key, char *fname, char *lname, char *score)
{
		t_entry		new_entry;

//		new_entry.entry_date = NULL;
		// printf("%s\n", ctime(&new_entry.entry_date));
		new_entry.key = atoi(key);
		new_entry.entry_date = time(0);
		strncpy(new_entry.fname, fname, 32);
		strncpy(new_entry.lname, lname, 32);
		new_entry.score = atoi(score);
		return (new_entry);
}

void	new_entry(int argc, char **argv)
{
	int			table_fd;
	t_entry		new_entry;

	table_fd = open_file(argv[2]);
	if (argc != 7 || table_fd < 0)
		print_usage(NEW_ENTRY);
	else
	{
		new_entry = init_entry(argv[3], argv[4], argv[5], argv[6]);
		write(table_fd, &new_entry, sizeof(t_entry));
		close(table_fd);
		printf("entry complete\n");
	}
}

void	create_table(int argc, char **argv)
{
	if (argc != 3)
		print_usage(CREATE_TABLE_USAGE);
	else
		open_new_file(argv[2]);
}

void	dispatch_input(int argc, char **argv, t_keys **database)
{
	if (!strcmp(argv[1], "add_column")) //./bogeedb add_category [col_name] ...
		*database = add_category(argc, argv, *database);
	else if (!strcmp(argv[1], "delete_column")) // ./bogeedb delete_category [col_name]
		new_entry(argc, argv, database);
	else if (!strcmp(argv[1], "add_row")) // ./bogeedb add_row [row_name] (col-information) ...
		add_row(argc, argv, database);
	else if (!strcmp(argv[1], "delete_row")) // ./bogeedb delete_row [row_name]
	{
		if (argc > 3)
			print_usage(DELETE_ROW);
		delete_row(database, argv[2]);
	}
	else if(!strcmp(argv[1], "modify"))
		modify_data() // do we have this yet?
	else if (!strcmp(argv[1], "query"))
		get_record(*database, atoi(argv[2]));
	else
		print_usage(INVALID_COMMAND);
}

int		main(int argc, char **argv)
{
	//create or open file bogeebd.text
	// from file create linked list
	// modify list based on user input request
	// write the linekd list contents back to a recreated bogeedb.txt file
	t_keys	*database;
	int		fd;

	if (argc > 1)
	{
		fd = open(filename, O_RDWR | O_APPEND);
		if (fd < 0)
			database = NULL;
		else
		{
			database = initialize_table(fd);
			close(fd);
		}
		dispatch_input(argc, argv, &database);
		save_database(database);
	}
	else
		print_usage(INVALID_COMMAND);

	return (0);
}
