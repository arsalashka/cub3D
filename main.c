/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maearly <maearly@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 17:54:33 by maearly           #+#    #+#             */
/*   Updated: 2021/05/01 16:16:41 by maearly          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int 	init_sett(t_head *head)
{
	head->win.mlx = mlx_init();
	if (!head->win.mlx)
		return (0);
	head->tex = calloc(sizeof(int) * 5, sizeof(t_tex));
	if (head->tex == NULL)
		return (0);
	head->map_buf.first = NULL;
	head->map_buf.i = 0;
	head->plr.pos_x = -1.0;
	head->skyline.f_color = -1;
	head->skyline.c_color = -1;
	head->screen.x = 0;
	head->screen.y = 0;
	head->bmp = 0;
	return (1);
}

int	ft_exit(t_head *head)
{
	int	i;

	i = -1;
	while (head->map[++i])
		free(head->map[i]);
	free(head->map[i]);
	head = NULL;
	exit (EXIT_SUCCESS);
}

int 	ft_error(t_head *head, char *str)
{
	if (str)
		write(STD_FD, str, ft_strlen(str));
	exit (EXIT_ERROR);
}

void	printf_checker(t_head head)
{
	int	i;

	i = -1;
	while (head.map[++i])
		printf("%s\n", head.map[i]);
}

int	main(int argc, char **argv)
{
	t_head	head;

	if (!init_sett(&head))
		return (ft_error(&head, "Error\nInitialization error!\n"));
	if (!check_args(&head, argc, argv))
		return (ft_error(&head, "Error\nArguments error!\n"));
	if (!read_map(&head, argv[1]))
		return (ft_error(&head, "Error\nMap error!\n"));
	printf_checker(head);
	if (!new_win_init(&head))
		return (0);
	if (head.bmp)
		make_screenshot(&head);
	mlx_hook(head.win.win, X_EVENT_PUSH_BUTTON, 0, &push_button, &head);
	mlx_hook(head.win.win, X_EVENT_UNPUSH_BUTTON, 0, &unpush_button, &head);
	mlx_hook(head.win.win, X_EVENT_EXIT_BUTTON, 0, &ft_exit, &head);
	mlx_loop_hook(head.win.mlx, &hook, &head);
	mlx_loop(head.win.mlx);
	return (0);
}
