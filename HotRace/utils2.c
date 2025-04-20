/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 18:23:37 by ssbaytri          #+#    #+#             */
/*   Updated: 2025/04/20 18:35:04 by ssbaytri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hotrace.h"

int	read_line(char *buffer, int size)
{
	int		i;
	char	c;

	i = 0;
	while (i < size - 1 && read(0, &c, 1) > 0 && c != '\n')
		buffer[i++] = c;
	buffer[i] = '\0';
	return (i);
}

t_entry	*add_entry(t_entry *head, char *key, char *value)
{
	t_entry	*new;

	new = malloc(sizeof(t_entry));
	if (!new)
		return (NULL);
	new->key = strdup(key);
	new->value = strdup(value);
	new->next = head;
	return (new);
}

void	free_entry(t_entry *entry)
{
	t_entry	*tmp;

	while (entry)
	{
		tmp = entry;
		entry = entry->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
	}
}

int	count_entries(t_entry *h)
{
	int	c;

	c = 0;
	while (h)
	{
		c++;
		h = h->next;
	}
	return (c);
}

void	handle_empty_case(void)
{
	char	key[BUFFER_SIZE];

	while (read_line(key, BUFFER_SIZE) > 0)
	{
		write(1, key, strlen(key));
		write(1, ": Not found.\n", 13);
	}
}
