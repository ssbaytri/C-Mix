/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hotrace.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 18:33:53 by ssbaytri          #+#    #+#             */
/*   Updated: 2025/04/20 20:12:02 by ssbaytri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hotrace.h"

static t_entry	*read_input_data(void)
{
	char	key[BUFFER_SIZE];
	char	value[BUFFER_SIZE];
	t_entry	*head;

	head = NULL;
	while (1)
	{
		if (read_line(key, BUFFER_SIZE) == 0)
			break ;
		if (read_line(value, BUFFER_SIZE) == 0)
			break ;
		head = add_entry(head, key, value);
	}
	return (head);
}

static t_pair	**create_hash_table(t_entry *head, int *size)
{
	t_pair	**table;
	int		i;

	*size = count_entries(head);
	if (*size == 0)
		return (NULL);
	*size = (*size) * 1.3;
	if (*size < 10)
		*size = 10;
	table = malloc(sizeof(t_pair *) * (*size));
	if (!table)
		return (NULL);
	i = 0;
	while (i < *size)
	{
		table[i] = NULL;
		i++;
	}
	return (table);
}

static void	populate_hash_table(t_pair **table, t_entry *head, int table_size)
{
	t_entry	*tmp;

	tmp = head;
	while (tmp)
	{
		ht_insert(table, tmp->key, tmp->value, table_size);
		tmp = tmp->next;
	}
}

static void	handle_queries(t_pair **table, int table_size)
{
	char	key[BUFFER_SIZE];
	t_pair	*result;

	while (read_line(key, BUFFER_SIZE) > 0)
	{
		result = ht_search(table, key, table_size);
		if (result)
		{
			write(1, result->value, strlen(result->value));
			write(1, "\n", 1);
		}
		else
		{
			write(1, key, strlen(key));
			write(1, ": Not found.\n", 13);
		}
	}
}

int	main(void)
{
	t_entry	*head;
	t_pair	**table;
	int		table_size;

	head = read_input_data();
	table = create_hash_table(head, &table_size);
	if (!table)
	{
		handle_empty_case();
		free_entry(head);
		return (0);
	}
	populate_hash_table(table, head, table_size);
	handle_queries(table, table_size);
	free_table(table, table_size);
	free_entry(head);
	return (0);
}
