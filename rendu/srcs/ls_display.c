/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/29 19:18:26 by bduron            #+#    #+#             */
/*   Updated: 2017/06/12 17:47:35 by bduron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

#define MAX(a, b) (a > b ? a : b)
#define MAX_LS(a, b) a = MAX(a, b)

void init_fmt(t_fmt *fmt, t_list *ents, int opts)
{	
	struct stat stat;
	char *name;
	t_data *data;

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
//	printf("Final: \nsize(%d), link(%d), uid(%d), gid(%d)\n", fmt->size, fmt->link, fmt->uid, fmt->gid);
}

//void init_fmt(t_fmt *fmt, t_list *ents)
//{
//	off_t max_size;
//	off_t cur_size;
//	nlink_t max_link;
//	nlink_t cur_link;
//	nlink_t max_usr;
//	nlink_t cur_link;
//
//	fmt->total = 0;
//	max_size = 0;
//	max_link = 0;
//	while (ents)
//	{
//		fmt->total += ((t_data *)ents->content)->stat.st_blocks;
//		cur_size = ((t_data *)ents->content)->stat.st_size;
//		max_size = (cur_size > max_size) ? cur_size : max_size;	
//		cur_link = ((t_data *)ents->content)->stat.st_nlink;
//		max_link = (cur_link > max_link) ? cur_link : max_link;	
//		ents = ents->next;
//	}
//	fmt->size_pad = ft_nblen((long)max_size, 10);
//	fmt->nlink_pad = ft_nblen((long)max_link, 10);
//}

char *disp_chmod(struct stat file_stat)
{
	char *chmod;
	int type;

	chmod = (char *)malloc(sizeof(char) * 11);
	
	type = file_stat.st_mode & S_IFMT; 

    if (type == S_IFBLK)  
   		chmod[0] = 'b';
    if (type == S_IFCHR)  
   		chmod[0] = 'c';
    if (type == S_IFDIR)  
   		chmod[0] = 'd';
    if (type == S_IFIFO)  
   		chmod[0] = 'p';
    if (type == S_IFLNK)  
   		chmod[0] = 'l';
    if (type == S_IFREG)  
   		chmod[0] = '-';
    if (type == S_IFSOCK)  
   		chmod[0] = 's';

//	chmod[0] = (S_ISDIR(file_stat.st_mode)) ? 'd' : '-'; // If - else for this one
	chmod[1] = (S_IRUSR & file_stat.st_mode) ? 'r' : '-';
	chmod[2] = (S_IWUSR & file_stat.st_mode) ? 'w' : '-';
	chmod[3] = (S_IXUSR & file_stat.st_mode) ? 'x' : '-';
	chmod[4] = (S_IRGRP & file_stat.st_mode) ? 'r' : '-';
	chmod[5] = (S_IWGRP & file_stat.st_mode) ? 'w' : '-';
	chmod[6] = (S_IXGRP & file_stat.st_mode) ? 'x' : '-';
	chmod[7] = (S_IROTH & file_stat.st_mode) ? 'r' : '-';
	chmod[8] = (S_IWOTH & file_stat.st_mode) ? 'w' : '-';
	chmod[9] = (S_IXOTH & file_stat.st_mode) ? 'x' : '-';
	chmod[10] = '\0';

	return (chmod);
}

void ls_display_list(t_data *data, t_fmt fmt)
{
	struct stat file_stat;
	char *date;
	char buf[1024];
	ssize_t len;

	if (lstat(data->path, &file_stat) < 0)
	{
		printf("ls: %s: %s\n", data->path, strerror(errno));	
		return ;			
	}

	date = ctime(&file_stat.st_mtime);
	while (*date++ != ' ')
	   ;	
	date[ft_strlen(date) - 9] = '\0';
	printf("%s ", disp_chmod(file_stat));
	printf("%*d ", fmt.link + 1, (int)file_stat.st_nlink);
	printf("%-*s  ", fmt.uid, getpwuid(file_stat.st_uid)->pw_name);
	printf("%-*s  ", fmt.gid, getgrgid(file_stat.st_gid)->gr_name);
	printf("%*ld ", fmt.size, (long)file_stat.st_size);
	printf("%s ", date);
	if (data->dirent)
		printf("%s", data->dirent->d_name); // FLUSH
	else
		printf("%s", data->path); // FLUSH
	if (!((file_stat.st_mode & S_IFMT) == S_IFLNK))
	   printf("\n");	
	
	if ((file_stat.st_mode & S_IFMT) == S_IFLNK) 
	{
		if ((len = readlink(data->path, buf, sizeof(buf)-1)) != -1)
    		buf[len] = '\0';
		printf(" -> %s\n", buf);
	}

}

void ls_display_flush(t_list *ents, t_list *nextdirs, int opts)
{
	t_data			*data;
	t_fmt			fmt;
	
	init_fmt(&fmt, ents, opts);

	while (ents)
	{
		data = ents->content;
		
		if (*(data->path) == '.' && !(opts & FT_DOT))
		{
			ents = ents->next;
			continue;
		}
		if (opts & FT_LIST)
			ls_display_list(data, fmt);	
		else 										//FLUSH
			printf("%s\n", data->path);	//FLUSH
		ents = ents->next;
	}
	if (nextdirs)	
   		printf("\n");
}

void ls_display(t_list *ents, char *dirpath, int opts)
{
	t_data			*data;
	static int		firstdir;	
	t_fmt			fmt;
	int				type; // munki 644

	if (firstdir++ || opts & FT_DIRNAME)
  		printf("%s:\n", dirpath);

	init_fmt(&fmt, ents, opts);

  	if (opts & FT_LIST)
		printf("total %ld\n", fmt.total); /////////// REPRENDRE LA

	while (ents)
	{
		data = ents->content;
	 	type = data->stat.st_mode & S_IFMT; 						// munki 644
		if ((type & S_IFDIR))		//
			printf("FORBIDDEN\n"); 									//
		
		if (*(data->dirent->d_name) == '.' && !(opts & FT_DOT))
		{
			ents = ents->next;
			continue;
		}
		if (opts & FT_LIST)
			ls_display_list(data, fmt);	
		else
			printf("%s\n", data->dirent->d_name);
		ents = ents->next;
	}
}
