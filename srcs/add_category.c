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

t_keys	*init_key(int id)
{
	t_key *key;

	key = (t_key*)malloc(sizeof(t_key));
	key->header = NULL;
	key->next = NULL;
	key->id = id;
	return (key);
}

t_header	*init_node(char *information)
{
	t_header	*node;

	node = (t_header*)malloc(sizeof(t_header));
	node->next = NULL;
	node->information = strdup(information);
	return (node);
}

t_header	*create_headers(int argc, char **argv)
{
	int			count;
	t_header	*head;
	t_header	*tmp;

	count = 3;
	head = init_node(argv[2]);
	tmp = head
	while (count < argc)
	{
		tmp->next = init_node(argv[count]);
		tmp = tmp->next;
		count++;
	}
	return (head);
}

void	add_links_to_rows(int new_cols, t_keys **keys)
{
	t_keys		*tmp_k;
	t_header	*tmp_h;
	int			count;

	tmp_k = *keys;
	count = 0;
	while (tmp_k)
	{
		tmp_h = tmp_k->header;
		while (tmp_h->next)
			tmp_h = tmp_h->next;
		while (count < new_cols)
		{
			tmp_h->next = init_node("\0");
			tmp_h = tmp_h->next;
			count++;
		}
		tmp_k = tmp_k->next;
	}
}

t_keys		*add_category(int argc, char **argv, t_keys *database)
{
	// should work in theory.
	//aka needs to be tested :p
	t_keys 		*tmp_keys;
	t_header	*tmp_headers;
	int 		count;

	count = 2;
	if (!database)
	{
		database = init_key(0);
		database->header = create_headers(argc, argv);
		return (database);
	}
	tmp_keys = database;
	tmp_headers = tmp_keys->header;
	while (tmp_headers->next)
		tmp_headers = tmp_headers->next;
	while (count < argc)
	{
		tmp_headers->next = init_node(argv[count]);
		tmp_headers = tmp_headers->next;
	}
	if ((tmp_keys = tmp_keys->next))
		add_links_to_rows(argc - 2, &tmp_keys); // adds empty nodes to all the rows so that the list stays square
	return (database);
}
