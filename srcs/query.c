#include <ftdb.h>

/*
 * Function will work by passing in the current version of the table.
 * will return the record based off the key value by iterating through
 * the link list, print each node, until NUll
 */

void	get_record(int argc, char **argv, t_keys **database)
{
	int		i;
	int		row_num;
	t_keys	tmp;

	i = 0;
	if (argc < 3)
		print_usage(QUERY);
	if (!database || !(*database)->header)
	{
		fprintf(stderr, "you have no categories! add some headers first using add_category\n");
		print_usage(QUERY);
	}
	tmp = **database;
	row_num = atoi(argv[3]);
	if (tmp.height < row_num)
	{
		printf("%s\n", "Please select row inside the tmp");
		exit(0);
	}
	while (i < row_num)
	{
		tmp = *(tmp.next);
		i++;
	}
	printf("row info");
	while (tmp.header->next != NULL)
	{
		printf("%s ", tmp.header->information);
		tmp.header = tmp.header->next;
	}
	printf("%s\n", tmp.header->information);
}

int	delete_record(t_keys *table, int row_num)
{
	int i;
	t_keys *head = table;

	i = 0;
	while (i++ < row_num)
		head = head->next;
	while(head->header->next != NULL)
	{
		head->header = NULL;
		head->header = head->header->next;
	}
	printf("\n");
	return (1);
}
