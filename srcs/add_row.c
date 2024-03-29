#include "ftdb.h"

int			get_num_cols(t_header *header)
{
	t_header *tmp;
	int count;

	count = 0;
	tmp = header;
	while (tmp)
	{
		tmp = tmp->next;
		count++;
	}
	return (count);
}

t_header	*create_row_list(int argc, char **argv, int num_cols)
{
	int			count;
	int			i;
	char		*information;
	t_header	*head;
	t_header	*tmp;

	count = 1;
	i = 4;
	head = init_node(argv[3]);
	tmp = head;
	while (count < num_cols)
	{
		if (i < argc)
			information = argv[i];
		else
			information = "\0";
		tmp->next = init_node(information);
		tmp = tmp->next;
		count++;
		i++;
	}
	return (head);
}

void		add_row(int argc, char **argv, t_keys **database)
{
	int		cols;
	t_keys	*tmp;

	if (argc < 4)
		print_usage(ADD_ROW);
	if (!database || !(*database)->header)
	{
		fprintf(stderr, "You have no categories! Add some headers frist using add_column\n");
		print_usage(ADD_ROW);
	}
	tmp = *database;
	cols = get_num_cols(tmp->header);
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = init_key(tmp->id + 1);
	tmp = tmp->next;
	tmp->header = create_row_list(argc, argv, cols);
}
