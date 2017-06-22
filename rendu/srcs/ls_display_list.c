/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_display_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/13 14:11:52 by bduron            #+#    #+#             */
/*   Updated: 2017/06/22 18:53:48 by bduron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

#define MAX(a, b) (a > b ? a : b)
#define MAX_LS(a, b) a = MAX(a, b)

void	init_fmt(t_fmt *fmt, t_list *ents, int opts)
{
	struct stat	stat;
	char		*name;
	t_data		*data;

	ft_bzero(fmt, sizeof(*fmt));
	while (ents)
	{
		data = (t_data *)ents->content;
		name = (data->dirent) ? data->dirent->d_name : data->path;
		if (!(opts & FT_DOT) && *name == '.')
		{
			ents = ents->next;
			continue;
		}
		else
			fmt->total += ((t_data *)ents->content)->stat.st_blocks;
		stat = ((t_data *)ents->content)->stat;
		MAX_LS(fmt->size, (int)ft_nblen(stat.st_size, 10));
		MAX_LS(fmt->link, (int)ft_nblen(stat.st_nlink, 10));
		MAX_LS(fmt->uid, (int)ft_strlen(getpwuid(stat.st_uid)->pw_name));
		MAX_LS(fmt->gid, (int)ft_strlen(getgrgid(stat.st_gid)->gr_name));
		ents = ents->next;
	}
}

void	print_link(t_data *data, struct stat file_stat)
{
	char	buf[1024];
	ssize_t	len;

	if (!((file_stat.st_mode & S_IFMT) == S_IFLNK))
		ft_printf("\n");
	if ((file_stat.st_mode & S_IFMT) == S_IFLNK)
	{
		if ((len = readlink(data->path, buf, sizeof(buf) - 1)) != -1)
			buf[len] = '\0';
		ft_printf(" -> %s\n", buf);
	}
}

void	print_date(struct stat file_stat)
{
	t_timestr *time;

	time = ft_timestr(file_stat.st_mtime);
	if (ft_time_isrecent(file_stat.st_mtime))
		ft_printf("%s %s %s:%s ", time->month,
				time->day, time->hour, time->minute);
	else
		ft_printf("%s %s %5s ", time->month, time->day, time->year);
	ft_timestr_del(time);
}

void	print_size(t_fmt fmt, struct stat file_stat)
{
	unsigned int min;
	unsigned int maj;

	if (S_ISCHR(file_stat.st_mode) || S_ISBLK(file_stat.st_mode))
	{
		min = minor(file_stat.st_rdev);
		maj = major(file_stat.st_rdev);
		ft_printf("%3d, %3d ", maj, min);
	}
	else
		ft_printf("%*ld ", fmt.size, (long)file_stat.st_size);
}

void	ls_display_list(t_data *data, t_fmt fmt)
{
	struct stat file_stat;

	if (lstat(data->path, &file_stat) < 0)
	{
		ft_printf("ls: %s: %s\n", data->path, strerror(errno));
		return ;
	}
	disp_mode(file_stat);
	ft_printf("%*d ", fmt.link + 1, (int)file_stat.st_nlink);
	ft_printf("%-*s  ", fmt.uid, getpwuid(file_stat.st_uid)->pw_name);
	ft_printf("%-*s  ", fmt.gid, getgrgid(file_stat.st_gid)->gr_name);
	print_size(fmt, file_stat);
	print_date(file_stat);
	ft_printf("%s", (data->dirent ? data->dirent->d_name : data->path));
	print_link(data, file_stat);
}
