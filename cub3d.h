/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viroques <viroques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 16:13:40 by viroques          #+#    #+#             */
/*   Updated: 2020/10/14 18:44:47 by viroques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include "minilibx_opengl/mlx.h"
#include "libft/libft.h"
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
}               t_sprite;

typedef struct  s_map
{
    int         width;
    int         height;
    int         col;
    int         line;
    int         **world_map;
}               t_map;

typedef struct  s_mlx
{
    void        *mlx_ptr;
    void        *win;
    int         win_width;
    int         win_height;
    int         screen_width;
    int         screen_height;
    int         f_color;
    int         c_color;
    t_img       img;
    t_vecteur   vec;
    t_player    player;
    t_text      text;
    t_sprite    *sprite;
    int         count_sprite;
    t_map       map;
    double  buff[WIN_WIDTH + 1];
    char       keyboard[125];
    char       **file;
}               t_mlx;

typedef struct s_bmp_header{
    uint16_t  type;             // Magic identifier: 0x4d42
    uint32_t  size;             // File size in bytes
    uint16_t  reserved1;        // Not used
    uint16_t  reserved2;        // Not used
    uint32_t  offset;           // Offset to image data in bytes from beginning of file (54 bytes)
    uint32_t  dib_header_size;  // DIB Header size in bytes (40 bytes)
    uint32_t   width_px;         // Width of the image
    uint32_t   height_px;        // Height of image
    uint16_t  num_planes;       // Number of color planes
    uint16_t  bits_per_pixel;   // Bits per pixel
    uint32_t  compression;      // Compression type
    uint32_t  image_size_bytes; // Image size in bytes
    uint32_t   x_resolution_ppm; // Pixels per meter
    uint32_t   y_resolution_ppm; // Pixels per meter
    uint32_t  num_colors;       // Number of colors  
    uint32_t  important_colors;
}               t_bmp_header;


typedef struct s_bmp_image{
    t_bmp_header header;
    int         *data;
} t_bmp_image;


void		ft_raycasting(t_mlx *mlx, t_vecteur *vec, t_player *player);
void		ft_init_vec(t_mlx *mlx);
int			ft_load_text(t_text *text);
int		    key_press(int keycode, t_mlx *mlx);
int		    key_release(int keycode, t_mlx *mlx);
int			ft_rotate(t_mlx *mlx);
void		ft_init_vec(t_mlx *mlx);
void        ft_draw_sprite(t_mlx *mlx, t_player *player);
int        ft_read_map(t_mlx *mlx, char *path);
int         ft_compt_args(char **tab, int size);
void        ft_free_tab(char **tab);
int         ft_str_is_digit(char *str);
int         ft_hash(char *key);
int         error(char *msg, int ret);
int         error_free(char *msg, int ret, char **tab);

#endif