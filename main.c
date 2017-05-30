/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/29 19:18:26 by bduron            #+#    #+#             */
/*   Updated: 2017/05/29 20:49:54 by bduron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <sys/types.h>
#include <pwd.h>
//#include <uuid/uuid.h>
#include <grp.h>

char *disp_chmod(struct stat file_stat)
{
	char *chmod;

	chmod = (char *)malloc(sizeof(char) * 11);

	chmod[0] = (S_ISDIR(file_stat.st_mode)) ? 'd' : '-'; // If - else for this one
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

void disp_file_info(char *path)
{
	struct stat file_stat;
	
	if (stat(path, &file_stat) < 0)
	   printf("ls: %s: %s\n", path, strerror(errno));	


	printf("%s ", disp_chmod(file_stat));
	printf("%d ", (int)file_stat.st_nlink);
	printf("%s ", getpwuid(file_stat.st_uid)->pw_name);
	printf("%s ", getgrgid(file_stat.st_gid)->gr_name);
	printf("%d ", (int)file_stat.st_size);
	printf("%s\n", path);


//	 Groupe: staff
//	 Taille: 2142 octets
//	 Date de derniere modification: Sep 17 23:42


}

void list_files(char *path)
{
	DIR *dirp;
	struct dirent *dp;

	if ((dirp = opendir(path)) == NULL)
	   printf("ls: %s: %s\n", path, strerror(errno));	
	
	while ((dp = readdir(dirp)) != NULL)
	{	
//		printf("\n%s\n", dp->d_name);
		disp_file_info(dp->d_name);
//		if (S_ISDIR(file_stat.st_mode))
//		{
//			printf("\nEntering %s\n", dp->d_name);
//			list_files(dp->d_name);		
//		}
	}

	closedir(dirp);
}


int main(int argc, char **argv)
{

	list_files(argv[1]);


	return (0);
}


/*
	Get flags 
	initialize ls_struct
	for each folder 
		save files infos in linked list (dirent + stat)
		compute list (padding, sort, dates...)
		display files + formatting 
		free list 

	free struct 
*/


