
#include <ftdb.h>

int open_db(char *filename)
{
	int fd;

	fd = open(filename, O_CREAT | O_RDWR | O_APPEND, 0777);
	if (fd == -1)
		perror("open record error");
	return fd;
}

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

void 	usage(void)
{
	printf("%s\n", "Usage - select one of the following");
	printf("%s\n", "1. create:");
	printf("%s\n", "2. insert: #key, #first name, #last name, #age");
	printf("%s\n", "3. delete: #key");
	printf("%s\n", "4. print: #key");
}