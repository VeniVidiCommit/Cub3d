#include "../include/cub3d.h"

static char	**ft_count_string(const char *s, char c)
{
	int		string;
	int		i;
	char	**tab;

	i = 0;
	string = 0;
	while (s[i])
	{
		if ((s[i + 1] == '\0' || s[i + 1] == c || s[i] == c))
			string++;
		i++;
	}
	if (!(tab = (char**)malloc(sizeof(char*) * (string + 1))))
		return (NULL);
	return (tab);
}

static int	ft_count_letter(const char *s, char c, char **tab)
{
	int		i;
	int		string;
	int		letter;

	i = 0;
	string = 0;
	letter = 0;
	while (s[i])
	{
		letter++;
		if ((s[i + 1] == '\0' || s[i + 1] == c || s[i] == c))
		{
			if (!(tab[string] = malloc(sizeof(char) * (letter + 1))))
			{
				while (tab[string])
					free(tab[string--]);
				return (-1);
			}
			string++;
			letter = 0;
		}
		i++;
	}
	return (0);
}

static void		ft_fill_tab(char const *s, char c, char **tab)
{
	int		i;
	int		string;
	int		letter;

	i = 0;
	string = 0;
	letter = 0;
	while (s[i])
	{
			tab[string][letter] = s[i];
			letter++;
		if ((s[i + 1] == '\0' || s[i + 1] == c || s[i] == c))
		{
			tab[string][letter] = '\0';
			string++;
			letter = 0;
		} 
		i++;
	}
	tab[string] = NULL;
}

char	**ft_split_sep(char const *s, char c)
{
	char	**tab;

	if (!(tab = ft_count_string(s, c)))
		return (NULL);
	if (ft_count_letter(s, c, tab) < 0)
	{
		free(tab);
		return (NULL);
	}
	ft_fill_tab(s, c, tab);
	return (tab);
}
