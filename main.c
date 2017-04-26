
#include "ftdb.h"

/*
** X REFACTOR
** X thinking of simply trying to write a table to a file and then reading it in every time as either a linked list or array
** X difficult part of doing this will be modifying information in the text file.
** X informaiton can be seperated by commas if there is an empty comma or ,, the information for that slot is NULL
**
** X when we want to modify or delete data simply delete the whole line and re-write the line at the bottom
** X to add a category add a new comma at the end of each line just before the new line

** Just make something super basic with a set of predefined inputs.
** making dynamic fields seems somewhat comlicated right now.
** also save the date and time of entry
*/

void	print_usage(int reason)
{
	printf("useage: ./bogeedb command\n");
	if (reason == INVALID_COMMAND)
	{
		printf("valid commands:\ncreate_table\n");
		// printf("add_category\n");
		// printf("add_ellement\n");
		// printf("delete_ellement\n");
		// printf("delete_category\n");
		printf("new_entry\n");
		printf("mod_ellement\n");
		printf("retrieve\n");
	}
	else if (reason == CREATE_TABLE_USAGE)
		printf("create_table [table_name]\n");
	// else if (reason == ADD_CATEGORY)
	// 	printf("add_category [table] [new_category]\n");
	else if (reason == NEW_ENTRY)
		printf("new_entry [table][firstname][lastname][score]\n");
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

t_entry 	init_entry(char *fname, char *lname, char *score)
{
		t_entry		new_entry;

//		new_entry.entry_date = NULL;
		ctime(&new_entry.entry_date);
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
	if (argc != 6 || table_fd < 0)
		print_usage(NEW_ENTRY);
	else
	{
		new_entry = init_entry(argv[3], argv[4], argv[5]);
		write(table_fd, &new_entry, sizeof(t_entry));
		close(table_fd);
		printf("entry complete\n");
	}
}

// t_tables	retrieve_tables(void)
// {
// 	t_tables	*tables;
// 	int			fd;
//
// 	fd = open("bogeedb_tables.db", O_CREAT | ORDWR | O_APPEND, 0664);
// }

void	create_table(int argc, char **argv)
{
	// later on will want to check that the file doenst already exist
	// for now just assume it doesnt exist. even if it does nothing will happen the file will just be opened then closed
	if (argc != 3)
		print_usage(CREATE_TABLE_USAGE);
	else
		open_new_file(argv[2]);
}

// void	add_col(int argc, char **argv)
// {
//
// 	if (argc != 4)
// 		print_usage(ADD_CATEGORY);
// 	else
// 	{
// 		// open the file given in av[2] that is the db file
// 		// copy the entire first line and reprint it adding the new category
// 		// copy all other lines adding an extra comma to the end.
// 	}
// }

void	dispatch_input(int argc, char **argv)
{
	if (!strcmp(argv[1], "create_table"))
		create_table(argc, argv);
	else if (!strcmp(argv[1], "new_entry"))
		new_entry(argc, argv);
	// else if (!strcmp(argv[1], "add_category"))
	// 	add_col(argc, argv); // make this
	// else if (!strcmp(argv[1], "add_ellement"))
	// 	add_ellement(argc, argv); // make this. add_row. maybe rename the functions
	// else if (!strcmp(argv[1], "delete_ellement"))
	// 	delete_ellement(argc, argv); // make this. delete_row
	// else if (!strcmp(argv[1], "delete_category"))
	// 	delete_category(argc, argv); // make this. delete_col
	// else if (!strcmp(argv[1], "mod_ellement"))
	// 	mod_ellement(argc, argv); // make this
	// else if (!strcmp(argv[1], "retrieve"))
	// 	retrieve(argc, argv); // make this
	else
		print_usage(INVALID_COMMAND); // make this
}

int		main(int argc, char **argv)
{
	// get user input from ac av.
	// depending on what they give us is what we will do with what they give us
	// create_table [table name]
	// add_category [table][new category]
	// add_ellement [table][name][data]
	// delete_ellement [table][name]
	// delete_category [table][category]
	// mod_ellement [table][element][category][new_data]
	// retrieve (table)(element)(category)
	if (argc > 1)
		dispatch_input(argc, argv);
	else
		print_usage(INVALID_COMMAND);
	return (0);
}
