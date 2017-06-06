/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/29 19:18:26 by bduron            #+#    #+#             */
/*   Updated: 2017/05/31 14:57:59 by bduron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

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

//void list_files(char *path)
//{
//	DIR *dirp;
//	struct dirent *dp;
//	char fn[FILENAME_MAX];
//	size_t len; 
//
//	len = strlen(path);
//	strcpy(fn, path);
//	fn[len++] = '/';	
//	fn[len] = '\0';	
//		
//
//	if ((dirp = opendir(path)) == NULL)
//		printf("ls: %s: %s\n", path, strerror(errno));	
//
//	printf("\n===>%s \n", fn);
//	while ((dp = readdir(dirp)) != NULL)
//	{	
//		strncpy(fn + len, dp->d_name, FILENAME_MAX - len);
//		disp_file_info(fn);
//		if (dp->d_type & DT_DIR && dp->d_name[0] != '.')
//		{
//			list_files(fn);		
//		}
//	}
//	closedir(dirp);
//}

//void run_ls(t_env *e)
//{
//	t_list *tmp;
//	struct stat file_stat;
//
//	tmp = e->target;
//	while (tmp)	//
//	{
//		if (stat((char *)tmp->content, &file_stat) < 0)
//			printf("ls: %s: %s\n", (char *)tmp->content, strerror(errno));	
//		if (tmp->content != NULL && S_ISDIR(file_stat.st_mode))
//			list_files((char *)tmp->content);
//		else 
//			disp_file_info((char *)tmp->content);
//		tmp = tmp->next;
//	}
//
//}
