#include "ftdb.h"

t_keys	*initialize_table(int fd)
{
	int height;
	int width;
	int value_test;

	char *line;
	t_keys *table;

	height = get_height(fd);
	fd = open_db("bogeedb"); //can we just pass the fd in?
	value_test = get_next_line(fd, &line);
	width = get_width(line, DELIM);
	close(fd); //we can close the file outside

	/* call a function that builds the table */
	table = read_table(fd, width, DELIM);
	table->width = width;
	table->height = height;
	return(table);
}


//initialize a single key
//create a link list base off the width size
//populate each node with the elements in string_array
t_keys *read_table(int fd, int width, char delim)
{
	int x;
	char *line;
	t_keys *table;
	t_header *header;
	char **string_array;
	int height;

	x = 1;
	table = NULL;
	header = NULL;
	height = 0;
	fd = open_db("bogeedb");
	while((x = get_next_line(fd, &line)))
	{
		if (x == -1)
		{
			perror("get next line error");
			exit(0);
		}
		if (x == 0)
			break;
		string_array = ft_strdelim(line, delim);
		header = NULL;
		populate_headers(&header, string_array, width);
		Pushtailkey(&table, header);
		free(string_array);
		height++; // keep track of the height. Need to store in struct
	}
	//print out the list
	// for (int i = 0; i < height; ++i)
	// {
	// 	for (int i = 0; i < width; ++i)
	// 	{
	// 		printf("%s\n", table->header->information);
	// 		table->header = table->header->next;
	// 	}
	// 	table = table->next;
	// }
	close(fd);

	return (table);
}
