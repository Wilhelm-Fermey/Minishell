/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wilhelmfermey <marvin@42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 10:16:44 by wilhelmfermey     #+#    #+#             */
/*   Updated: 2022/05/31 10:33:08 by wilhelmfermey    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <errno.h>
#include <sys/stat.h>

void	add_STDIN(int fdd)
{
	int		fd_t;
	char		buff;

	fd_t = open(".total_data", O_RDWR | O_CREAT | O_APPEND, 0644);
	while (read(fdd, &buff, 1) > 0)
		write (fd_t, &buff, 1);
	close (fd_t);
	close (fdd);

}

void	merge_files(char **input, int fdd)
{
	int		fd;
	int		fd_t;
	struct stat	info;
	char		*buff;
	int		i[2];

		
	fd_t = open(".total_data", O_RDWR | O_CREAT | O_TRUNC, 0644);
	close (fd_t);
	i[0] = 0;
	if (fdd != 0)
		add_STDIN(fdd);
	fd_t = open(".total_data", O_RDWR | O_CREAT | O_APPEND, 0644);
	while (input[i[0]])
	{
		if (input[i[0]][0] == '1')
		{	
			fd = open(input[i[0]] + 1, O_RDWR, 0644);
			fstat(fd, &info);
			i[1] = info.st_size;
			buff = malloc (i[1] + 1);
			if (!buff)
				printf("Error malloc\n");
			read(fd, buff, i[1]);
			write (fd_t, buff, i[1]);
			close (fd);
			free (buff);
		}
		i[0]++;
	}
	close (fd_t);
}

void	handle_all_out(char **out)
{
	int		fd;
	int		fd_t;
	struct stat	info;
	char		*buff;
	int		i[2];

		
	fd = open(".PIPE", O_RDWR);
	fstat(fd, &info);
	i[1] = info.st_size;
	buff = malloc (i[1] + 1);
	if (!buff)
		printf("Error malloc\n");
	read(fd, buff, i[1]);
	i[0] = 0;
	while (out[i[0]])
	{
		if (out[i[0]][0] == '1')
			fd_t = open(out[i[0]] + 1, O_RDWR | O_CREAT | O_TRUNC, 0644);
		else
			fd_t = open(out[i[0]] + 1, O_RDWR | O_CREAT | O_APPEND, 0644);
		write (fd_t, buff, i[1]);
		close (fd_t);
		i[0]++;
	}
	close (fd);
	free(buff);
}
