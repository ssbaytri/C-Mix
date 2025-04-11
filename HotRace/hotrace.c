#include "hotrace.h"

unsigned long hash_function(char *str)
{
	unsigned long hash;
	int c;
	
	hash = 5381;
	c = 0;
	while (str[c])
	{
		hash = ((hash << 5) + hash) + c;
		c++;
	}
	printf("hash: %lu\n", hash);
	printf("hash index %lu\n", hash % TABLE_SIZE);
	return (hash % TABLE_SIZE);
}

void	insert(t_pair *table[], char *key, char *value)
{
	unsigned long index;
	t_pair *new_pair;

	index = hash_function(key);
	new_pair = malloc(sizeof(t_pair));
	if (!new_pair)
		return;
	new_pair->key = key;
	new_pair->value = value;
	table[index] = new_pair;
}

int	main(int ac, char **av)
{
	(void)av;
	if (ac != 1)
	{
		write(2, "Usage: ./hotrace\n", 17);
		return (1);
	}
	t_pair *table[TABLE_SIZE] = {NULL};
	insert(table, "key1", "value1");
	insert(table, "key2", "value2");
	insert(table, "key3", "value3");
	return (0);
}