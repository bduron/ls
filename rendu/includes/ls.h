/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/29 19:18:26 by bduron            #+#    #+#             */
/*   Updated: 2017/06/22 18:50:24 by bduron           ###   ########.fr       */
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
#include <time.h>
#include <unistd.h>
# include "libft.h"

# define FT_LIST		(1 << 1)
# define FT_RECURSIVE	(1 << 2)
# define FT_DOT			(1 << 3)
# define FT_REVERSE		(1 << 4)
# define FT_TSORT		(1 << 5)

# define FT_DIRNAME		(1 << 6)

# define ERR_WRONGOPT	-1

typedef struct		s_data
{
	struct stat		stat;
	struct dirent	*dirent;
	char			*path;
}					t_data;

typedef struct		s_fmt
{
	long			total;
	int				size;
	int				link;
	int				uid;
	int				gid;
}					t_fmt;

int		parse_ls(int argc, char **argv, t_list **ents, t_list **dirs);
int		get_opt(int argc, char **argv, int *opts);
void	get_files(char **argv, int opts, t_list **ents, t_list **dirs);
int		get_ents(char *curdir, t_list **ents, t_list **nextdirs, int opts);

void run_ls(t_list **ents, t_list **dirs, int opts);
void ls_sort(t_list **ents, int opts);

void ls_display(t_list *ents, char *dirpath, int opts);
void ls_display_list(t_data *data, t_fmt fmt);
void disp_mode(struct stat file_stat);
void init_fmt(t_fmt *fmt, t_list *ents, int opts);
void ls_display_flush(t_list *ents, t_list *nextdirs, int opts);
void print_link(t_data *data, struct stat file_stat);

int cmp_av(void const *a, void const *b);
int ls_cmpmtime(t_list *a, t_list *b);
int ls_cmpname(t_list *a, t_list *b);
int ls_cmpnamedir(t_list *a, t_list *b);

void ls_usage(char opt);

void ls_ents_free(void *p, size_t size);
void ls_dirs_free(void *p, size_t size);

/* Debbug functions */
void printav(char **av);
void ft_print_lst(t_list *head);
void ft_print_dirs(t_list *head);

#endif
