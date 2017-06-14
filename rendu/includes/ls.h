/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/29 19:18:26 by bduron            #+#    #+#             */
/*   Updated: 2017/06/14 12:46:42 by bduron           ###   ########.fr       */
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
//# include <uuid/uuid.h>
# include <grp.h>
# include <unistd.h>
#include <time.h>
#include <unistd.h>
# include "libft.h"

# define FT_LIST		(1 << 1) // -l
# define FT_RECURSIVE	(1 << 2) // -R
# define FT_DOT			(1 << 3) // -a
# define FT_REVERSE		(1 << 4) // -r
# define FT_TSORT		(1 << 5) // -t

# define FT_DIRNAME		(1 << 6) // display dir name when argv_files > 2 

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

/////////// TIME //////////////
typedef struct s_timestr
{
	char *weekday;
	char *month;
	char *day;
	char *hour;
	char *minute;
	char *second;
	char *year;
}				t_timestr;

int		parse_ls(int argc, char **argv, t_list **ents, t_list **dirs);
int		get_opt(int argc, char **argv, int *opts);
void	get_files(char **argv, int opts, t_list **ents, t_list **dirs);
int		get_ents(t_data *curdir, t_list **ents, t_list **nextdirs, int opts);

void run_ls(t_list **ents, t_list **dirs, int opts);
void ls_sort(t_list **ents, int opts);

void ls_display(t_list *ents, char *dirpath, int opts);
void ls_display_list(t_data *data, t_fmt fmt);
void disp_chmod(struct stat file_stat);
void init_fmt(t_fmt *fmt, t_list *ents, int opts);
void ls_display_flush(t_list *ents, t_list *nextdirs, int opts);
void print_link(t_data *data, struct stat file_stat);

int cmp_av(void const *a, void const *b);
int ls_cmpmtime(t_list *a, t_list *b);
int ls_cmpname(t_list *a, t_list *b);

void ls_usage(char opt);


void ls_ents_free(void *p, size_t size);

/* Debbug functions */
void printav(char **av);
void ft_print_lst(t_list *head);

/* LIBFT */
t_timestr *ft_timestr(time_t timestamp);
void ft_timestr_del(t_timestr *time);
int		ft_time_isrecent(time_t event);

int ft_nblen(long n, int base);

void ft_lstinsert(t_list *dst, t_list *src);
void	ft_list_reverse(t_list **begin_list);
void	ft_list_remove_if(t_list **begin_list, void *data_ref, int (*cmp)());

void ft_lstsort(t_list **headref, int (*lstcmp)());
t_list *sortedmerge(t_list *a, t_list *b, int (*lstcmp)());
void ft_lstsplit(t_list *source, t_list **front, t_list** back);

//void disp_file_info(char *path);
//char *disp_chmod(struct stat file_stat);

#endif
