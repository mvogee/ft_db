#ifndef FTDB_H
# define FTDB_H


# include <fcntl.h>
# include <time.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <libft.h>
# include <ftdb.h>



typedef struct s_header{
	int col_num;
	char *information;
	struct s_header *next;

}				t_header;

typedef struct s_keys{
	int id;
	int height;
	int width;
	t_header *header;
	struct s_keys *next;
}				t_keys;

enum e_errors
{
	INVALID_COMMAND,
	CREATE_TABLE_USAGE,
	NEW_ENTRY
	//ADD_CATEGORY
};

int 	open_db(char *filename);
int		get_width(char *line);
int		get_height(int fd);
void 	close_record(int fd);
void 	usage(void);

/*link_list_functions*/
void Pushheader(t_header **head, char *data);
void Pushtailheader(t_header **head, char *data);
void Pushkey(t_keys **head, t_header *col_head);
void Pushtailkey(t_keys **head, t_header *col_head);
t_header *initialize_columns(int size);
void populate_headers(t_header **header, char **array, int width);


//main function
t_keys	*initialize_table(int fd);
void populate_headers(t_header **header, char **array, int width);
t_keys *read_table(int fd, int width);
#endif
