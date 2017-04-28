#include "ftdb.h"

int		get_width(char *line)
{
	int width;
	int pointer;

	width = 0;
	pointer = 1;
	while (*line)
	{
		if (pointer != (*line == ' '))
			if (pointer)
				width++;
		pointer = (*line == ' ');
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

void close_record(int fd)
{
	close(fd);
}
