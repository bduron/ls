/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/29 19:18:26 by bduron            #+#    #+#             */
/*   Updated: 2017/06/07 13:24:06 by bduron           ###   ########.fr       */
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

# define FT_LIST		(1 << 1) // -l
# define FT_RECURSIVE	(1 << 2) // -R
# define FT_DOT			(1 << 3) // -a
# define FT_REVERSE		(1 << 4) // -r
# define FT_TSORT		(1 << 5) // -t

# define ERR_WRONGOPT	-1

typedef struct		s_data
{
	struct stat		stat;
	struct dirent	*dirent;
	char			*path;
}				t_data;


int		parse_ls(int argc, char **argv, t_list **ents, t_list **dirs);
int		get_opt(int argc, char **argv, int *opts);
void	get_files(char **argv, int opts, t_list **ents, t_list **dirs);

void run_ls(t_list **ents, t_list **dirs, int opts);

int cmp_av(void const *a, void const *b);

void ls_usage(char opt);


/* Debbug functions */
void printav(char **av);
void ft_print_lst(t_list *head);

/* LIBFT */
void ft_lstinsert(t_list *dst, t_list *src);

//void run_ls(t_env *e);
//void list_files(char *path);
//void disp_file_info(char *path);
//char *disp_chmod(struct stat file_stat);

#endif
