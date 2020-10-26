#include "../include/cub3d.h"

static  void        get_max_col(char **file, t_mlx *mlx)
{
    int i;

    i = 0;
    while (file[i])
    {
        if (ft_strlen(file[i]) > (size_t)mlx->map.col)
            mlx->map.col = ft_strlen(file[i]);
        mlx->map.line++;
        i++;
    }
}

int         ft_malloc_map(t_mlx *mlx, char **file)
{
    int i;
    int k;

    i = -1;
    get_max_col(file, mlx);
    if (!(mlx->map.world_map = malloc(sizeof(int *) * mlx->map.line)))
        return (error("Malloc fail\n", -1));
    while(++i < mlx->map.line)
    {
        if (!(mlx->map.world_map[i] = malloc(sizeof(int) * mlx->map.col)))
        {
            while (i--)
                free(mlx->map.world_map[i]);
            free(mlx->map.world_map);
            return (error("Malloc fail\n", -1));
        }
        k = -1;
        while (++k < mlx->map.col)
            mlx->map.world_map[i][k] = 1;
    }
    return (0);
}

static  void            set_player_position_2(t_mlx *mlx, char **file, int i, int j)
{
    if (file[i][j] == 'E')
    {
        mlx->player.dir_x = 0;
        mlx->player.dir_y = 1;
        mlx->player.plan_x = 0.66;
        mlx->player.plan_y = 0;
    }
    if (file[i][j] == 'W')
    {
        mlx->player.dir_x = 0;
        mlx->player.dir_y = -1;
        mlx->player.plan_x = -0.66;
        mlx->player.plan_y = 0;
    }
}

static  void            set_player_position(t_mlx *mlx, char **file, int i, int j)
{
    mlx->map.world_map[i][j] = 0;
    mlx->player.pos_x = i;
    mlx->player.pos_y = j;
    mlx->player.pop = 1;
    if (file[i][j] == 'N')
    {
        mlx->player.dir_x = -1;
        mlx->player.dir_y = 0;
        mlx->player.plan_x = 0;
        mlx->player.plan_y = 0.66;
    }
    if (file[i][j] == 'S')
    {
        mlx->player.dir_x = 1;
        mlx->player.dir_y = 0;
        mlx->player.plan_x = 0;
        mlx->player.plan_y = -0.66;
    }
    set_player_position_2(mlx, file, i, j);
}

void         fill_map_world(t_mlx *mlx, char **file)
{
    int i;
    int j;

    i = -1;
    while (file[++i])
    {
        j = -1;
        while (file[i][++j])
        {
            if (file[i][j] == '0')
                mlx->map.world_map[i][j] = 0;
            else if (file[i][j] == '2')
            {
                mlx->map.world_map[i][j] = 2;
                mlx->count_sprite++;
            }
            else if (ft_strchr("NWES", file[i][j])) 
                set_player_position(mlx, file, i , j);
            else
                mlx->map.world_map[i][j] = 1;
        }
    }
}