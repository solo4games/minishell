/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_back_redir.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrandy <lbrandy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 11:12:09 by lbrandy           #+#    #+#             */
/*   Updated: 2021/10/02 16:16:26 by lbrandy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ternar_help(int b_read)
{
	if (b_read > 0)
		return (1);
	else
		return (b_read);
}

static int	get_next_line(char **line)
{
	char	buf[10000];
	int		b_read;
	int		i;

	i = 0;
	if ((read(0, &buf[i], 0) < 0) || !(line))
		return (-1);
	b_read = read(0, &buf[i], 1);
	while (b_read > 0 && buf[i] != '\n')
	{
		i++;
		b_read = read(0, &buf[i], 1);
	}
	buf[i] = '\0';
	*line = malloc(i * sizeof(char));
	if (b_read != -1 && (*line))
	{
		i = -1;
		while (buf[++i])
			(*line)[i] = buf[i];
		(*line)[i] = '\0';
	}
	return (ternar_help(b_read));
}

void	do_redir(char *name, t_g_lst *grand)
{
	int		i;
	char	*str;

	str = NULL;
	sig_init_for_ch_redir();
	close(grand->pip[0]);
	write(1, "> ", 2);
	i = get_next_line(&str);
	while (i > 0)
	{
		if (ft_strncmp(str, name, ft_strlen(name)) == 0)
			break ;
		write(grand->pip[1], str, ft_strlen(str));
		write(grand->pip[1], "\n", 1);
		write(1, "> ", 2);
		i = get_next_line(&str);
	}
	exit(g_exit_sta.tus);
}

int	readline_mass(char *name, t_g_lst *grand)
{
	int		status;

	if ((pipe(grand->pip)) < 0)
		exit(g_exit_sta.tus);
	grand->pid = fork();
	if (!grand->pid)
		do_redir(name, grand);
	waitpid(grand->pid, &status, WUNTRACED | WCONTINUED);
	g_exit_sta.tement = WEXITSTATUS(status);
	close(grand->pip[1]);
	return (grand->pip[0]);
}
