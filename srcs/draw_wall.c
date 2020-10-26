#include "../include/cub3d.h"

static	void		ft_draw_flor_ground(t_mlx *mlx, int draw_end, int width)
{
	int draw_start;

	draw_start = draw_end;
	while (draw_start < mlx->win_height)
	{
		mlx->img.data[draw_start * mlx->win_width + width - 1] = mlx->f_color;
		mlx->img.data[(mlx->win_height - draw_start - 1) * mlx->win_width + width] = mlx->c_color;
		draw_start++;
	}
}

static	t_img		*ft_get_info_wall(t_mlx *mlx, t_info_wall *info, int draw_start)
{
	t_img *g_texture;

	if (mlx->vec.side <= 1)
		info->wall_x = mlx->player.pos_y + mlx->vec.perp_wall_dist * mlx->vec.ray_dir_y;
	else
		info->wall_x = mlx->player.pos_x + mlx->vec.perp_wall_dist * mlx->vec.ray_dir_x;
	info->wall_x -= floor(info->wall_x);
	if (mlx->vec.side == 0)
		g_texture = mlx->texture[0];
	if (mlx->vec.side == 1)
		g_texture = mlx->texture[1];
	if (mlx->vec.side == 2)
		g_texture = mlx->texture[2];
	if (mlx->vec.side == 3)
		g_texture = mlx->texture[3];
	info->text_x = (int)(info->wall_x * (double)g_texture->width);
	if (mlx->vec.side <= 1 && mlx->vec.ray_dir_x > 0)
		info->text_x = g_texture->width - info->text_x - 1;
	if (mlx->vec.side >= 2 && mlx->vec.ray_dir_y < 0)
		info->text_x = g_texture->width - info->text_x - 1;
	info->step = 1.0 * g_texture->height / mlx->vec.line_height;
	info->text_pos = (draw_start - mlx->win_height / 2 + mlx->vec.line_height / 2) * info->step;
	return (g_texture);
}

void				ft_draw_wall_text(int width, int draw_start, int draw_end,t_mlx *mlx)
{
	t_img		*g_texture;
	t_info_wall	info;
	int			y;
	int			text_y;

	ft_bzero(&info, sizeof(t_info_wall));
	g_texture = ft_get_info_wall(mlx, &info, draw_start);
	y = draw_start;
	while (y < draw_end)
	{
		text_y = (int)info.text_pos & (g_texture->height - 1);
		info.text_pos += info.step;
		mlx->img.data[y * mlx->win_width + width - 1] = g_texture->data[info.text_x + text_y * g_texture->height];
		y++;
	}
	ft_draw_flor_ground(mlx, draw_end, width);
}