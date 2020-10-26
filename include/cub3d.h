/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viroques <viroques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 16:13:40 by viroques          #+#    #+#             */
/*   Updated: 2020/10/26 21:39:42 by viroques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include "../minilibx_opengl/mlx.h"
# include "../libft/libft.h"
# include <fcntl.h>

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
# define KEY_ESC 53
# define H_SIZE 512

typedef struct      s_img
{
    void            *img_ptr;
    int             *data;
    int             width;
    int             height;
    int             size_l;
    int             bpp;
    int             endian;
}                   t_img;

typedef struct      s_player
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
    int             pop;
}                   t_player;

typedef struct      s_vecteur
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

typedef struct      s_sprite
{
    double          x;
    double          y;
}                   t_sprite;

typedef struct      s_info_sprite
{
    double          sprite_x;
    double          sprite_y;
    double          inv_det;
    double          transform_x;
    double          transform_y;
    int             text_width;
    int             text_height;
    int             v_move_screen;
    int             sprite_screen_x;
    int             sprite_height;
    int             sprite_width;
    int             draw_start_y;
    int             draw_end_y;
    int             draw_start_x;
    int             draw_end_x;
    int             tex_x;
}                   t_info_sprite;

typedef struct s_info_wall
{
    double          wall_x;;
    double          step;
    double          text_pos;
    int             text_x;
}               t_info_wall;

typedef struct      s_map
{
    int             width;
    int             height;
    int             col;
    int             line;
    int             **world_map;
}                   t_map;

typedef struct      s_tmp_free {
    t_img           **tmp_texture;
    char            **tmp_file;

}                   t_tmp_free;

typedef struct      s_mlx
{
    void            *mlx_ptr;
    void            *win;
    int             win_width;
    int             win_height;
    int             screen_width;
    int             screen_height;
    int             f_color;
    int             c_color;
    t_img           img;
    t_vecteur       vec;
    t_player        player;
    t_img           **texture;
    t_sprite        *sprite;
    int             count_sprite;
    t_map           map;
    double          buff[1920];
    char            keyboard[125];
    char            **file;
    char            **file_n;
    t_tmp_free      tmp_free;
    int             save;
}                   t_mlx;

typedef struct      s_bmp_header{
    uint16_t        type;            
    uint32_t        size;             
    uint16_t        reserved1;        
    uint16_t        reserved2;        
    uint32_t        offset;          
    uint32_t        dib_header_size;  
    uint32_t        width_px;         
    uint32_t        height_px;        
    uint16_t        num_planes;       
    uint16_t        bits_per_pixel;   
    uint32_t        compression;      
    uint32_t        image_size_bytes; 
    uint32_t        x_resolution_ppm; 
    uint32_t        y_resolution_ppm;
    uint32_t        num_colors;
    uint32_t        important_colors;
}                   t_bmp_header;

typedef struct      s_header_parser
{
    char            **values;
    char            hash[H_SIZE];
    int             index_text;
    int             compt;
    int             check;
    int             index;
}                   t_header_parser;


void		ft_raycasting(t_mlx *mlx, t_vecteur *vec, t_player *player);
int		    ft_init(t_mlx *mlx);
int			ft_load_text(t_mlx *mlx);
int		    key_press(int keycode, t_mlx *mlx);
int		    key_release(int keycode, t_mlx *mlx);
int			ft_keyboard_manager(t_mlx *mlx);
void		ft_draw_wall_text(int width, int draw_start, int draw_end,t_mlx *mlx);
void        ft_draw_sprite(t_mlx *mlx, t_player *player);
int         parsing_map(t_mlx *mlx, char *path);
int         ft_compt_args(char **tab, int size);
void        ft_free_tab(char **tab);
int         ft_str_is_digit(char *str);
int         ft_hash(char *key);
int         error(char *msg, int ret);
int         error_free(char *msg, int ret, char **tab);
char        *error_char(char *msg, char *nul);
int         ft_malloc_text(t_mlx *mlx);
char        **ft_split_sep(char const *s, char c);
int			screenshot(t_mlx *mlx, char *argv);
int		    exit_game_err(t_mlx *mlx);
int         exit_game(t_mlx *mlx);
void        ft_calcul_wall(t_vecteur *vec, int x, t_mlx *mlx);
int         key_press(int keycode, t_mlx *mlx);
int         key_release(int keycode, t_mlx *mlx);
int         parse_header_map(t_mlx *mlx, char **file, char **file_n);
int         ft_count(t_mlx *mlx, char **file, char **file_n);
int         ft_get_color_fc(t_mlx *mlx, char **values, char *hash);
void        fill_map_world(t_mlx *mlx, char **file);
int         ft_malloc_map(t_mlx *mlx, char **file);
int         ft_check_map(t_mlx *mlx, char **file, char **file_n);
int         define_min_len(char **file, int i, t_mlx *mlx);
#endif
