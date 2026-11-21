/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macheuk- <macheuk-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 10:54:26 by macheuk-          #+#    #+#             */
/*   Updated: 2023/11/23 16:12:08 by macheuk-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	length_dst;
	size_t	length_src;

	if (!dst && !size)
		return (0);
	i = 0;
	length_dst = ft_strlen(dst);
	length_src = ft_strlen(src);
	if (size < length_dst)
		return (length_src + size);
	while (src[i] && ((i + length_dst + 1) < size))
	{
		dst[length_dst + i] = src[i];
		i++;
	}
	dst[length_dst + i] = '\0';
	return (length_dst + length_src);
}
