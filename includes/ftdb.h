#ifndef FTDB_H
# define FTDB_H

# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include <time.h>
# include <stdlib.h>

typedef struct 		s_entry
{
	int			key;
	time_t		entry_date;
	char 		fname[32];
	char		lname[32];
	int			score;
}					t_entry;

typedef struct	s_headers
{
	t_headers	*next;
	t_col		*col_head;
	char		*header;
	char		*datatype;
}				t_headers
//
// typedef struct 	s_col
// {
// 	t_col	*down;
// 	char	*data;
// }				t_col;

enum e_errors
{
	INVALID_COMMAND,
	CREATE_TABLE_USAGE,
	NEW_ENTRY
	//ADD_CATEGORY
};

#endif
