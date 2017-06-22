/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/29 19:18:26 by bduron            #+#    #+#             */
/*   Updated: 2017/06/16 20:47:43 by bduron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

char *construct_path(const char *parent, const char *path)
{
	char *tmp;
	char *fullpath;

	tmp = ft_strjoin(parent, "/");		
	fullpath = ft_strjoin(tmp, path);
	free(tmp);
	return (fullpath);
}

int get_ents(char *curdir, t_list **ents, t_list **nextdirs, int opts)
{
	DIR				*dirp;
	struct dirent	*dp;
	t_data			data;
	char			*errname;

	if ((dirp = opendir(curdir)) == NULL)
	{ 
		if ((errname = ft_strrchr(curdir, '/')))
			ft_printf("%s:\nls: %s: %s\n\n", curdir, errname + 1, strerror(errno));	
		else 
			ft_printf("%s:\nls: %s: %s\n\n", curdir, curdir, strerror(errno));	
		return (1);
	}

	while ((dp = readdir(dirp)) != NULL)
	{
		data.path = construct_path(curdir, dp->d_name);
		if (lstat(data.path, &data.stat) < 0)
		{
			ft_printf("ls: %s: %s\n", dp->d_name, strerror(errno));	
			free(data.path);
			continue ;
		}
		data.dirent = malloc(sizeof(*dp) + 1);
		ft_memcpy(data.dirent, dp, sizeof(*dp));
		
		ft_lstadd(ents, ft_lstnew(&data, sizeof(data)));
		if ((S_ISDIR(data.stat.st_mode) && !(opts & FT_DOT) 
				&& dp->d_name[0] == '.'))
			continue ;
		if (S_ISDIR(data.stat.st_mode) && ft_strcmp(dp->d_name, ".") 
				&& ft_strcmp(dp->d_name, "..") && (opts & FT_RECURSIVE))
		{	
			//data.path = ft_strdup(data.path); // improve this 
			ft_lstadd(nextdirs, ft_lstnew(data.path, sizeof(char) * ft_strlen(data.path) + 1));
		}
	}
	//ft_print_dirs(*nextdirs); /// DEBUG
	ft_lstsort(nextdirs, ls_cmpnamedir);
	if (opts & FT_REVERSE)
		ft_list_reverse(nextdirs);
	//ft_print_dirs(*nextdirs); /// DEBUG
	(void)closedir(dirp);
	return (0);
}


void ls_sort(t_list **ents, int opts)
{
	int (*sort_func)();

	sort_func = &ls_cmpname;
	
	if (opts & FT_TSORT)	
		sort_func = &ls_cmpmtime; 

	ft_lstsort(ents, sort_func);

	if (opts & FT_REVERSE)
		ft_list_reverse(ents);
}

void run_ls(t_list **ents, t_list **dirs, int opts)
{
	char *dirpath; 
	t_list *nextdirs;
	t_list *curdir; 

	nextdirs = NULL;
	curdir = *dirs;
	while (curdir)
	{	
		dirpath = curdir->content;
		//ft_printf("Entering %s\n", data->path); // DEBUG
		if (get_ents(dirpath, ents, &nextdirs, opts)) 
		{
			curdir = curdir->next;	
			ft_lstdel(ents, ls_ents_free); 
			//*ents = NULL; // DELETE free 
			nextdirs = NULL; // OK list integré a dirs
		   continue ;
		}	

		if (opts & FT_RECURSIVE)
		{
			//ft_printf("-------------------------\n");
			//ft_printf("[%s]\n", data->path);
			//ft_printf("Dirs before insert : ");
			//ft_print_lst(*dirs);
			ft_lstinsert(curdir, nextdirs);
			//ft_printf("Dirs after insert : ");
			//ft_print_lst(*dirs);
			//ft_printf("\n");
	
		}

		ls_sort(ents, opts); 
		ls_display(*ents, dirpath, opts);
		if (curdir->next)
   			ft_printf("\n");
		// if last dir to visit trigger LASTDIR opt -> control last -R \n

		curdir = curdir->next;	
		ft_lstdel(ents, ls_ents_free); 
		*ents = NULL; // DELETE
		nextdirs = NULL; // OK
	}
	


	(void)opts;
	(void)ents;
	//char *path = ((t_data *)(*dirs)->content)->path;
}




