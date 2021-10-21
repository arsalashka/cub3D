/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maearly <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 17:57:43 by maearly           #+#    #+#             */
/*   Updated: 2021/04/30 20:51:29 by maearly          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <fcntl.h>
# include <stdbool.h>
# include <math.h>
# include "utils/utils.h"
# include "mlx/mlx.h"

# define STD_FD 					1
# define EXIT_ERROR				1
# define EXIT_SUCCESS			0
# define X_EVENT_PUSH_BUTTON		2
# define X_EVENT_UNPUSH_BUTTON	3
# define X_EVENT_EXIT_BUTTON		17
# define KEY_W			13
# define KEY_A			0
# define KEY_S			1
# define KEY_D			2
# define KEY_Q			12
# define KEY_E			14
# define KEY_LEFT		123
# define KEY_RIGHT		124
# define KEY_FORWARD 	126
# define KEY_BACKWARD	125
# define KEY_ESC			53
# define MOVESPEED		0.12
# define STRAFESPEED		0.10
# define ROT_SPEED		0.07
# define R	1
# define NO	2		/* head->tex[0] */
# define SO	3		/* head->tex[1] */
# define WE	4		/* head->tex[2] */
# define EA	5		/* head->tex[3] */
# define S	6		/* head->tex[4] */
# define FT	7		/* head->tex[5] textured floor */
# define CT	8		/* head->tex[6] textured ceiling */
# define F	9
# define C	10
# define MP	11		/* map's unit */

typedef struct s_pos
{
	double	x;
	double	y;
}				t_pos;

typedef struct s_skyline
{
	int		c_color;
	int		f_color;
}				t_skyline;

typedef struct s_raycast
{
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		color;
	int		y;
	int		tex_num;
	double	wall_x;
	int		tex_x;
	int		tex_y;
	double	step;
	double	tex_pos;
}				t_raycast;

typedef struct s_win
{
	void	*mlx;
	void	*win;
	void	*img;
	void	*addr;
	int		line_length;
	int		bits_per_pixel;
	int		endian;
}				t_win;

typedef struct s_tex
{
	char	*path;
	void	*tex;
	void	*ptr;
	t_pos	start;
	t_pos	end;
	int		width;
	int		height;
	int		bpp;
	int		sl;
	int		en;
}				t_tex;

typedef struct s_plr
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	strf_dir_x;
	double	strf_dir_y;
	double	plane_x;
	double	plane_y;
}				t_plr;

typedef struct s_sprite
{
	t_pos			pos;
	double			dist;
	int				flag;
}				t_sprite;

typedef struct s_sprite_draw
{
	double	sprite_x;
	double	sprite_y;
	double	inv_det;
	double	transform_x;
	double	transform_y;
	int		spr_screen_x;
	int		spr_height;
	int		spr_width;
	int		draw_start_y;
	int		draw_end_y;
	int		draw_start_x;
	int		draw_end_x;
	int		stripe;
	int		tex_x;
	int		tex_y;
	int		y;
	int		color;
	int		d;
}			t_sprite_draw;

typedef struct s_head
{
	t_win		win;
	t_tex		**tex;
	int			spr_count;
	t_sprite	*sprites;
	t_sprite	*sorted;
	t_skyline	skyline;
	t_list		map_buf;
	t_plr		plr;
	t_pos		screen;
	t_pos		move;
	t_pos		strafe;
	t_pos		rotate;
	int			bmp;
	char		**map;
}				t_head;

int		check_args(t_head *head, int argc, char **argv);
int		read_map(t_head *head, char const *path_to_map);
void	ft_free_list(t_list *map_buf);
int		set_resolution(t_head *head, char **str);
void	check_resolution(t_head *head);
int		set_texture(t_head *head, int index, char **str);
int		set_floor_ceiling(t_head *head, int index, char **str_color);
void	free_splited_line(char **str);
int		set_map(t_head *head);
int		check_map(t_head *head, int y_max);
int		find_plr(t_head *head);
int		check_strlen(t_head *head);
int		check_arround_symbols(t_head *head);
int		check_config(t_head *head);
int		set_sprites_pos(t_head *head);
void	sprite_on_fov(t_head *head, t_raycast *cast);
int		hook(t_head *head);
int		new_win_init(t_head *head);
int		correct_plr_pos_y(t_head *head);
void	my_mlx_pixel_put(t_win *win, int x, int y, int color);
int		push_button(int button, t_head *head);
int		unpush_button(int button, t_head *head);
void	draw_map(t_head *all);
int		set_position(t_head *head);
void	go_forward(t_head *head);
void	go_backward(t_head *head);
void	strafe_n_direction(t_head *head);
int		get_tex_color(t_tex *tex, double x, double y);
void	prep_calc(t_head *head, t_raycast *cast, int x);
void	step_n_side_dist(t_head *head, t_raycast *cast);
void	dda_algorithm(t_head *head, t_raycast *cast);
void	perp_dist(t_head *head, t_raycast *cast);
void	draw_start_end(t_head *head, t_raycast *cast);
void	wall_x_calc(t_head *head, t_raycast *cast);
void	tex_x(t_head *head, t_raycast *cast);
void	draw_ceiling_floor(t_head *head, t_raycast *cast, int x);
void	draw_line(t_head *head, t_raycast *cast, int x, double *z_buff);
void	sprite_calc(t_head *head, double const *z_buff);
void	spr_draw_calc(t_head *head, t_sprite_draw *draw, int i);
void	spr_draw_calc2(t_head *head, t_sprite_draw *draw);
void	spr_drawer(t_head *head, t_sprite_draw *draw, double const *z_buff);
int		ft_error(t_head *head, char *str);
int		ft_exit(t_head *head);
void	make_screenshot(t_head *head);

#endif
