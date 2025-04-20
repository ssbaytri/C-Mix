/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 18:25:00 by ssbaytri          #+#    #+#             */
/*   Updated: 2025/04/20 18:33:02 by ssbaytri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hotrace.h"

void	free_table(t_pair **table, int table_size)
{
	int	i;

	if (!table)
		return ;
	i = 0;
	while (i < table_size)
	{
		if (table[i])
			free(table[i]);
		i++;
	}
	free(table);
}

unsigned long	hash_function(const char *key, int table_size)
{
	unsigned long	hash;
	int				c;

	if (table_size <= 0)
		return (0);
	hash = 5381;
	c = *key;
	while (c)
	{
		hash = ((hash << 5) + hash) + c;
		key++;
		c = *key;
	}
	return (hash % table_size);
}

void	ht_insert(t_pair **table, char *k, char *v, int table_size)
{
	unsigned long	idx;
	unsigned long	original_idx;
	t_pair			*p;

	if (table_size <= 0)
		return ;
	idx = hash_function(k, table_size);
	original_idx = idx;
	while (table[idx])
	{
		if (strcmp(table[idx]->key, k) == 0)
		{
			table[idx]->value = v;
			return ;
		}
		idx = (idx + 1) % table_size;
		if (idx == original_idx)
			return ;
	}
	p = malloc(sizeof(t_pair));
	p->key = k;
	p->value = v;
	table[idx] = p;
}

t_pair	*ht_search(t_pair **table, char *k, int table_size)
{
	unsigned long	idx;
	unsigned long	original_idx;

	if (table_size <= 0)
		return (NULL);
	idx = hash_function(k, table_size);
	original_idx = idx;
	while (table[idx])
	{
		if (strcmp(table[idx]->key, k) == 0)
			return (table[idx]);
		idx = (idx + 1) % table_size;
		if (idx == original_idx)
			break ;
	}
	return (NULL);
}
