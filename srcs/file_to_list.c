#include "ftdb.h"

t_keys	*initialize_table(int fd, char *filepath)
{
	int height;
	int width;
	int value_test;
	char *line;
	t_keys *table;

	height = get_height(fd);
	fd = open_db(filepath);
	value_test = get_next_line(fd, &line);
	width = get_width(line, DELIM);
	close(fd);
	table = read_table(fd, width, DELIM, filepath);
	if (table)
	{
		table->height = height;
		table->width = width;
	}
	return(table);
}

t_keys *read_table(int fd, int width, char delim, char *filepath)
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
	fd = open_db(filepath);
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
		height++;
	}
	close(fd);
	return (table);
}
