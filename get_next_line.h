/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttranche <ttranche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 11:35:34 by ttranche          #+#    #+#             */
/*   Updated: 2020/11/19 17:45:13 by ttranche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>

typedef struct		s_mem
{
	int				fd;
	int				start;
	int				read;
	char			mem[BUFFER_SIZE < 0 ? 0 : BUFFER_SIZE];
	struct s_mem	*next;
}					t_mem;

int					get_next_line(int fd, char **line);
int					ft_strlen(char *s);

#endif
