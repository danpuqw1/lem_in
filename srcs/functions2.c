/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dteemo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 18:00:17 by dteemo            #+#    #+#             */
/*   Updated: 2020/11/05 18:00:18 by dteemo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

unsigned int	ft_hash(const char *datum, int size)
{
	unsigned int hash_value;
	unsigned int i;

	hash_value = 0;
	while (*datum++)
	{
		hash_value = (hash_value << ONE_EIGHTH) + *datum;
		if ((i = hash_value & HIGH_BITS) != 0)
			hash_value = (hash_value ^ (i >> THREE_QUARTERS)) & ~HIGH_BITS;
	}
	return (hash_value % size);
}

t_node			*ft_search(const char *name, t_node **rooms)
{
	int		id;
	t_node	*buf;

	id = ft_hash(name, MAP_SIZE);
	if (rooms[id] == NULL)
		return (NULL);
	else if (ft_strcmp(rooms[id]->name, name) == 0)
		return (rooms[id]);
	else
	{
		buf = rooms[id];
		while (buf != NULL)
		{
			if (ft_strcmp(buf->name, name) == 0)
				return (buf);
			buf = buf->next;
		}
	}
	return (NULL);
}

char			*ft_strchrjoin(char *dest, char *src, char c)
{
	char	*new;
	int		pars[4];

	pars[0] = 0;
	pars[1] = 0;
	if ((dest == NULL && src == NULL) || (c == '\0'))
		return (NULL);
	else if (dest == NULL && src != NULL)
		return (ft_strdup(src));
	pars[2] = ft_strlen(dest);
	pars[3] = ft_strlen(src);
	new = ft_strnew(pars[2] + pars[3] + 1);
	while (pars[0] < (pars[2] + pars[3] + 1))
	{
		if (pars[0] < pars[2])
			new[pars[0]] = dest[pars[0]];
		else if (pars[0] == pars[2])
			new[pars[0]] = c;
		else
			new[pars[0]] = src[pars[1]++];
		pars[0]++;
	}
	new[pars[0]] = '\0';
	ft_memdel((void **)&dest);
	return (new);
}

void			ft_nodedelone(t_node **alst)
{
	t_node *new_l;

	new_l = *alst;
	if (new_l)
	{
		if (new_l->name != NULL)
			free(new_l->name);
		if (new_l->rel != NULL)
			free(new_l->rel);
		free(*alst);
		*alst = NULL;
	}
}

void			ft_nodedel(t_node **alst)
{
	t_node **buf;

	buf = alst;
	if (buf)
	{
		while ((*buf)->next)
			ft_nodedel(&(*buf)->next);
		ft_nodedelone(&(*buf));
	}
}
