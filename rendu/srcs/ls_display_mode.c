/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_display_mode.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/22 18:53:04 by bduron            #+#    #+#             */
/*   Updated: 2017/06/22 18:53:31 by bduron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

void	disp_mode_sst(struct stat file_stat)
{
	ft_putchar((S_IRUSR & file_stat.st_mode) ? 'r' : '-');
	ft_putchar((S_IWUSR & file_stat.st_mode) ? 'w' : '-');
	if (file_stat.st_mode & S_ISUID)
		ft_putchar((S_IXUSR & file_stat.st_mode) ? 's' : 'S');
	else
		ft_putchar((S_IXUSR & file_stat.st_mode) ? 'x' : '-');
	ft_putchar((S_IRGRP & file_stat.st_mode) ? 'r' : '-');
	ft_putchar((S_IWGRP & file_stat.st_mode) ? 'w' : '-');
	if (file_stat.st_mode & S_ISGID)
		ft_putchar((S_IXGRP & file_stat.st_mode) ? 's' : 'S');
	else
		ft_putchar((S_IXGRP & file_stat.st_mode) ? 'x' : '-');
	ft_putchar((S_IROTH & file_stat.st_mode) ? 'r' : '-');
	ft_putchar((S_IWOTH & file_stat.st_mode) ? 'w' : '-');
	if (file_stat.st_mode & S_ISVTX)
		ft_putchar((S_IXOTH & file_stat.st_mode) ? 't' : 'T');
	else
		ft_putchar((S_IXOTH & file_stat.st_mode) ? 'x' : '-');
}

void	disp_mode(struct stat file_stat)
{
	int		type;
	char	c;

	type = file_stat.st_mode & S_IFMT;
	c = (type == S_IFBLK) ? 'b' : '-';
	c = (type == S_IFCHR) ? 'c' : c;
	c = (type == S_IFDIR) ? 'd' : c;
	c = (type == S_IFIFO) ? 'p' : c;
	c = (type == S_IFLNK) ? 'l' : c;
	c = (type == S_IFSOCK) ? 's' : c;
	ft_putchar(c);
	disp_mode_sst(file_stat);
}
