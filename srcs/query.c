

#include <ftdb.h>

/*
 * Function will work by passing in the current version of the table.
 * will return the record based off the key value by iterating through 
 * the link list, print each node, until NUll
 */

int	get_record(t_keys *table, int row_num)
{
	int i;
	t_keys *head = table;

	i = 0;
	while (i++ < row_num)
		head = head->next;
	while(head->header->next != NULL)
	{
		printf("%s ", head->header->information);
		head->header = head->header->next;
	}
	printf("\n");
	return (1);
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
