/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_plr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maearly <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 20:37:58 by maearly           #+#    #+#             */
/*   Updated: 2021/04/21 15:39:11 by maearly          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	set_plane(t_head *head, char c)
{
	if (c == 'N')
	{
		head->plr.plane_x = 0.66;
		head->plr.plane_y = 0;
	}
	else if (c == 'E')
	{
		head->plr.plane_x = 0;
		head->plr.plane_y = 0.66;
	}
	else if (c == 'S')
	{
		head->plr.plane_x = -0.66;
		head->plr.plane_y = 0;
	}
	else if (c == 'W')
	{
		head->plr.plane_x = 0;
		head->plr.plane_y = -0.66;
	}
}

void	set_plr_dir(t_head *head, float dir_x, float dir_y, char c)
{
	head->plr.dir_x = dir_x;
	head->plr.dir_y = dir_y;
	head->plr.strf_dir_x = dir_y;
	head->plr.strf_dir_y = -dir_x;
	set_plane(head, c);
}

int 	set_plr_pos_x(t_head *head, const char *str, int x)
{
	if (!str)
		return (0);
	if (str[x + 1] == '1')
		head->plr.pos_x = x + 0.5;
	else if (str[x - 1] == '1')
		head->plr.pos_x = x + 0.5;
	else
		head->plr.pos_x = x;
	return (1);
}

int 	find_plr_dir(t_head *head, char *str)
{
	int	x;

	if (!str)
		return (0);
	x = -1;
	while (str[++x])
	{
		if (str[x] == 'N' || str[x] == 'E' || str[x] == 'S' || str[x] == 'W')
		{
			if (!set_plr_pos_x(head, str, x))
				return (0);
			if (str[x] == 'N')
				set_plr_dir(head, 0, -1, str[x]);
			else if (str[x] == 'E')
				set_plr_dir(head, 1, 0, str[x]);
			else if (str[x] == 'S')
				set_plr_dir(head, 0, 1, str[x]);
			else if (str[x] == 'W')
				set_plr_dir(head, -1, 0, str[x]);
			str[x] = '0';
			return (1);
		}
	}
	return (0);
}

int 	find_plr(t_head *head)
{
	int		y;
	t_node	*tmp;

	tmp = head->map_buf.first;
	y = 0;
	while (head->map_buf.first)
	{
		if (find_plr_dir(head, head->map_buf.first->line))
		{
			head->plr.pos_y = y;
			break ;
		}
		head->map_buf.first = head->map_buf.first->next;
		y++;
	}
	if (head->plr.pos_x == -1)
		return (0);
	head->map_buf.first = tmp;
	return (1);
}
