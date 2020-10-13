#include "cub3d.h"

int         ft_compt_args(char **tab, int size)
{
    int i;

    i = 0;
    while (tab[i])
        i++;
    if (i == size)
        return (1);
    return (0);
}
void        ft_free_tab(char **tab)
{
    int i;

    i = 0;
    while (tab[i])
    {
        free(tab[i]);
        i++;
    }
    free(tab);
}

int         ft_str_is_digit(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (ft_isdigit(str[i]))
            i++;
        else
            return (0);
    }
    return (1);
}

int         ft_hash(char *key)
{
    int i;
    int hash_value;
    i = 0;
    hash_value = 0;
    while (key[i])
    {
        hash_value = hash_value << 8;
        hash_value += key[i];
        i++;
    }
    return (hash_value % H_SIZE);
}

int         error(char *msg, int ret)
{
    write(2, "Error\n", 7);
    write(2, msg, ft_strlen(msg));
    return (ret);
}

int         error_free(char *msg, int ret, char **tab)
{
    ft_free_tab(tab);
    write(2, "Error\n", 7);
    write(2, msg, ft_strlen(msg));
    return (ret);
}