#include "cub3d.h"

void        ft_draw_sprite(t_mlx *mlx, t_player *player)
{
    double sprite_x = 3 - player->pos_x;
    double sprite_y = 20 - player->pos_y;
    double inv_det = 1.0 / (player->plan_x * player->dir_y - player->dir_x * player->plan_y);
    double transform_x = inv_det * (player->dir_y * sprite_x - player->dir_x * sprite_y);
    double transform_y = inv_det * (-player->plan_y * sprite_x + player->plan_x * sprite_y);

    int sprite_screen_x = (int)(WIN_WIDTH / 2) * (1 + transform_x / transform_y);
    int sprite_height = abs((int)(WIN_HEIGHT / (transform_y)));
    int draw_start_y = -sprite_height / 2 + WIN_HEIGHT / 2;
    int text_width = mlx->text.texture[4]->width;
    int text_height = mlx->text.texture[4]->height;

    if (draw_start_y < 0)
        draw_start_y = 0;
    int draw_end_y = sprite_height / 2 + WIN_HEIGHT / 2;
    if (draw_end_y >= WIN_HEIGHT)
        draw_end_y = WIN_HEIGHT - 1;
    
    int sprite_width = abs((int)(WIN_HEIGHT / (transform_y)));
    int draw_start_x = -sprite_width / 2 + sprite_screen_x;
    if (draw_start_x < 0)
        draw_start_x = 0;
    int draw_end_x = sprite_width / 2 + sprite_screen_x;
    if (draw_end_x >= WIN_WIDTH)
        draw_end_x = WIN_WIDTH - 1;
    for (int stripe = draw_start_x; stripe < draw_end_x; stripe++)
    {
        int tex_x = (int)(256 * (stripe - (-sprite_width / 2 + sprite_screen_x)) *  text_width / sprite_width) / 256;
        if (transform_y > 0 && stripe > 0 && stripe < WIN_WIDTH && transform_y < mlx->buff[stripe])
        {
            for(int y = draw_start_y; y < draw_end_y; y++)
            {
                int d = (y) * 256 - WIN_HEIGHT * 128 + sprite_height * 128;
                int tex_y = ((d * text_height) / sprite_height) / 256;
                int color = mlx->text.texture[4]->data[text_width * tex_y + tex_x];
                if ((color & 0xffffff) != 0)
                    mlx->img.data[y * WIN_WIDTH + stripe - 1] = color;
            }
        }
    }
}