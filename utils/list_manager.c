/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maearly <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 18:22:30 by maearly           #+#    #+#             */
/*   Updated: 2021/04/29 21:17:29 by maearly          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

t_node	*create_node(char *line)
{
	t_node	*tmp;
	int		i;

	i = -1;
	tmp = malloc(sizeof(t_node *));
	if (!tmp)
		return (NULL);
	tmp->line = malloc(sizeof(char) * (ft_strlen(line) + 1));
	if (!tmp->line)
		return (NULL);
	while (line[++i])
		tmp->line[i] = line[i];
	tmp->line[i] = '\0';
	tmp->next = NULL;
	return (tmp);
}

void	ft_free_list(t_list *list)
{
	t_node	*tmp;

	while (list->first != NULL)
	{
		tmp = list->first;
		list->first = list->first->next;
		free(tmp);
	}
}

int	list_manager(t_list *list, char *line)
{
	t_node	*tmp;

	if (!line)
		return (0);
	if (line[0] == '\0')
		return (1);
	tmp = create_node(line);
	if (!tmp)
		return (0);
	if (list->i == 0)
	{
		list->first = tmp;
		list->tail = tmp;
		list->i = 1;
		return (1);
	}
	list->tail->next = tmp;
	list->tail = tmp;
	list->i++;
	return (1);
}
