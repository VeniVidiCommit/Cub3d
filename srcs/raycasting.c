#include "../include/cub3d.h"

static void		ft_calcul_ray_position_box(t_vecteur *vec, int x, t_player *player, t_mlx *mlx)
{
	player->camera_x = 2 * x / (double)(mlx->win_width) - 1;
    vec->ray_dir_x = player->dir_x + player->plan_x * player->camera_x;
    vec->ray_dir_y = player->dir_y + player->plan_y * player->camera_x;
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

static void		ft_perform_dda_side(t_vecteur *vec)
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
}

static void		ft_perform_dda(t_mlx *mlx, t_vecteur *vec, t_player *player)
{
	int hit;

	hit = 0;
    while (hit == 0)
	{
		ft_perform_dda_side(vec);
        if (mlx->map.world_map[vec->map_x][vec->map_y] == 1) 
			hit = 1;
	}
		if (vec->side <= 1) 
	  		vec->perp_wall_dist = (vec->map_x - player->pos_x + (1 - vec->step_x) / 2) / vec->ray_dir_x;
		else           
	  		vec->perp_wall_dist = (vec->map_y - player->pos_y + (1 - vec->step_y) / 2) / vec->ray_dir_y; 
}

void			ft_raycasting(t_mlx *mlx, t_vecteur *vec, t_player *player)
{
	int x;

	x = -1;
	while (++x <= mlx->win_width)
	{
		ft_calcul_ray_position_box(vec, x, player, mlx);
		ft_calcul_step(vec, player);
		ft_perform_dda(mlx, vec, player);
		ft_calcul_wall(vec, x, mlx);
        mlx->buff[x] = vec->perp_wall_dist + 1;
	}
	if (mlx->count_sprite > 0)
    	ft_draw_sprite(mlx, player);
	if (mlx->save != 1)
		mlx_put_image_to_window(mlx->mlx_ptr, mlx->win, mlx->img.img_ptr, 0, 0);
}
