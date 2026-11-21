/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macheuk- <macheuk-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 18:26:07 by macheuk-          #+#    #+#             */
/*   Updated: 2023/11/21 13:28:11 by macheuk-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int		n;
	unsigned int		i;
	char				*str;

	if (!s)
		return (NULL);
	if (ft_strlen(s) < start)
		return (ft_strdup(""));
	else if (ft_strlen(s) + 1 < len + start)
		n = ft_strlen(s) - start;
	else
		n = len;
	str = (char *)malloc(sizeof(*s) * (n + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (s[start + i] && i < n)
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
