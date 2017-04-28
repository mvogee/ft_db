#ifndef FTDB_H
# define FTDB_H

# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include <time.h>
# include <stdlib.h>
#include "libft.h"

typedef struct s_header{
	int		col_num;
	char	*information;
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
	ADD_COLUMN,
	DELETE_COLUMN,
	ADD_ROW,
	DELETE_ROW,
	MODIFY,
	RETRIEVE
};

// main.c

void	print_usage(int reason);
void		open_new_file(char *filename);
int		open_file(char *filename);
t_entry 	init_entry(char *key, char *fname, char *lname, char *score);
void	new_entry(int argc, char **argv);
void	create_table(int argc, char **argv);
void	dispatch_input(int argc, char **argv, t_keys **database);

// list_to_file.c

int 	open_clean_database(char *filename);
char	*construct_line(t_header *header);
void	save_database(t_keys *database);

// query.c

int	get_record(t_keys *table, int row_num);
int	delete_record(t_keys *table, int row_num);

// file_to_list.c

t_keys	*initialize_table(int fd);
t_keys *read_table(int fd, int width);

// link_list_funcs.c

void Pushheader(t_header **head, char *data);
void Pushtailheader(t_header **head, char *data);
void Pushkey(t_keys **head, t_header *col_head);
void Pushtailkey(t_keys **head, t_header *col_head);
void populate_headers(t_header **header, char **array, int width);
t_header *initialize_columns(int size);

// helper_funcs.c

int		get_width(char *line);
int		get_height(int fd);
void close_record(int fd);

// add_row.c

int get_num_cols(t_header *header);
t_header	*create_row_list(int argc, char **argv, int num_cols);
void	add_row(int argc, char **argv, t_keys **database);

//delete_row.c

void	free_row(t_keys *tmp);
void 	delete_row(t_keys **databse, char *row_head);

// add_category.c

t_keys	*init_key(int id);
t_header	*init_node(char *information);
t_header	*create_headers(int argc, char **argv);
void	add_links_to_rows(int new_cols, t_keys **keys);
t_keys		*add_category(int argc, char **argv, t_keys *database);

// delete_category.c

int		find_category(char *category, t_header *header);
void	free_node(t_header **node);
void 	delete_element(int pos, t_header **header);
void	delete_column(char *category, t_keys **database);


#endif
