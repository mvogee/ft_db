
#include "ftdb.h"

int		open_db(char *filename)
{
	int fd;

	fd = open(filename, O_CREAT | O_RDWR | O_APPEND, 0777);
	if (fd == -1)
		perror("open record error");
	return fd;
}

int		get_width(char *line, char delim)
{
	int width;
	int pointer;

	width = 0;
	pointer = 1;
	while (*line)
	{
		if (pointer != (*line == delim))
			if (pointer)
				width++;
		pointer = (*line == delim);
		line++;
	}
	return width;
}

int		get_height(int fd)
{
	int height;
	int flag;
	char *line;

	flag = 1;
	height = 0;
	while(flag)
	{
		if (flag == -1)
		{
			perror("get next line error");
			exit(0);
		}
		flag = get_next_line(fd, &line);
		if (flag == 0)
			break;
		height++;
	}
	close(fd);
	return height;
}

t_header	*initialize_columns(int size)
{
	t_header *head = NULL;
	t_header *node = NULL;
	int i;

	i = 0;
	head = (t_header*)ft_memalloc(sizeof(t_header));
	head->next = NULL;
	while(i++ < size)
	{
		node = (t_header*)ft_memalloc(sizeof(t_header));
		node->col_num = i;
		node->next = head;
		head = node;
	}
	t_header *temp;
	temp = head;
	for (int i = 0; i < size; ++i)
		temp = temp->next;
	return (head);
}

int			column_number(t_keys header, char* column_name)
{
	int col_num;

	col_num = 0;
	while (header.header->next)
	{	
		if (ft_strcmp(header.header->information, column_name) == 0)
		{
			return col_num;
			break ;
		}
		header.header = header.header->next;
		col_num++;
	}
	if (ft_strcmp(header.header->information, column_name) == 0)
		return col_num;
	return (-1);
}
