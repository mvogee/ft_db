
#include <ftdb.h>


void Pushheader(t_header **head, char *data)
{
	t_header *node;

	node = (t_header *)ft_memalloc(sizeof(t_header));
	node->information = data;
	node->next = *head;
	*head = node;
}

void Pushtailheader(t_header **head, char *data)
{
	t_header *current = *head;
	if (current == NULL)
	{
		Pushheader(head, data);
	}
	else
	{
		while(current->next != NULL)
		{
			current = current->next;
		}
		Pushheader(&(current->next), data);
	}
}

void Pushkey(t_keys **head, t_header *col_head)
{
	t_keys *node;

	node = (t_keys *)ft_memalloc(sizeof(t_keys));
	node->next = *head;
	node->header = col_head;
	*head = node;
}

void Pushtailkey(t_keys **head, t_header *col_head)
{
	t_keys *current = *head;

	if (current == NULL)
		Pushkey(head, col_head);
	else
	{
		while(current->next != NULL)
		{
			current = current->next;
		}
		Pushkey(&(current->next), col_head);
	}
}

void populate_headers(t_header **header, char **array, int width)
{
	int i;

	i = -1;
	while(++i < width)
		Pushtailheader(header, array[i]);
}

t_header *initialize_columns(int size)
{
	t_header *head = NULL;
	t_header *node = NULL;
	int i;

	i = 0;
	head = (t_header*)ft_memalloc(sizeof(t_header));
	head->next = NULL;
	while(i++ < size)
	{
		node = (t_header*)ft_memalloc(sizeof(t_header));
		node->col_num = i;
		node->next = head;
		head = node;
	}
	t_header *temp;
	temp = head;
	for (int i = 0; i < size; ++i)
	{
		printf("%d\n", temp->col_num);
		temp = temp->next;
	}
	return (head);
}