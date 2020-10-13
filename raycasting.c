#include "cub3d.h"

static void		ft_draw_wall_text(int width, int draw_start, int draw_end, int side, t_mlx *mlx)
{
	double wall_x;

	if (side <= 1)
		wall_x = mlx->player.pos_y + mlx->vec.perp_wall_dist * mlx->vec.ray_dir_y;
	else
		wall_x = mlx->player.pos_x + mlx->vec.perp_wall_dist * mlx->vec.ray_dir_x;
	wall_x -= floor(wall_x);
	t_img *g_texture;
	if (side == 0)
		g_texture = mlx->text.texture[0];
	if (side == 1)
		g_texture = mlx->text.texture[1];
	if (side == 2)
		g_texture = mlx->text.texture[2];
	if (side == 3)
		g_texture = mlx->text.texture[3];
	int text_x = (int)(wall_x * (double)g_texture->width);
	if (side <= 1 && mlx->vec.ray_dir_x > 0)
		text_x = g_texture->width - text_x - 1;
	if (side >= 2 && mlx->vec.ray_dir_y < 0)
		text_x = g_texture->width - text_x - 1;
	double step = 1.0 * g_texture->height / mlx->vec.line_height;
	double text_pos = (draw_start - WIN_HEIGHT / 2 + mlx->vec.line_height / 2) * step;
	for (int y = draw_start; y < draw_end; y++)
	{
		int text_y = (int)text_pos & (g_texture->height - 1);
		text_pos += step;
		mlx->img.data[y * WIN_WIDTH + width - 1] = g_texture->data[text_x + text_y * g_texture->height];
	}
	// draw_flor_and_ground
	draw_start = draw_end;
	while (draw_start < WIN_HEIGHT)
	{
		mlx->img.data[draw_start * WIN_WIDTH + width - 1] = mlx->f_color;
		mlx->img.data[(WIN_HEIGHT - draw_start - 1) * WIN_WIDTH + width] = mlx->c_color;
		draw_start++;
	}
}

static void		ft_calcul_ray_position_direction(t_vecteur *vec, int x, t_player *player)
{
	player->camera_x = 2 * x / (double)(WIN_WIDTH) - 1; //x-coordinate in camera space
    vec->ray_dir_x = player->dir_x + player->plan_x * player->camera_x;
    vec->ray_dir_y = player->dir_y + player->plan_y * player->camera_x;
}

static void		ft_wich_box(t_vecteur *vec, t_player *player)
{
	vec->map_x = (int)player->pos_x;
	vec->map_y = (int)player->pos_y;
	vec->delta_dist_x = (vec->ray_dir_y == 0) ? 0 : ((vec->ray_dir_x == 0) ? 1 : fabs(1 / vec->ray_dir_x));
    vec->delta_dist_y = (vec->ray_dir_x == 0) ? 0 : ((vec->ray_dir_y == 0) ? 1 : fabs(1 / vec->ray_dir_y));
}

static void		ft_calcul_step(t_vecteur *vec, t_player *player)
{
	if (vec->ray_dir_x < 0)
		{
			vec->step_x = -1;
			vec->side_dist_x = (player->pos_x - vec->map_x) * vec->delta_dist_x;
		}
		else
		{
			vec->step_x = 1;
			vec->side_dist_x = (vec->map_x + 1.0 - player->pos_x) * vec->delta_dist_x;
		}
		if (vec->ray_dir_y < 0)
		{
			vec->step_y = -1;
			vec->side_dist_y = (player->pos_y - vec->map_y) * vec->delta_dist_y;
		}
		else
		{
			vec->step_y = 1;
			vec->side_dist_y = (vec->map_y + 1.0 - player->pos_y) * vec->delta_dist_y;
		}
}

static void		ft_perform_dda(t_mlx *mlx, t_vecteur *vec, t_player *player)
{
	int hit;

	hit = 0;
    while (hit == 0)
	{
    	if (vec->side_dist_x < vec->side_dist_y)
    	{
			vec->side_dist_x += vec->delta_dist_x;
			vec->map_x += vec->step_x;
			if (vec->ray_dir_x < 0)
				vec->side = 0;
			else
				vec->side = 1;
		}
        else
        {
          vec->side_dist_y += vec->delta_dist_y;
          vec->map_y += vec->step_y;
			if (vec->ray_dir_y < 0)
				vec->side = 2;
			else
				vec->side = 3;
        }
        if (mlx->map.world_map[vec->map_x][vec->map_y] == 1) 
			hit = 1;
	}
	//fising eyes correction
		if (vec->side <= 1) 
	  		vec->perp_wall_dist = (vec->map_x - player->pos_x + (1 - vec->step_x) / 2) / vec->ray_dir_x;
		else           
	  		vec->perp_wall_dist = (vec->map_y - player->pos_y + (1 - vec->step_y) / 2) / vec->ray_dir_y; 
}

static void		ft_calcul_wall(t_vecteur *vec, int x, t_mlx *mlx)
{
		int line_height;
		int draw_start;
		int draw_end;

		line_height = (int)(WIN_HEIGHT / vec->perp_wall_dist);
		mlx->vec.line_height = line_height;
		draw_start = -line_height / 2 + WIN_HEIGHT / 2;
		if (draw_start < 0)
			draw_start = 0;
		draw_end = line_height / 2 + WIN_HEIGHT / 2;
		if (draw_end >= WIN_HEIGHT || draw_end < 0)
			draw_end = WIN_HEIGHT - 1;
	  ft_draw_wall_text(x, draw_start, draw_end, vec->side, mlx);
}

void		ft_raycasting(t_mlx *mlx, t_vecteur *vec, t_player *player)
{
	int x;

	x = -1;
	while (++x <= WIN_WIDTH)
	{
		ft_calcul_ray_position_direction(vec, x, player);
		ft_wich_box(vec, player);
		ft_calcul_step(vec, player);
		ft_perform_dda(mlx, vec, player);
		ft_calcul_wall(vec, x, mlx);
        mlx->buff[x] = vec->perp_wall_dist;
	}
	if (mlx->count_sprite > 0)
    	ft_draw_sprite(mlx, player);
}
