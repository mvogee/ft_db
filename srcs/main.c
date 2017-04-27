
#include "ftdb.h"


void	print_usage(int reason)
{
	printf("useage: ./bogeedb command\n");
	if (reason == INVALID_COMMAND)
	{
		printf("valid commands:\n");
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
		printf("new_entry [table][key][firstname][lastname][score]\n");
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

void	dispatch_input(int argc, char **argv)
{
	if (!strcmp(argv[1], "create_table"))
		create_table(argc, argv);
	else if (!strcmp(argv[1], "new_entry"))
		new_entry(argc, argv);
	else if (!strcmp())
	else
		print_usage(INVALID_COMMAND); // make this
}

int		main(int argc, char **argv)
{
	//create or open file bogeebd.text
	// from file create linked list
	// modify list based on user input request
	// write the linekd list contents back to a recreated bogeedb.txt file
	if (argc > 1)
		dispatch_input(argc, argv);
	else
		print_usage(INVALID_COMMAND);
	return (0);
}
