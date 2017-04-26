
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <libft.h>
#include <ftdb.h>

typedef struct s_header{
	char *information;
	struct s_header *next;
}				t_header;

typedef struct s_keys{
	int id;
	t_header *header;
	struct s_keys *next;
}				t_keys;

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
	char **line;

	flag = 1;
	height = 0;
	line = NULL:
	while(flag)
	{
		if (flag == -1)
			perror("get next line error");
		flag = get_next_line(fd, line);
		height++;
	}
	return height;
}

int	store_information(int fd)
{
	int height;
	int width;
	char **line;

	fd = open_db("bvogeedb");
	height = get_height(fd);
	get_next_line(fd, &line);
	width = get_width(*line);

	printf("height: %d\n", height);
	printf("width: %d\n", width);
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

int	main(int argc, char **argv)
{
	int fd;
	t_header

	if (argc < 2)
		usage();
	if (argc == 2 && !strcmp(argv[1], "create"))
	{
		printf("%s\n","Coming soon is a way to build a database. Stay tuned!");
	}
	if (argc == 2 && !strcmp(argv[1], "insert"))
	{
		fd = open_db("bvogeedb");
		//check the current length and width of the database
		//ask user for new column info
		//update attribute link list with new node

	}
	close_record(fd);
	return(0);

}





/*read in information to get the length of the first line 