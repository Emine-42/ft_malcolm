/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macheuk- <macheuk-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 18:00:16 by macheuk-          #+#    #+#             */
/*   Updated: 2023/11/09 19:22:45 by macheuk-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*actual;

	if (lst != NULL && *lst != NULL && del != NULL)
	{
		while (lst && *lst)
		{
			actual = (*lst)->next;
			ft_lstdelone(*lst, del);
			*lst = actual;
		}
	}
}
