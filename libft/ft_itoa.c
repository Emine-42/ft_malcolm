/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macheuk- <macheuk-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 13:32:59 by macheuk-          #+#    #+#             */
/*   Updated: 2023/11/21 13:32:42 by macheuk-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_count_size(int n)
{
	int	count;
	int	num;

	count = 1;
	num = n;
	if (n < 0)
	{
		count++;
		num = -n;
	}
	while (num >= 10)
	{
		count++;
		num /= 10;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	int		count;
	char	*str;
	int		num;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	count = ft_count_size(n);
	num = n;
	str = (char *)malloc(sizeof(char) * (count + 1));
	if (!str)
		return (NULL);
	str[count] = '\0';
	if (n < 0)
		n = -n;
	while (count > 0)
	{
		count--;
		str[count] = (n % 10) + '0';
		n /= 10;
	}
	if (num < 0)
		str[0] = '-';
	return (str);
}
