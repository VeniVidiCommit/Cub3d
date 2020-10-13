#include "cub3d.h"

void		ft_init_vec(t_mlx *mlx)
{

	mlx->player.pos_x = 0;
	mlx->player.pos_y = 0;
	mlx->player.dir_x = -1;
	mlx->player.dir_y = 0;
	mlx->player.plan_x = 0;
	mlx->player.plan_y = 0.66;
	mlx->player.move_speed = 0.10;
	mlx->player.rotate_speed = 0.10;
	mlx->player.camera_x = 0;
	mlx->count_sprite = 0;
	ft_bzero(mlx->keyboard, sizeof(char) * 125);
}

int			ft_load_text(t_text *text)
{
	int nb_texture = 5;
	int i = 0;
	text->texture = malloc(sizeof(t_img *) * nb_texture);
	while (i < nb_texture)
	{
		text->texture[i] = malloc(sizeof(t_img));
		ft_bzero(text->texture[i], sizeof(t_img));
		i++;
	}
	return (1);
}