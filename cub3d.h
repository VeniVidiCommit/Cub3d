/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viroques <viroques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 16:13:40 by viroques          #+#    #+#             */
/*   Updated: 2020/10/07 00:08:33 by viroques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include "./minilibx_mms/mlx.h"
# include "./libft/libft.h"
# include <fcntl.h>

# define WIN_WIDTH 800 
# define WIN_HEIGHT 600
# define MAP_WIDTH 8
# define MAP_HEIGHT 25
# define TEXT_WIDTH 64
# define TEXT_HEIGHT 64
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_W 13
# define KEY_LEFT 123
# define KEY_RIGHT 124
# define NO 0
# define SO 1
# define WE 2
# define EA 3
# define S 4
# define H_SIZE 512

typedef struct  s_img
{
    void        *img_ptr;
    int         *data;
    int         width;
    int         height;
    int         size_l;
    int         bpp;
    int         endian;
}               t_img;

typedef struct  s_player
{
    double          pos_x;
    double          pos_y;
    double          dir_x;
    double          dir_y;
    double          plan_x;
    double          plan_y;
    double          move_speed;
    double          rotate_speed;
    double          camera_x;
}                   t_player;

typedef struct  s_vecteur
{
    double          ray_dir_x;
    double          ray_dir_y;
    int             map_x;
    int             map_y;
    double          side_dist_x;
    double          side_dist_y;
    double          delta_dist_x;
    double          delta_dist_y;
    double          perp_wall_dist;
    int             step_x;
    int             step_y;
    int             side;
    int             keycode;
    int             line_height;
}               t_vecteur;

typedef struct  s_text
{
    t_img   **texture;
}               t_text;

typedef struct s_sprite
{
    double  x;
    double  y;
    char    *path;
    t_img   *texture;
}               t_sprite;

typedef struct  s_map
{
    char        **w_map;
    int         width;
    int         height;
}               t_map;

typedef struct  s_mlx
{
    void        *mlx_ptr;
    void        *win;
    int         win_width;
    int         win_height;
    int         screen_width;
    int         screen_height;
    t_img       img;
    t_vecteur   vec;
    t_player    player;
    t_text      text;
    t_sprite    sprite;
    t_map       map;
    double  buff[WIN_WIDTH + 1];
    char       keyboard[125];
    char       **file;
}               t_mlx;

extern int worldMap[MAP_WIDTH][MAP_HEIGHT];

void		ft_raycasting(t_mlx *mlx, t_vecteur *vec, t_player *player);
void		ft_init_vec(t_mlx *mlx);
int			ft_load_text(t_mlx *mlx, t_text *text);
int		    key_press(int keycode, t_mlx *mlx);
int		    key_release(int keycode, t_mlx *mlx);
int			ft_rotate(t_mlx *mlx);
void		ft_init_vec(t_mlx *mlx);
void        ft_draw_sprite(t_mlx *mlx, t_player *player);
int        ft_read_and_split_map(t_mlx *mlx, char *path);

#endif