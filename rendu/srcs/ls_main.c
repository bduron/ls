/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/29 19:18:26 by bduron            #+#    #+#             */
/*   Updated: 2017/06/08 12:47:47 by bduron           ###   ########.fr       */
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


void ls_display(t_list *ents, char *dirpath, int opts)
{
	t_data *data;	
	// filter
		// .dot dirs 
	// sort
		// classic
		// time
		// reverse
	// display	
		// classic 
		// list
		
	printf("\n%s:\n", dirpath);
	while (ents)
	{
		data = ents->content;
		
		if (*(data->dirent->d_name) == '.' && !(opts & FT_DOT))
		{
			ents = ents->next;
			continue;
		}

		printf("%s\n", data->dirent->d_name);
	
		ents = ents->next;
	}
}

char *construct_path(const char *parent, const char *path)
{
	char *tmp;
	char *fullpath;

	tmp = ft_strjoin(parent, "/");		
	fullpath = ft_strjoin(tmp, path);
	free(tmp);
	return (fullpath);
}

void get_ents(t_data *curdir, t_list **ents, t_list **nextdirs)
{
	DIR				*dirp;
	struct dirent	*dp;
	t_data			data;

	if ((dirp = opendir(curdir->path)) == NULL)
		exit(1);

	while ((dp = readdir(dirp)) != NULL)
	{
		data.path = construct_path(curdir->path, dp->d_name);
		stat(data.path, &data.stat); // protect
		data.dirent = malloc(sizeof(*dp) + 1);
		ft_memcpy(data.dirent, dp, sizeof(*dp));
		
		ft_lstadd(ents, ft_lstnew(&data, sizeof(data)));
		if (S_ISDIR(data.stat.st_mode) && ft_strcmp(dp->d_name, ".") 
				&& ft_strcmp(dp->d_name, ".."))
//			if ((opts & FT_DOT))
//				ft_lstadd(nextdirs, ft_lstnew(&data, sizeof(data)));
			// dirs list content should only be data.path ? 
	}
	ft_lstsort(nextdirs, ls_cmpname);
	//SORT NEXTDIR 

	(void)closedir(dirp);
}

// CMP function

void ls_filter(t_list **dirs, int opts)
{
	if (!(opts & FT_DOT))	
		ft_list_remove_if(dirs, void *data_ref, int (*cmp)())


}

void ls_sort(t_list **ents, int opts)
{
	int (*sort_func)();

	sort_func = &ls_cmpname;
	
//	if (opts & FT_TSORT)	
//		sort_func = &ls_cmptime; // CODE cmptime

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
		//printf("Entering %s\n", data->path); // DEBUG
		get_ents(data, ents, &nextdirs); // get ents + nextdirs + sort 	 
		

		if (opts & FT_RECURSIVE)
			ft_lstinsert(*curdir, nextdirs);

		ls_sort(ents, opts);
		ls_display(*ents, data->path, opts);

		
		//printf("\nEntries: "); // DEBUG
		//ft_print_lst(*ents);
		//printf("Dirs: "); // DEBUG
		//ft_print_lst(nextdirs);
		//printf("\n"); // DEBUG


		*curdir = (*curdir)->next;	
		*ents = NULL; // DELETE
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
//		printf("ls: %s: %s\n", path, strerror(errno));	
//
//
//	printf("%s ", disp_chmod(file_stat));
//	printf("%d ", (int)file_stat.st_nlink);
//	printf("%s ", getpwuid(file_stat.st_uid)->pw_name);
//	printf("%s ", getgrgid(file_stat.st_gid)->gr_name);
//	printf("%d ", (int)file_stat.st_size);
//	//printf("%s\n", strrchr(path, '/') + 1);
//	printf("%s\n", path);
//
//
//	//	 Groupe: staff
//	//	 Taille: 2142 octets
//	//	 Date de derniere modification: Sep 17 23:42
//
//
//}
