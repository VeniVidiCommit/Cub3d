#include "../include/cub3d.h"

static  int         set_sprite_position(t_mlx *mlx, char **file)
{
    int i;
    int j;
    int nb;

    i = -1;
    nb = 0;
    if (!(mlx->sprite = malloc(sizeof(t_sprite) * mlx->count_sprite)))
        return(error("Malloc failed in set_sprite_position\n", -1));
    while (file[++i])
    {
        j = 0;
        while (file[i][j])
        {
            if (file[i][j] == '2')
            {
                mlx->sprite[nb].x = i;
                mlx->sprite[nb].y = j;
                nb++;
            }
            j++;
        }
    }
    return (0);
}

int         ft_count(t_mlx *mlx, char **file, char **file_n)
{
    int i;
    int j;

    i = 0;
    j = 0;
    if (ft_malloc_map(mlx, file) < 0 || ft_check_map(mlx, file, file_n) < 0)
        return (-1);
    fill_map_world(mlx, file);
    if (mlx->player.pop == 0)
        return (error("Need to initilize player position\n", -1));
    if (set_sprite_position(mlx, file) < 0)
        return (-1);
    return (0);
}