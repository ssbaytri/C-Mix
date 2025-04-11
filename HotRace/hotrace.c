#include "hotrace.h"

void	free_table(t_pair *table[])
{
	int i;

	for (i = 0; i < TABLE_SIZE; i++)
	{
		if (table[i])
			free(table[i]);
	}
}

unsigned long hash_function(char *str)
{
	unsigned long hash;
	int c;
	
	hash = 5381;
	c = 0;
	while (str[c])
	{
		hash = ((hash << 5) + hash) + str[c];
		c++;
	}
	printf("hash value: %lu\n", hash);
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

t_pair *search(t_pair *table[], char *key)
{
	unsigned long index;

	index = hash_function(key);
	printf("index: %lu\n", index);
	printf("hash: %lu\n", hash_function(key));
	if (table[index] && strcmp(table[index]->key, key) == 0)
		return (table[index]);
	return (NULL);
}

void	ll()
{
	system("leaks -q hotrace");
}

int	main(int ac, char **av)
{
	atexit(ll);
	t_pair *table[TABLE_SIZE];
	(void)av;
	if (ac != 1)
	{
		write(2, "Usage: ./hotrace\n", 17);
		return (1);
	}
	insert(table, "key1", "value1");
	insert(table, "key2", "value2");
	insert(table, "key3", "value3");
	insert(table, "key4", "value4");
	insert(table, "key5", "value5");

	t_pair *result = search(table, "key1");
	if (result)
		printf("Found: %s -> %s\n", result->key, result->value);
	else
		printf("Not found\n");

	free_table(table);
	return (0);
}