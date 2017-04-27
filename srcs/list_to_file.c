#include "../includes/ftdb.h"

int 	open_clean_database(char *filename)
{
	int fd;

	fd = open(filename, O_RDWR | O_APPEND);
	if (fd < 0)
		fd = open(filename, O_CREAT | O_RDWR | O_APPEND, 0664);
	else
	{
		remove("bogeedb_backup"); // will delete the old file "bogeedb.txt" at this point if the program is stopped all the data is lost
		rename(filename, "bogeedb_backup"); // this way we alwasy have a backup to fall back on if the program fails beyond this point
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
			line = (char*)realloc(line, strlen(line) + strlen(tmp_node->information) + 1);
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

void	save_database(t_keys *database)
{
	t_keys		*tmp_keys;
	char		*write_me;
	int			fd;

	tmp_keys = database;
	write_me = NULL;
	fd = open_clean_database("bogeedb");
	if (fd < 0)
	{
		fprintf(stderr, "something went wrong opening the file");
		rename("bogeedb_backup.txt", "bogeedb.txt"); // opening a new fil failed so fall back to the backup.
		// beyond this point if the program fails the name would have to be restored manually
	}
	while (tmp_keys && fd >= 0)
	{
		write_me = construct_line(tmp_keys->header);
		printf("%s", write_me); // need to do testing to make sure my line looks right
		write(fd, write_me, strlen(write_me));
		free(write_me);
		write_me = NULL;
		tmp_keys = tmp_keys->next;
	}
	if (fd >=0)
		close(fd);
}

// t_header *init_row(void)
// {
// 	t_header *row;
//
// 	row = (t_header*)malloc(sizeof(t_header));
// 	row->next = NULL;
// 	row->information = strdup("information");
// 	return (row);
// }
//
// t_keys	*init_list(int k)
// {
// 	t_keys *key;
//
// 	key = (t_keys*)malloc(sizeof(t_keys));
// 	key->next = NULL;
// 	key->id = k;
// 	key->header = init_row();
// 	key->header->next = init_row();
// 	key->header->next->next = init_row();
// 	return (key);
// }
//
// int main() {
// 	t_keys *keys;
//
// 	keys = init_list(1);
// 	keys->next = init_list(2);
// 	keys->next->next = init_list(3);
// 	save_database(keys);
// 	return 0;
// }