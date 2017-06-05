/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/29 19:18:26 by bduron            #+#    #+#             */
/*   Updated: 2017/05/31 14:57:59 by bduron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LS_H
# define LS_H

# include <dirent.h>
# include <stdio.h>
# include <string.h>
# include <errno.h>
# include <sys/stat.h>
# include <stdlib.h>
# include <sys/types.h>
# include <pwd.h>
# include <uuid/uuid.h>
# include <grp.h>
# include <unistd.h>
# include "libft.h"

# define FT_NONE		(1 << 0) // -f
# define FT_DEFAULT		(1 << 1) // nothing, lexicographycally sorted
# define FT_HIDDEN		(1 << 2) // -a
# define FT_FOLLOWLNK	(1 << 3) // ? 
# define FT_TSORT		(1 << 4) // -t
# define FT_REVERSE		(1 << 5) // -r
# define FT_RECURSIVE	(1 << 6) // -R
# define FT_LIST		(1 << 7) // -l

# define ERR_WRONGOPT	-1


typedef struct	s_env
{
//	t_list		*files;
	int			opts;
	int			nopts;
	t_list 		*target;

		

}				t_env;


void env_init(t_env *e);
void del_target(void *content, size_t content_size);
void clean_target(t_env *e);
void get_target(int argc, char **argv, int i, t_env *e);
int get_opt(int argc, char **argv, t_env *e);
void ls_usage(char opt);
void run_ls(t_env *e);
void list_files(char *path);
void disp_file_info(char *path);
char *disp_chmod(struct stat file_stat);

#endif
