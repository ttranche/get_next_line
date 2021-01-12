/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttranche <ttranche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 11:48:08 by ttranche          #+#    #+#             */
/*   Updated: 2020/11/19 19:28:56 by ttranche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_mem	*get_store(int fd, t_mem **start)
{
	t_mem	*list;
	t_mem	*new;

	list = *start;
	while (list)
	{
		if (list->fd == fd)
			return (list);
		if (list->next)
			list = list->next;
		else
			break ;
	}
	if (!(new = malloc(sizeof(t_mem))))
		return (NULL);
	new->fd = fd;
	new->next = NULL;
	new->read = 0;
	new->start = 0;
	if (*start)
		list->next = new;
	else
		*start = new;
	return (new);
}

void	free_store(int fd, t_mem **start)
{
	t_mem *prev;
	t_mem *aftr;
	t_mem *curr;

	prev = NULL;
	aftr = *start;
	while (aftr)
	{
		if (aftr->fd == fd)
		{
			if (prev == NULL)
				*start = aftr->next;
			else
				prev->next = aftr->next;
			curr = aftr;
			aftr = aftr->next;
			free(curr);
		}
		else
		{
			prev = aftr;
			aftr = prev->next;
		}
	}
}

char	*ft_addstr(char *dst, char *src, size_t len)
{
	char	*mem;
	size_t	i;
	size_t	start;

	start = dst ? ft_strlen(dst) : 0;
	if (!(mem = malloc(start + len + 1)))
		return (NULL);
	i = 0;
	while (i++ < start)
		mem[i - 1] = dst[i - 1];
	i = 0;
	while (i < len)
	{
		mem[i + start] = src[i];
		++i;
	}
	mem[i + start] = 0;
	if (dst)
		free(dst);
	return (mem);
}

int		add_line(char **line, t_mem *store)
{
	int i;
	int dline;

	i = 0;
	dline = 0;
	while (store->start + i < store->read)
	{
		if (store->mem[store->start + i] == '\n' && (dline = 1))
			break ;
		++i;
	}
	if (!(*line = ft_addstr(*line, store->mem + store->start, i)))
		return (2);
	store->start += i;
	if (dline)
	{
		store->start++;
		return (1);
	}
	else
		store->start = 0;
	return (0);
}

int		get_next_line(int fd, char **line)
{
	static t_mem	*storage;
	t_mem			*store;
	int				error;

	if (!line || BUFFER_SIZE <= 0 || !(store = get_store(fd, &storage)))
		return (-1);
	*line = NULL;
	while (1)
		if ((error = add_line(line, store)))
			break ;
		else if ((store->read = read(fd, store->mem, BUFFER_SIZE)) <= 0)
			break ;
	if (error == 2 || (error = store->read) <= 0)
	{
		if (error != 0)
		{
			if (*line)
				free(*line);
			*line = NULL;
		}
		free_store(fd, &storage);
		return (error);
	}
	return (1);
}
