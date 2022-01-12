/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrandy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 13:25:28 by lbrandy           #+#    #+#             */
/*   Updated: 2021/07/17 17:35:33 by lbrandy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*left_checking(char **line, char **left)
{
	char	*p;

	p = NULL;
	if (*left)
	{
		p = ft_strchr(*left, '\n');
		if (p)
		{
			*p = '\0';
			*line = ft_strdup(*left);
			if (!*line)
				ft_clean_left(left);
			*left = ft_strcpy(*left, ++p);
		}
		else
		{
			*line = ft_strdup(*left);
			free(*left);
			*left = NULL;
		}
	}
	else
		ft_check_line(left, line);
	return (p);
}

static int	free_help(char *temp, char *left)
{
	free(left);
	free(temp);
	return (-1);
}

static int	doing_line(char **p, char *buf, char **left, char **line)
{
	char	*temp;

	*p = ft_strchr(buf, '\n');
	if (*p)
	{
		**p = '\0';
		(*p)++;
		*left = ft_strdup(*p);
		if (!*left)
		{
			free(*line);
			*line = 0;
			free(buf);
			return (-1);
		}
	}
	temp = *line;
	*line = ft_strjoin(*line, buf);
	if (!*line)
		return (free_help(temp, *left));
	free(temp);
	return (1);
}

static int	ternar_help(char *p)
{
	if (p)
		return (1);
	else
		return (0);
}

int	get_next_line(int fd, char **line)
{
	char			*buf;
	static char		*left;
	int				n;
	char			*p;

	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (BUFFER_SIZE < 1 || read(fd, buf, 0) < 0 || (!(line))
		|| (!buf))
		return (-1);
	p = left_checking(line, &left);
	if (!(*line))
		return (-1);
	n = read(fd, buf, BUFFER_SIZE);
	while (!p && n > 0)
	{
		buf[n] = '\0';
		if (doing_line(&p, buf, &left, line) == -1)
		{
			free(buf);
			return (-1);
		}
		n = read(fd, buf, BUFFER_SIZE);
	}
	free(buf);
	return (ternar_help(p));
}
