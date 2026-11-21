/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macheuk- <macheuk-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 10:10:23 by macheuk-          #+#    #+#             */
/*   Updated: 2023/11/23 16:26:45 by macheuk-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void	*ft_free_all(char **tab, int index)
{
	int	i;

	i = 0;
	while (i < index)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
}

int	ft_tabsize(char const *s, char c)
{
	int	n;
	int	i;
	int	lastsep;

	i = 0;
	n = 0;
	lastsep = -1;
	while (s[i])
	{
		if (s[i] == c)
		{
			if (lastsep != (i - 1))
				n++;
			lastsep = i;
		}
		else
		{
			if (s[i] != c && s[i + 1] == '\0')
				n++;
		}
		i++;
	}
	return (n);
}

int	ft_rangetochar(char const *s, char c, int index)
{
	int	n;
	int	i;

	i = 0;
	n = 0;
	while (s[i])
	{
		if (s[i] == c)
		{
			if (n != 0 && index == 0)
				return (n);
			else
			{
				if (index > 0 && s[i + 1] != c && n != 0)
				{
					index--;
					n = 0;
				}
			}
		}
		else
			n++;
		i++;
	}
	return (n);
}

void	ft_fill_tab(char *tab, char const *s, char c, int index)
{
	int	lastsep;
	int	i;
	int	j;

	lastsep = -1;
	i = 0;
	j = 0;
	while (s[i] && index >= 0)
	{
		if (s[i] != c && index == 0)
		{
			tab[j] = s[i];
			j++;
		}
		if (s[i] == c && index >= 0)
		{
			if (lastsep != (i - 1))
				index--;
			lastsep = i;
		}
		if (index == 0 && (s[i] == c || (s[i + 1] == '\0' || s[i + 1] == c)))
			tab[j] = '\0';
		i++;
	}
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	int		num_strs;
	int		i;

	i = 0;
	if (!s)
		return (NULL);
	num_strs = ft_tabsize(s, c);
	tab = malloc(sizeof(char *) * (num_strs + 1));
	if (!tab)
		return (NULL);
	while (i < num_strs)
	{
		tab[i] = malloc(sizeof(char) * (ft_rangetochar(s, c, i) + 1));
		if (!tab[i])
			return (ft_free_all(tab, i));
		ft_fill_tab(tab[i], s, c, i);
		i++;
	}
	tab[i] = NULL;
	return (tab);
}
