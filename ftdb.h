#ifndef FTDB_H
# define FTDB_H

# include <stdio.h>
# include <unistd.h>

typedef struct	s_headers
{
	t_headers	*next;
	t_col		*col_head;
	char		*header;
	char		*datatype;
}				t_headers

typedef struct 	s_col
{
	t_col	*down;
	char	*data;
	char	*header;
}				t_col;

typedef struct	s_tables
{
	char		*path;
	char		*filname;
	t_tables	*next;
}				t_tables;

typedef enum e_errors
{
	INVALID_COMMAND,
	CREATE_TABLE_USAGE,

};

#endif
