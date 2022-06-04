/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkansoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 12:11:50 by zkansoun          #+#    #+#             */
/*   Updated: 2022/05/31 13:50:52 by wilhelmfermey    ###   ########.fr       */
/*   Updated: 2022/05/30 17:57:01 by wilhelmfermey    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "LIB42/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h>
# include <errno.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <curses.h>
# include <term.h>
# include <signal.h>
# include <stdint.h>
# include <sys/stat.h>

t_list	**g_envp;

typedef struct s_seg
{
	char			**tokens;
	char			*cmd;
	char			**input;
	char			**output;
	char			*flags;
	char			**args;
	char			**array;
	int				fd[2];
	int				fdd;
	struct s_seg	*next;
}	t_seg;

/* ******************************** MAIN ************************************ */
void	add_list(t_seg **seg);
t_seg	**take_tokens(char **segments);
int		prompt(char **path);
void	fill_envp(char **envp);

/* ******************************** FILL ************************************ */
void	fill_cmd(t_seg **seg, char **path);
void	fill_flags(t_seg **seg);
void	fill_input(t_seg **seg);
void	fill_output(t_seg **seg);
void	fill_args(t_seg **seg);
int		ft_is_not_inout(char *str, t_seg *seg);

/* ******************************* UTILS ************************************ */
char	*ft_strjoin2(char *str, char *buff);
int		ft_lstsize2(t_seg **lst);
char	*ft_strstr(char *str, char *to_find);
int		ft_check_args(char **strr, char *str);

/* ******************************* UTILS2 *********************************** */
void	ft_print_list(t_list **head);
void	del_content(t_list **head, char *content);
char	**add_line(char **tabb, char *str);
char	**add_line_end(char **tabb, char *str);
void	print_table(char **str);

/* ******************************* UTILS3 *********************************** */
int     ft_strcmp(char *s1, char *s2);
void	update_exit_code(char *str);
void    add_list(t_seg **seg);

/* ***************************** CHECK_QUOTE ********************************* */
int		ft_even(t_seg **seg);
int		check_args(t_seg **seg);

/* **************************** CHECK_VARIABLE ******************************* */
void	ft_check_variable(t_seg **seg, char **envp);
int		check_seg(t_seg **seg);
int		ft_line_space(char *str);

/* ******************************* ONE SEG *** ******************************* */
void	ft_one_arg(char *line);
int		ft_check_one_arg(char *line);

 /* ***************************** FT_PIPEX ********************************** */
int		ft_check(t_seg **seg, char *line);
int		ft_cmd(t_seg **seg, char **path);
int		ft_choose(t_seg **seg, char **path);
void	ft_pipex(t_seg **seg, char **path);

/* ******************************** FT_CD ************************************ */
void	ft_cd(t_seg **seg);
void	set_env(char *var, char *val);
char	*get_value_env(char *var);

/* ******************************** FT_SPLIT_QUOTES ************************** */
char	**ft_split_quotes(char const *s, char c);

/* *************************** substitute_var ******************************** */
int		check_sq(char *str, int index);
char	*get_var(char *str);
char	*replace_var_envp(char *str, t_list **g_envp, int index);
void	replace_var(t_seg **seg, t_list **g_envp);

/* ******************************* FT_ARRAY ********************************** */
char	**ft_array(t_seg **seg);

/* ******************************** EXECVE *********************************** */
void	ft_child(t_seg **res, int *fdd);
void	ft_parents(t_seg **res, int *fdd);
void	ft_pipe_builtin(t_seg **seg);

/* ******************************** FT_ECHO ********************************* */
void	ft_echo_all_empty(t_seg **seg);
void	ft_echo_no_redir(t_seg **seg);
void	ft_echo_redir(t_seg **seg);
void	ft_echo(t_seg **seg);

/* ******************************** FT_PWD ********************************* */
void	ft_pwd(t_seg **seg);
void	simple_cases(t_seg **seg);

/* ******************************** FT_EXPORT ****************************** */
void	ft_export(t_seg **seg);
int		check_name(char *str);

/* ******************************** FT_UNSET ****************************** */
int		chech_name_unset(char *str);
void	ft_unset(t_seg **seg);

/* ******************************** FT_ENV ******************************** */
void	ft_env(t_seg **seg);

/* ******************************** FT_EXIT ******************************** */
void	ft_exit(t_seg **seg);

/* ******************************* FT_CHILD ******************************* */
void	ft_child_input2(t_seg **res, char *str);
void	ft_child_input(t_seg **res);
void	ft_child_output(t_seg **res, int *fdd);
void	check_heredoc(t_seg **seg);

/* ******************************* FREE_DATA ***************************** */
void	free_table(char **str);
void	free_struc(t_seg **seg);
void	free_env(void);

/* ******************************* MERGE_FILES ************************** */
void	merge_files(char **input, int fdd);
void	add_STDIN(int fdd);
void	handle_all_out(char **out);

/* ******************************* SIGNALS ************************** */
void	run_signals(int sig);

#endif
