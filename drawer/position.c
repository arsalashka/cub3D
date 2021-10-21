/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   position.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maearly <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 15:26:38 by maearly           #+#    #+#             */
/*   Updated: 2021/04/29 14:24:55 by maearly          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	push_button(int button, t_head *head)
{
	if (button == KEY_W || button == KEY_FORWARD)
		head->move.x = 1;
	else if (button == KEY_S || button == KEY_BACKWARD)
		head->move.y = 1;
	if (button == KEY_A)
		head->strafe.x = 1;
	else if (button == KEY_D)
		head->strafe.y = 1;
	if (button == KEY_Q || button == KEY_LEFT)
		head->rotate.x = 1;
	else if (button == KEY_E || button == KEY_RIGHT)
		head->rotate.y = 1;
	return (0);
}

int	unpush_button(int button, t_head *head)
{
	if (button == KEY_W || button == KEY_FORWARD)
		head->move.x = 0;
	else if (button == KEY_S || button == KEY_BACKWARD)
		head->move.y = 0;
	else if (button == KEY_A)
		head->strafe.x = 0;
	else if (button == KEY_D)
		head->strafe.y = 0;
	else if (button == KEY_Q || button == KEY_LEFT)
		head->rotate.x = 0;
	else if (button == KEY_E || button == KEY_RIGHT)
		head->rotate.y = 0;
	else if (button == KEY_ESC)
		ft_exit(head);
	return (0);
}
/*	return (exit_game(all, EXIT_SUCCESS)); */

void 	go_forward(t_head *head)
{
	if (head->move.x == 1)
		if (head->map[(int)(head->plr.pos_y)][(int)(head->plr.pos_x +
				head->plr.dir_x * MOVESPEED)] != '1')
			head->plr.pos_x += head->plr.dir_x * MOVESPEED;
	if (head->map[(int)(head->plr.pos_y + head->plr.dir_y * MOVESPEED)][(int)
			(head->plr.pos_x)] != '1')
		head->plr.pos_y += head->plr.dir_y * MOVESPEED;
}

void 	go_backward(t_head *head)
{
	if (head->move.y == 1)
	{
		if (head->map[(int)(head->plr.pos_y)][(int)(head->plr.pos_x -
				head->plr.dir_x * MOVESPEED)] != '1')
			head->plr.pos_x -= head->plr.dir_x * MOVESPEED;
		if (head->map[(int)(head->plr.pos_y - head->plr.dir_y * MOVESPEED)]
				[(int)(head->plr.pos_x)] != '1')
			head->plr.pos_y -= head->plr.dir_y * MOVESPEED;
	}
}

int	set_position(t_head *head)
{
	if (head->move.x == 1)
		go_forward(head);
	else if (head->move.y == 1)
		go_backward(head);
	if (head->strafe.x == 1 || head->strafe.y == 1 || head->rotate.y == 1
		|| head->rotate.x == 1)
		strafe_n_direction(head);
	return (0);
}
/* printf("pos_x: %f, pos_y: %f, dir_x: %f, dir_y: %f, strf_sir_x: %f, "
		"strf_dir_y: %f\n", head->plr.pos_x, head->plr.pos_y, head->plr
		.dir_x, head->plr.dir_y, head->plr.strf_dir_x, head->plr.strf_dir_y); */