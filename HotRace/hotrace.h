/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hotrace.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 18:22:56 by ssbaytri          #+#    #+#             */
/*   Updated: 2025/04/20 18:35:39 by ssbaytri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

typedef struct s_entry
{
	char			*key;
	char			*value;
	struct s_entry	*next;
}					t_entry;

typedef struct s_pair
{
	char			*key;
	char			*value;
}					t_pair;

size_t				ft_strlen(const char *s);
char				*ft_strdup(const char *src);
int					ft_strcmp(const char *a, const char *b);

void				handle_empty_case(void);
int					read_line(char *buffer, int size);
t_entry				*add_entry(t_entry *head, char *key, char *value);
void				free_entry(t_entry *entry);
int					count_entries(t_entry *h);

void				free_table(t_pair **table, int table_size);
unsigned long		hash_function(const char *key, int table_size);
void				ht_insert(t_pair **table, char *k, char *v, int table_size);
t_pair				*ht_search(t_pair **table, char *k, int table_size);
