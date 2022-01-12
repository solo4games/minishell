/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrandy <lbrandy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 16:09:06 by trachell          #+#    #+#             */
/*   Updated: 2021/10/02 16:26:20 by lbrandy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include "../srcs/libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/ioctl.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <termios.h>
# include <errno.h>

/*Структуры парсера*/
typedef struct s_redir
{
	char			*filename;
	char			*type;
	int				fd;

}				t_redir;

typedef struct s_exit_status
{
	int				tus;
	int				tement;
}				t_exit_status;

t_exit_status		g_exit_sta;
typedef struct s_token
{
	char			*str;
	struct s_token	*next;
}				t_token;

/*Массив списков для обработки команд*/
typedef struct s_g_lst
{
	char			*path_f;
	char			**path;
	char			**paths;
	char			**cmd_flags;
	int				i;
	int				j;
	char			*str;
	struct s_token	*first_list;
	int				r_cnt;
	int				p_r_cnt;
	int				p_cnt;
	t_redir			*redirs;
	int				redir_count;
	int				pip[2];
	int				fd;
	int				fd1;
	int				fd2;
	int				pid;
}				t_g_lst;

/*Общая структура*/
typedef struct s_all
{
	int				b_flag;
	int				flag;
	pid_t			pid;
	int				i;
	int				pipes;
	t_g_lst			*grand;
	int				**fd_pipe;
	t_list			*envp_list;
	int				exit_flag;
	struct termios	config;
}				t_all;

/*Парсер-функции*/
char		*pars_quotes(char *str, char **env);
char		*ft_dollar(char *str, int *i, char **env);
char		**ft_check_razdel(char *str);
char		*preparser(char *str);
void		token_pb(t_token **head, char *str);
t_token		*do_token_list(t_token *head, char *str);
int			not_in_quote(char *str, int end);
t_g_lst		*grandlist_creation(char *str, int pipes);
int			check_redir(char *str);
int			pipe_count(char *str);
int			parser_main(char **env, t_all *all);
int			readline_mass(char *name, t_g_lst *grand);
t_list		*envp_list_create(char **envp);
void		my_env_func(t_list *envp_list);
void		my_export_func(char **mass, t_list *envp_list);
void		my_unset_func(char **mass, t_list **envp_list);
void		my_cd_func(t_list *envp_list, char **mass);
void		my_pwd_func(void);
void		my_echo_func(char **mass);
int			ft_strcmp(const char *str1, const char *str2);
void		my_exit_func(char **mass, t_all *all);
int			ifkey(char c);
char		*replace_envp(char *str, int j, int *i, char *temp);
void		change_pwd(t_list *tmp, char *pwd, char *old_pwd);
void		change_envp(t_list *envp_list, char *old_pwd);
char		*walk(char *path, char *temp_old, int flag, int i);
int			changing(t_list *tmp, char *path);
int			get_home(char *path, t_list *envp_list);
char		*go_up(char *str);
char		*go_down(char *str, char *sub);
int			ft_doing_dup(char *str, t_list *lst, int i);
int			ft_check_duplicate(t_list *envp_list, char *str);
void		ft_create_str_plus(t_list **envp_list, char *str);
int			doing_overload(t_list *lst, char *str, int i);
int			ft_check_over(t_list **envp_list, char *str);
int			new_str_count(char *str);
t_redir		*redir_fd_create(t_token *list, t_g_lst *grand);
void		pipe_fd_create(t_all *all, char *str);
void		fd_create(char *type, t_redir *red,
				char *name, t_g_lst *grand);
int			search_envp(char *str, char **envp);
void		call_child(t_all *all, char **envp);
t_redir		*created(t_token *tmp, t_g_lst *grand);
void		d_red(char *type, t_redir *red,
				char *name, t_g_lst *grand);

/*Я сделяль*/
void		init_pipes(t_all *all);
void		ch_p_handler(t_all *all, char **envp);
void		err_hand(char *message);
void		ft_lstfree_cont(void *content);
void		without_pipes(t_all *all, char **envp, t_g_lst *grand);
void		with_pipes(t_all *all, char **envp);
void		init_fields(t_all *all, char **envp);
void		free_envp(char **mass, int flag);
char		**from_list_to_mass(t_list *envp_list, char **mass_envp, int flag);
void		sig_init(void);
void		sig_init_for_ch(void);
void		sig_init_for_ch_redir(void);
void		catch_signal_c(int signum);
void		ctrl_d(void);
void		ctrl_c(int val);
void		ctrl_c_d(int val);
void		ctrl_sl(int val);
void		dup_handler(t_all *all, t_g_lst *grand);
void		dup_reverse(t_all *all);
void		redirs(t_g_lst *grand, t_all *all);
char		**list_separator(t_token *head, int redir_count);
void		cmd_handl(char **envp, t_g_lst *grand, t_list **e_list, t_all *all);
int			check_command(char *command, t_all *all);
void		check_exec(t_g_lst *grand);
void		do_builtins(char **mass, t_list **envp_list, t_all *all);

#endif