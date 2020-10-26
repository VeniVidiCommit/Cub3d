#include "../include/cub3d.h"

int         error(char *msg, int ret)
{
    write(2, "Error\n", 7);
    write(2, msg, ft_strlen(msg));
    return (ret);
}
char         *error_char(char *msg, char *err)
{
    write(2, "Error\n", 7);
    write(2, msg, ft_strlen(msg));
    return (err);
}

int         error_free(char *msg, int ret, char **tab)
{
    ft_free_tab(tab);

    write(2, msg, ft_strlen(msg));
    return (ret);
}