/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrettsc <mbrettsc@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 16:17:18 by mbrettsc          #+#    #+#             */
/*   Updated: 2023/10/15 14:17:28 by mbrettsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

# define EXEC 0
# define HEREDOC 1
# define PIPE 2
# define GREAT 3
# define GREATER 4
# define LESS 5
# define STDINN 0
# define STDOUT 1
# define STDERR 2

typedef struct s_env
{
	char	*key;
	char	*value;
}				t_env;

typedef struct s_data
{
	char	*read_data;
}				t_data;

typedef struct s_lexer
{
	t_list	*lex;
}				t_lexer;

typedef struct s_parse
{
	char	*cmd;
	char	**text;
	int		type;
	int		outfile;
	int		infile;
	int		fd;
	int		pid;
	int		control;
}				t_parse;

typedef struct s_shell
{
	t_list	*env;
	char	*cmd;
	t_lexer	*lex_list;
	t_list	*parse;
	char	*heredoc;
	int		does_have_heredoc;
	int		exec_status;
}				t_shell;

extern t_shell	*g_shell;

t_parse		*parse_(int *j, t_list *new, int *i);
char		*after_dark2(char *key, char *tmp);
char		*quote_control(char *tmp);
char		*set_build(char *str);
char		*before_dollar(char *tmp);
char		*_search_path(void);
char		*get_home(void);
char		**get_args(t_parse *data, t_list *tmp);
char		*ft_strjoin2(char *s1, const char *s2);
int			ft_ultimatestrcmp(char *key, char *tmp, int i);
int			quote_len1(char *data);
int			check(void);
int			is_builtin(t_list *tmp);
int			single_or_multi_command(void);
int			ft_parser(void);
int			create_files(void);
int			create_in_files(t_parse *data3, t_list *tmp3);
int			quote_check(char *data);
int			print_error(void);
int			create_files(void);
int			is_space(char *cmd);
int			*create_pipe(void);
int			*create_pipe(void);
void		signals(int sig);
void		signals_control(void);
void		free_str1(char *str1, int flag);
void		free_tmps(char *str, char *str2, char *str_tmp);
void		_ft_exit_status(t_list *data, char *str1);
void		set_heredoc(int sig);
void		killer(int sig);
void		clear_pipe(int *fd);
void		env_get(char **env, t_shell **shell);
void		get_readline(void);
void		lexer(void);
void		expander(void);
void		get_env_to_lexlist(t_lexer **lex_list);
void		print_list(void *data);
void		exec(char **env);
void		loop_heredoc(void);
void		run_single_command(char **env, t_list *data);
void		free_env(void);
void		free_parser(void);
void		free_loop(int control);
void		free_lexer(void);
void		free_text(char **text);
void		free_(void);
void		erase_after(char *tmp, t_list *data, int i);
void		free_tmp_tmp2(char *tmp, char *tmp2, char *tmp3);
void		ft_tilde_build1(t_list *data, char *key, char *tmp);
void		ft_tilde_build2(t_list *data, char *str);
void		get_after_num(char *tmp, t_list *data, int i);
void		quote_build(char **tmp, char **data, int *i, int *j);
void		ft_exit_status(char *tmp, t_list *data);
void		free_node(t_list *node);
void		welcome_to_parse(t_list	*node, int i, int j, int flag);
void		get_text(t_parse **parse, char *str, int j, int a);
void		tokenize_type(t_parse **parse, const char *str);
void		free_parse(t_parse *parse);
void		parse_init(void);
void		does_dollar_make_sense(char *tmp, t_list *data,
				t_list *shell_data, int i);
void		_does_dollar_make_sense(t_env *y, char *before,
				char *after, t_list *data);
void		exec_echo(t_parse *data);
void		exec_env(void);
void		exec_export(t_parse *data);
void		exec_unset(t_parse *data);
void		exec_pwd(t_parse *data);
void		exec_cd(t_parse *data);
void		create_dup(t_list *data1, int *fd, int fd_index);
void		clear_pipe(int *fd);
void		switch_pipe(int **fd);
void		wait_all(void);
void		execute_builtin_command(t_list *tmp, int *fd, int fd_index);
void		exec_others(t_list *data, char **env, int *fd, int fd_index);
void		execve_child_free(char **str);
void		get_env_utils(t_list **data, char *tmp, char *tmp2);

#endif