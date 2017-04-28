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

#endif
