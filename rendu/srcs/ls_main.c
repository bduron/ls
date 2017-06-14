/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/29 19:18:26 by bduron            #+#    #+#             */
/*   Updated: 2017/06/14 12:43:28 by bduron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

//while (dirs != NULL) 
//	pop currentdir from dirs 
//	get currentdir entries: ents [file, file, dir, file, ...]
//	if -R		
//		+ get nextdirs from currentdir: nextdirs [dir, dir, dir, ...]				
//		sort nextdirs
//		dirs = merge nextdirs + dirs 	
//	compute ents (sort, ...) 
//	display ents 
//	deletes ents 		
//	go to the next dir in dirs 



char *construct_path(const char *parent, const char *path)
{
	char *tmp;
	char *fullpath;

	tmp = ft_strjoin(parent, "/");		
	fullpath = ft_strjoin(tmp, path);
	free(tmp);
	return (fullpath);
}

int get_ents(t_data *curdir, t_list **ents, t_list **nextdirs, int opts)
{
	DIR				*dirp;
	struct dirent	*dp;
	t_data			data;

	if ((dirp = opendir(curdir->path)) == NULL)
	{
		ft_printf("%s:\nls: %s: %s\n\n", curdir->path, ft_strrchr(curdir->path, '/') + 1, strerror(errno));	
		return (1);
	}

	while ((dp = readdir(dirp)) != NULL)
	{
		data.path = construct_path(curdir->path, dp->d_name);
		if (lstat(data.path, &data.stat) < 0)
		{
			ft_printf("ls: %s: %s\n", data.path, strerror(errno));	
			return (1) ;			
		}	// protect
		data.dirent = malloc(sizeof(*dp) + 1);
		ft_memcpy(data.dirent, dp, sizeof(*dp));
		
		ft_lstadd(ents, ft_lstnew(&data, sizeof(data)));
		if ((S_ISDIR(data.stat.st_mode) && !(opts & FT_DOT) 
				&& dp->d_name[0] == '.'))
			continue ;
		if (S_ISDIR(data.stat.st_mode) && ft_strcmp(dp->d_name, ".") 
				&& ft_strcmp(dp->d_name, ".."))
			ft_lstadd(nextdirs, ft_lstnew(&data, sizeof(data)));
	}
	ft_lstsort(nextdirs, ls_cmpname);
	(void)closedir(dirp);
	return (0);
}


void ls_sort(t_list **ents, int opts)
{
	int (*sort_func)();

	sort_func = &ls_cmpname;
	
	if (opts & FT_TSORT)	
		sort_func = &ls_cmpmtime; // CODE cmptime

	ft_lstsort(ents, sort_func);

	if (opts & FT_REVERSE)
		ft_list_reverse(ents);
}

void run_ls(t_list **ents, t_list **dirs, int opts)
{
	t_data *data; 
	t_list *nextdirs;
	t_list **curdir; 

	nextdirs = NULL;
	curdir = dirs;
	while (*curdir)
	{	
		data = (*curdir)->content;
		//ft_printf("Entering %s\n", data->path); // DEBUG
		if (get_ents(data, ents, &nextdirs, opts))
		{
			*curdir = (*curdir)->next;	
			*ents = NULL; // DELETE free 
			nextdirs = NULL; // OK list integré a dirs
		   continue ;
		}	

		if (opts & FT_RECURSIVE)
			ft_lstinsert(*curdir, nextdirs);

		ls_sort(ents, opts);
		ls_display(*ents, data->path, opts);
		if ((*curdir)->next)
   			ft_printf("\n");
		// if last dir to visit trigger LASTDIR opt -> control last -R \n

		*curdir = (*curdir)->next;	
		ft_lstdel(ents, ls_ents_free); 
		//*ents = NULL; // DELETE
		nextdirs = NULL; // OK
	}
	//ft_lstdel(ents);



	(void)opts;
	(void)ents;
	//char *path = ((t_data *)(*dirs)->content)->path;
}



























//char *disp_chmod(struct stat file_stat)
//{
//	char *chmod;
//
//	chmod = (char *)malloc(sizeof(char) * 11);
//
//	chmod[0] = (S_ISDIR(file_stat.st_mode)) ? 'd' : '-'; // If - else for this one
//	chmod[1] = (S_IRUSR & file_stat.st_mode) ? 'r' : '-';
//	chmod[2] = (S_IWUSR & file_stat.st_mode) ? 'w' : '-';
//	chmod[3] = (S_IXUSR & file_stat.st_mode) ? 'x' : '-';
//	chmod[4] = (S_IRGRP & file_stat.st_mode) ? 'r' : '-';
//	chmod[5] = (S_IWGRP & file_stat.st_mode) ? 'w' : '-';
//	chmod[6] = (S_IXGRP & file_stat.st_mode) ? 'x' : '-';
//	chmod[7] = (S_IROTH & file_stat.st_mode) ? 'r' : '-';
//	chmod[8] = (S_IWOTH & file_stat.st_mode) ? 'w' : '-';
//	chmod[9] = (S_IXOTH & file_stat.st_mode) ? 'x' : '-';
//	chmod[10] = '\0';
//
//	return (chmod);
//}

//void disp_file_info(char *path)
//{
//	struct stat file_stat;
//
//	if (stat(path, &file_stat) < 0)
//		ft_printf("ls: %s: %s\n", path, strerror(errno));	
//
//
//	ft_printf("%s ", disp_chmod(file_stat));
//	ft_printf("%d ", (int)file_stat.st_nlink);
//	ft_printf("%s ", getpwuid(file_stat.st_uid)->pw_name);
//	ft_printf("%s ", getgrgid(file_stat.st_gid)->gr_name);
//	ft_printf("%d ", (int)file_stat.st_size);
//	//ft_printf("%s\n", strrchr(path, '/') + 1);
//	ft_printf("%s\n", path);
//
//
//	//	 Groupe: staff
//	//	 Taille: 2142 octets
//	//	 Date de derniere modification: Sep 17 23:42
//
//
//}
