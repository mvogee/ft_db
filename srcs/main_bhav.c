
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <libft.h>
#include <ftdb.h>


t_keys	*initialize_table(int fd)
{
	int height;
	int width;
	char *line;
	t_keys *table;

	height = get_height(fd);
	fd = open_db("bvogeedb");
	get_next_line(fd, &line);
	width = get_width(line);
	close(fd);

	/* call a function that builds the table */
	table = read_table(fd, width);
	return(table);
}


//initialize a single key 
//create a link list base off the width size
//populate each node with the elements in string_array
t_keys *read_table(int fd, int width)
{
	int x;
	char *line;
	t_keys *table;
	t_header *header;
	char **string_array;
	int height;

	x = 1;
	table = NULL;
	//header = NULL;
	height = 0;
	fd = open_db("bvogeedb");
	while((x = get_next_line(fd, &line)))
	{
		if (x == -1)
		{
			perror("get next line error");
			exit(0);
		}
		if (x == 0)
			break;
		string_array = ft_strsplit(line, ' ');
		header = NULL;
		populate_headers(&header, string_array, width);
		Pushtailkey(&table, header);
		free(string_array);
		height++;
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

int	main(int argc, char **argv)
{
	int fd;
	t_keys *table;

	if (argc < 2)
		usage();
	if (argc > 2 && !strcmp(argv[1], "create"))
	{
		printf("%s\n","Coming soon is a way to build a database. Stay tuned!");
	}
	if (argc > 2 && !strcmp(argv[1], "insert"))
	{
		fd = open_db("bvogeedb");
		table = initialize_table(fd);
	}
	if (argc > 2 && !strcmp(argv[1], "query"))
	{
		fd = open_db("bvogeedb");
		table = initialize_table(fd);
		get_record(table, atoi(argv[2]));
		free(table);
	}
	fd = 0;
	close_record(fd);
	return(0);
}

