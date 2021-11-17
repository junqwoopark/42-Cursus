/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 08:34:18 by junkpark          #+#    #+#             */
/*   Updated: 2021/11/17 15:21:26 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	int		len;
	int		idx;
	t_list	*ret;

	len = ft_lstsize(lst);
	if (len == 0)
		return (NULL);
	ret = (t_list *)malloc((sizeof(t_list)) * (len));
	if (ret == NULL)
	{
		ft_lstclear(&ret, del);
		return (NULL);
	}
	idx = 0;
	while (idx + 1 < len)
	{
		ret[idx].next = &(ret[idx + 1]);
		ret[idx].content = f(lst -> content);
		lst = lst -> next;
		idx++;
	}
	ret[idx].next = NULL;
	ret[idx].content = f(lst -> content);
	return (ret);
}
