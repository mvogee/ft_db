
#include "ftdb.h"

int 	open_clean_database(char *filename, char *backup)
{
	int fd;

	fd = open(filename, O_RDWR | O_APPEND);
	if (fd < 0)
		fd = open(filename, O_CREAT | O_RDWR | O_APPEND, 0664);
	else
	{
		remove(backup);
		rename(filename, backup);
		fd = open(filename, O_CREAT | O_RDWR | O_APPEND, 0664);
	}
	return (fd);
}

char	*construct_line(t_header *header)
{
	t_header	*tmp_node;
	char 		*line;

	tmp_node = header;
	line = NULL;
	while(tmp_node)
	{
		if (line)
		{
			line = (char*)realloc(line, strlen(line) + strlen(tmp_node->information) + 2);
			line = strcat(line, ",");
			line = strcat(line, tmp_node->information);
		}
		else
			line = strdup(tmp_node->information);
		tmp_node = tmp_node->next;
	}
	line = (char*)realloc(line, strlen(line) + 1);
	line = strcat(line, "\n");
	return (line);
}

void	save_database(t_keys *database, char *filepath)
{
	t_keys		*tmp_keys;
	char		*write_me;
	int			fd;
	char		*backup_name;

	tmp_keys = database;
	write_me = NULL;
	backup_name = ft_strjoin(filepath, "_backup");
	fd = open_clean_database(filepath, backup_name);
	if (fd < 0)
	{
		fprintf(stderr, "something went wrong opening the file");
		rename(backup_name, filepath);
	}
	while (tmp_keys && fd >= 0)
	{
		write_me = construct_line(tmp_keys->header);
		write(fd, write_me, strlen(write_me));
		free(write_me);
		write_me = NULL;
		tmp_keys = tmp_keys->next;
	}
	if (fd >= 0)
		close(fd);
}
