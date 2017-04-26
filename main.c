
#include "ftdb.h"

/*
** WHY NOT INNITIALLY DO AN ARRAY OF LINKED LISTS WHERE THE ELLEMENTS ALL HAVE KEYS.
** ALSO THIS WAY WE CAN GET THE CORRECT ELLEMENT IN O(1)
** THE ELLEMENT WILL HOLD A LINKED LIST HEAD FOR THAT ELLEMENT THAT CONTAINS ALL THE HEADERS
** THE COLUMN HEADERS CAN THEN BE SEARCHED FOR THE CORRECT HEADER NUMBER AND THE SPECIFIC DATA GOTTEN FROM THE LIST
**
** THE DOWN SIDE TO THIS IS THAT ADDING A NEW HEADER WOULD MEAN GOING THROUGH EVERY ENTRY AND ADDING THAT LINK TO THE LIST
** BUT THE WAY I AM DOING IT NOW WITH THE RIGHT LINK IN THE COLUMNS WOULD HAVE TO DO THAT ANYWAY.
*/

// I NEED A FILE THAT I KNOW THE NAME OF TO STORE THE LIST OF TABLES IN SO THAT I CAN RETRIEVE IT ON RUNNING
void	print_usage(int reason)
{
	printf("useage: ./bogeedb command.\n")
	if (reason == INVALID_COMMAND)
		printf("valid commands: create_table\n add_category\n add_ellement\n delete_ellement\n delete_category\n delete_table\n mod_ellement\n retrieve\n");
	else if (reason == CREATE_TABLE_USAGE)
		printf("create_table [table_name]\n");
}

int		open_new_record(char *filename)
{
	int			fd;

	fd = open(filename, O_CREAT | O_RDWR | O_APPEND, 0664);
	if (fd == -1)
		perror("an error occured opening the file %s\n", filename);
	else
		printf("new table %s has been created\n", filename);
	return (fd);
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
	int			fd;
	char		*filename;
	t_tables	*tables;

	if (argc > 3)
	{
		print_usage(CREATE_TABLE_USAGE);
		return ;
	}
	fd = open_new_record(filename);
	//create the new file with the name filename.db
}

void	dispatch_input(int argc, char **argv)
{
	if (!strcmp(argv[1], "create-table"))
		create_table(argc, argv); // make this
	else if (!strcmp(argv[1], "add-category"))
		add_category(argc, argv); // make this. add_col
	else if (!strcmp(argv[1], "add-ellement"))
		add_ellement(argc, argv); // make this. add_row. maybe rename the functions
	else if (!strcmp(argv[1], "delete-ellement"))
		delete_ellement(argc, argv); // make this. delete_row
	else if (!strcmp(argv[1], "delete-category"))
		delete_category(argc, argv); // make this. delete_col
	else if (!strcmp(argv[1], "mod-ellement"))
		mod_ellement(argc, argv); // make this
	else if (!strcmp(argv[1], "retrieve"))
		retrieve(argc, argv); // make this
	else
		print_usage(NO_VALID_COMMAND); // make this
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
	{
		dispatch_input(argc, argv);
	}
	else
	{
	}
	return (0);
}
