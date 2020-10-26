#include "../include/cub3d.h"

static void		free_map_world_and_text(t_mlx *mlx)
{
	int i;

	i = 0;
	while (i < mlx->map.line)
	{
		free(mlx->map.world_map[i]);
		i++;
	}
	free(mlx->map.world_map);
	i = 0;
	while (i < 5)
	{
		free(mlx->texture[i]);
		i++;
	}
	free(mlx->texture);
}

int		exit_game(t_mlx *mlx)
{
	mlx_destroy_window(mlx->mlx_ptr, mlx->win);
	free_map_world_and_text(mlx);
	exit(0);
}

int		exit_game_err(t_mlx *mlx)
{
	mlx_destroy_window(mlx->mlx_ptr, mlx->win);
	exit(-1);
}