#include "../includes/ftdb.h"

typedef struct s_header{
	char *information;
	struct s_header *next;
}				t_header;

typedef struct s_keys{
	int id;
	t_header *header;
	struct s_keys *next;
}				t_keys;


int		find_category(char *category, t_header *header)
{
	int pos;
	t_header *tmp;

	pos = 0;
	tmp = header;
	while(tmp && strcmp(category, tmp->information))
	{
		tmp = tmp->next;
		pos++;
	}
	if (!tmp)
		pos = -1;
	return (pos);
}

void	free_node(t_header **node)
{
	free((*node)->information);
	free(*node);
}

void 	delete_element(int pos, t_header **header)
{
	t_header	*tmp;
	t_header	*prev;
	int			count;

	tmp = *header;
	count = 0;
	if (pos = 0)
	{
		tmp = tmp->next;
		prev = *header;
		free_node(&prev);
		return (tmp);
	}
	while (count < pos && tmp)
	{
		prev = tmp;
		tmp = tmp->next;
		count++;
	}
	if (!tmp)
		return (*header);
	prev->next = tmp->next;
	free_node(tmp);
	return (*header);
}

void	delete_column(char *category, t_keys *keys)
{
	// works in thoery ;p
	// needs to be tested

	int 	list_pos;
	t_keys	*tmp;

	list_pos = 0;
	tmp = keys;
	if (!keys)
	{
		printf("you need to create categories before you can delete them\n");
		return ;
	}
	list_pos = find_category(category, tmp->header);
	if (list_pos < 0)
	{
		printf("no category \"%s\" found", category);
		return ;
	}
	while (tmp)
	{
		tmp->header = delete_element(list_pos, &tmp->header);
		tmp = tmp->next;
	}
}
