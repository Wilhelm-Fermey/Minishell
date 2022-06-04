/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wilhelmfermey <marvin@42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 18:26:04 by wilhelmfermey     #+#    #+#             */
/*   Updated: 2022/05/23 18:12:32 by wilhelmfermey    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_value_env(char *var)
{
	t_list	*tmp;
	char	*val;
	int	size[2];

	tmp = *g_envp;
	size[0] = (int)(ft_strlen(var));
	while (tmp)
	{
		size[1] = (int)(ft_strlen(tmp->content));
		if (!ft_strncmp(var, tmp->content, ft_strlen(var)))
		{
			val = ft_substr(tmp->content, size[0], size[1] - size[0]);
			return (val);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

void	set_env(char *var, char *val)
{
	t_list	*tmp;
	int	size[2];

	tmp = *g_envp;
	size[0] = (int)(ft_strlen(var));
	while (tmp)
	{
		if (!ft_strncmp(tmp->content, var, size[0]))
		{
			free (tmp->content);
			tmp->content = ft_strjoin(var, val);
			break ;
		}
		tmp = tmp->next;
	}
}
void	ft_cd(t_seg **seg)
{
	t_seg	*tmp;
	char	*str;
	char	*OLDPWD;

	tmp = *seg;
	str = NULL;
	update_exit_code("0");
	OLDPWD = get_value_env("PWD=");
	if (!tmp->args[0])
		str = ft_substr(getenv("HOME"), 0, ft_strlen(getenv("HOME")));
	else if(!ft_strcmp(tmp->args[0], "~") && !tmp->args[1])
		str = ft_substr(getenv("HOME"), 0, ft_strlen(getenv("HOME")));
	else if (tmp->args[0][0] == '~' && tmp->args[0][1] != '\0' && !tmp->args[1])
		str = ft_strjoin(getenv("HOME"), tmp->args[0] + 1);

	else if (tmp->args[0] && !tmp->args[1])
		str = ft_substr(tmp->args[0], 0, ft_strlen(tmp->args[0])); 
	else if (tmp->args[0] && tmp->args[1])
	{
		update_exit_code("1");
		if (!tmp->args[2])
		{
			ft_putstr_fd("cd : string not in pwd: ", 2);
			ft_putstr_fd(tmp->args[0], 2);
			ft_putstr_fd("\n", 2);
		}
		else
			ft_putstr_fd("cd: too many arguments\n", 2);

	}
	if (str)
	{
		if (chdir(str) == -1)
		{
			update_exit_code(ft_itoa(errno));
			ft_putstr_fd("cd: ", 2);
			ft_putstr_fd(strerror(errno), 2);
			ft_putstr_fd("\n", 2);
		}
	free (str);
	set_env("PWD=", getcwd(NULL, 0));
	set_env("OLDPWD=", OLDPWD);
	free (OLDPWD);
	}
}
