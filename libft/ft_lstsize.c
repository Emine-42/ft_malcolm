/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macheuk- <macheuk-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 10:56:01 by macheuk-          #+#    #+#             */
/*   Updated: 2023/11/08 13:09:53 by macheuk-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		counter;
	t_list	*actual;

	if (lst == NULL)
		return (0);
	counter = 1;
	actual = lst;
	while (actual->next != NULL)
	{
		counter++;
		actual = actual->next;
	}
	return (counter);
}
