/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   position2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maearly <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 16:25:28 by maearly           #+#    #+#             */
/*   Updated: 2021/04/29 14:25:39 by maearly          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	right_rotation(t_head *head)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = head->plr.dir_x;
	head->plr.dir_x = head->plr.dir_x * cos(-ROT_SPEED) - head->plr.dir_y
		* sin(-ROT_SPEED);
	head->plr.dir_y = old_dir_x * sin(-ROT_SPEED) + head->plr.dir_y
		* cos(-ROT_SPEED);
	head->plr.strf_dir_x = head->plr.dir_y;
	head->plr.strf_dir_y = -head->plr.dir_x;
	old_plane_x = head->plr.plane_x;
	head->plr.plane_x = head->plr.plane_x * cos(-ROT_SPEED)
		- head->plr.plane_y * sin(-ROT_SPEED);
	head->plr.plane_y = old_plane_x * sin(-ROT_SPEED) + head->plr.plane_y
		* cos(-ROT_SPEED);
}

void	left_rotation(t_head *head)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = head->plr.dir_x;
	head->plr.dir_x = head->plr.dir_x * cos(ROT_SPEED) - head->plr.dir_y
		* sin(ROT_SPEED);
	head->plr.dir_y = old_dir_x * sin(ROT_SPEED) + head->plr.dir_y
		* cos(ROT_SPEED);
	head->plr.strf_dir_x = head->plr.dir_y;
	head->plr.strf_dir_y = -head->plr.dir_x;
	old_plane_x = head->plr.plane_x;
	head->plr.plane_x = head->plr.plane_x * cos(ROT_SPEED)
		- head->plr.plane_y * sin(ROT_SPEED);
	head->plr.plane_y = old_plane_x * sin(ROT_SPEED) + head->plr.plane_y
		* cos(ROT_SPEED);
}

void 	right_strafe(t_head *head)
{
	if (head->strafe.y == 1)
	{
		if (head->map[(int)(head->plr.pos_y)][(int)(head->plr.pos_x
													-head->plr.strf_dir_x *
													STRAFESPEED)] != '1')
			head->plr.pos_x -= (head->plr.strf_dir_x * STRAFESPEED + 0.0001);
		if (head->map[(int)(head->plr.pos_y - head->plr.strf_dir_y
				* STRAFESPEED)][(int)(head->plr.pos_x)] != '1')
			head->plr.pos_y -= (head->plr.strf_dir_y * STRAFESPEED + 0.0001);
	}
}

void 	left_strafe(t_head *head)
{
	if (head->strafe.x == 1)
		if (head->map[(int)(head->plr.pos_y)][(int)(head->plr.pos_x +
							head->plr.strf_dir_x * STRAFESPEED)] != '1')
			head->plr.pos_x += (head->plr.strf_dir_x * STRAFESPEED + 0.0001);
	if (head->map[(int)(head->plr.pos_y + head->plr.strf_dir_y * STRAFESPEED)]
			[(int)(head->plr.pos_x)] != '1')
		head->plr.pos_y += (head->plr.strf_dir_y * STRAFESPEED + 0.0001);
}

void 	strafe_n_direction(t_head *head)
{
	if (head->rotate.x == 1)
		right_rotation(head);
	if (head->rotate.y == 1)
		left_rotation(head);
	if (head->strafe.x == 1)
		left_strafe(head);
	if (head->strafe.y == 1)
		right_strafe(head);
}
