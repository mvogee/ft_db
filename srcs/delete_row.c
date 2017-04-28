#include "../includes/ftdb.h"

// typedef struct s_header{
// 	char *information;
// 	struct s_header *next;
// }				t_header;
//
// typedef struct s_keys{
// 	int id;
// 	t_header *header;
// 	struct s_keys *next;
// }				t_keys;

void	free_row(t_keys *tmp)
{
	t_header *tmp_h;
	t_header *tmp_hn;

	tmp_h = tmp->header;
	while (tmp_h)
	{
		tmp_hn = tmp_h->next;
		free(tmp_h->information);
		free(tmp_h);
		tmp_h = tmp_hn;
	}
	free(tmp);
}

void 	delete_row(t_keys **databse, char *row_head)
{
	t_keys	*tmp;
	t_keys	*prev;

	tmp = *database;
	if (tmp && !strcmp(tmp->header->information, row_head))
	{
		*database = tmp->next;
		free_row(tmp);
	}
	else
	{
		while (tmp && strcmp(tmp->header->information, row_head))
		{
			prev = tmp;
			tmp = tmp->next;
		}
		if (!tmp)
			fprintf(stderr, "no row named \"%s\" found\n", row_head);
		else
		{
			prev->next = tmp->next;
			free_row(tmp);
		}
	}
}
