/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dteemo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 17:21:01 by dteemo            #+#    #+#             */
/*   Updated: 2020/11/03 17:21:02 by dteemo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	ft_quinit(t_queue *q)
{
	q->frnt = 1;
	q->rear = 0;
}

int		ft_quinsert(t_queue *q, char *s)
{
	if (q->rear < MAP_SIZE)
	{
		q->rear++;
		q->qu[q->rear] = ft_strdup(s);
		return (1);
	}
	else
		return (0);
}

int		ft_quempty(t_queue *q)
{
	if (q->rear < q->frnt)
		return (1);
	else
		return (0);
}

char	*ft_qupop(t_queue *q)
{
	char *node;

	if (ft_quempty(q) == 1)
		return (NULL);
	node = q->qu[q->frnt];
	q->frnt++;
	return (node);
}
