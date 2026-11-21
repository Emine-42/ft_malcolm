/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macheuk- <macheuk-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 11:37:16 by macheuk-          #+#    #+#             */
/*   Updated: 2023/11/08 13:09:37 by macheuk-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*actual;

	if (lst == NULL)
		return (NULL);
	actual = lst;
	while (actual->next != NULL)
	{
		actual = actual->next;
	}
	return (actual);
}
