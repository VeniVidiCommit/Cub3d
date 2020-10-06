#include "cub3d.h"

void		ft_init_vec(t_mlx *mlx)
{

	mlx->player.pos_x = 3;
	mlx->player.pos_y = 14;
	mlx->player.dir_x = -1;
	mlx->player.dir_y = 0;
	mlx->player.plan_x = 0;
	mlx->player.plan_y = 0.66;
	mlx->player.move_speed = 0.10;
	mlx->player.rotate_speed = 0.10;
	mlx->player.camera_x = 0;
	int i = 0;
	while(i < 125)
	{
		mlx->keyboard[i] = 0;
		i++;
	}
}

int			ft_load_text(t_mlx *mlx, t_text *text)
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
	t_mlx *yo;
	yo = mlx;
	t_text *papa;
	papa = text;
	// text->texture[0]->img_ptr = mlx_xpm_file_to_image(mlx->mlx_ptr, "./textures/metal.xpm", &text->texture[0]->width, &text->texture[0]->height);
	// text->texture[0]->data = (int *)mlx_get_data_addr(text->texture[0]->img_ptr, &mlx->img.bpp, &mlx->img.size_l, &mlx->img.endian);
	// text->texture[1]->img_ptr = mlx_xpm_file_to_image(mlx->mlx_ptr, "./textures/brick.xpm", &text->texture[1]->width, &text->texture[1]->height);
	// text->texture[1]->data = (int *)mlx_get_data_addr(text->texture[1]->img_ptr, &mlx->img.bpp, &mlx->img.size_l, &mlx->img.endian);
	// text->texture[2]->img_ptr = mlx_xpm_file_to_image(mlx->mlx_ptr, "./textures/stone.xpm", &text->texture[2]->width, &text->texture[2]->height);
	// text->texture[2]->data = (int *)mlx_get_data_addr(text->texture[2]->img_ptr, &mlx->img.bpp, &mlx->img.size_l, &mlx->img.endian);
	// text->texture[3]->img_ptr = mlx_xpm_file_to_image(mlx->mlx_ptr, "./textures/wood.xpm", &text->texture[3]->width, &text->texture[3]->height);
	// text->texture[3]->data = (int *)mlx_get_data_addr(text->texture[3]->img_ptr, &mlx->img.bpp, &mlx->img.size_l, &mlx->img.endian);
	// text->texture[4]->img_ptr = mlx_xpm_file_to_image(mlx->mlx_ptr, "./textures/sprite.xpm", &text->texture[4]->width, &text->texture[4]->height);
	// text->texture[4]->data = (int *)mlx_get_data_addr(text->texture[4]->img_ptr, &mlx->img.bpp, &mlx->img.size_l, &mlx->img.endian);
	return (1);
}