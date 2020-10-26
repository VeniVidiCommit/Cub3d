#include "../include/cub3d.h"

static  int         check_if_map_is_split(char **file_n)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (file_n[i])
    {
        j = 0;
        while(file_n[i][j])
        {
            if (file_n[i][j] == '\n' && file_n[i + 1][0] == '\n')
                    return (error("The map is split\n", -1));
            j++;
        }
        i++;
    }
    return (0);
}

static  int         check_start_position(t_mlx *mlx, char **file, int *i, int *j, int *check)
{
    while (file[*i][*j])
    {
        if ((*i == 0 || *i == mlx->map.line - 1) && (file[*i][*j] == 0 || ft_strchr("SNEW2", file[*i][*j])))
            return (error("Map is not close\n", -1));
        if (ft_strchr("012SNEW ", file[*i][*j]))
        {
            if (ft_strchr("SNEW", file[*i][*j]))
            {
                if (*check == 1)
                    return (error("Multiple definition of start position\n", -1));
                *check = 1;
            }
        }
    else
        return (error("Invalid character inside definition of map\n", -1));
    *j = *j + 1;
    }
    return(0);
}

static  int         check_if_map_close(char **file, t_mlx *mlx)
{
    int i;
    int j;
    int check;

    i = 0;
    j = 0;
    check = 0;
    while (file[i])
    {
        j = 0;
        while(file[i][j] == ' ')
            j++;
        if (file[i][j] == '0' || ft_strchr("SNEW2", file[i][j]))
            return (error("Map is not close (1)\n", -1));
        if (check_start_position(mlx, file, &i, &j, &check) < 0)
            return (-1);
        if (file[i][j - 1] == '0' || ft_strchr("SNEW2", file[i][j - 1]))
            return (error("Map is not close\n", -1));
        i++;
    }
    if (i == 0)
        return (error("No map definition\n", -1));
    return (0);
}

static  int        check_border(char **file, int min_len, int i, int j, t_mlx *mlx)
{
    if (file[i][j] == ' ')
    {
        if (i == 0 && file[i + 1][j] == '0')
            return (error("Map is not close\n", -1));
        if (i == mlx->map.line - 1 && file[i - 1][j] == '0')
            return (error("Map is not close\n", -1));
        if (i > 0 && i < mlx->map.line - 1 && (file[i - 1][j] == '0'  || file[i + 1][j] == '0'))
            return (error("Map is not close\n", -1));
    }
    if (j > min_len)
    {
        if (file[i][j] != '1')
            return (error("Map is not close\n", -1));
    }
    return (0);
}

int         ft_check_map(t_mlx *mlx, char **file, char **file_n)
{
    int i;
    int j;
    int min_len;

    i = 0;
    j = 0;
    if (check_if_map_is_split(file_n) < 0 || check_if_map_close(file, mlx))
        return (-1);
    while (file[i])
    {
        j = 0;
        min_len = define_min_len(file, i, mlx);
        while (file[i][j])
        {
            if (check_border(file, min_len, i, j, mlx) < 0)
                return (-1);
            j++;
        }
        i++;
    }
    return (0);
}