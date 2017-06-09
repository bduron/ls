/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/29 19:18:26 by bduron            #+#    #+#             */
/*   Updated: 2017/06/08 18:16:47 by bduron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"


void init_fmt(t_fmt *fmt, t_list *ents)
{
	off_t max_size;
	off_t cur_size;

	fmt->total = 0;
	max_size = 0;
	while (ents)
	{
		cur_size = ((t_data *)ents->content)->stat.st_size;
		fmt->total += cur_size;
		max_size = (cur_size > max_size) ? cur_size : max_size;	
		ents = ents->next;
	}
	fmt->pad = ft_nblen((long)max_size, 10);
}

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

void ls_display_list(t_data *data)
{
	struct stat file_stat;

	if (stat(data->path, &file_stat) < 0)
	{
		printf("ls: %s: %s\n", data->path, strerror(errno));	
		return ;			
	}

	printf("%s ", disp_chmod(file_stat));
	printf("%d ", (int)file_stat.st_nlink);
	printf("%s ", getpwuid(file_stat.st_uid)->pw_name);
	printf("%s ", getgrgid(file_stat.st_gid)->gr_name);
	printf("%ld ", (long)file_stat.st_size);
	//printf("%s\n", strrchr(path, '/') + 1);
	printf("%s\n", data->path);


	//	 Groupe: staff
	//	 Taille: 2142 octets
	//	 Date de derniere modification: Sep 17 23:42


}

void ls_display(t_list *ents, char *dirpath, int opts)
{
	t_data			*data;
	static int		firstdir;	
	t_fmt			fmt;
	
	init_fmt(&fmt, ents);

	if (firstdir++ || opts & FT_DIRNAME)
  		printf("%s:\n", dirpath);

  	printf("total %ld\n", fmt.total); /////////// REPRENDRE LA

	while (ents)
	{
		data = ents->content;
		
		if (*(data->dirent->d_name) == '.' && !(opts & FT_DOT))
		{
			ents = ents->next;
			continue;
		}
		if (opts & FT_LIST)
			ls_display_list(data);	
		else 
			printf("%s\n", data->dirent->d_name);
		ents = ents->next;
	}
	printf("\n");

}
