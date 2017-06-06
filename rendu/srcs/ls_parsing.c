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

void ls_usage(char opt)
{
	printf("ls: illegal option -- %c\n", opt);
	printf("usage: ls [-Ralrt] [file ...]\n");
	exit(1);
} 

//void clean_target(t_env *e)
//{
//	t_list *tmp;
//
//	struct stat file_stat;
//
//	tmp = e->target;		
//	while (tmp)
//	{
//		if (stat((char *)tmp->content, &file_stat) < 0)
//		{	
//			printf("ls: %s: %s\n", (char *)tmp->content, strerror(errno));	
//			free(tmp->content);
//			tmp->content = NULL;
//		}
//		tmp = tmp->next;	
//	}
//}





//void get_target(int argc, char **argv, int i, t_env *e)
//{
//	size_t ntarget;
//
//	ntarget = argc - i;
//	if (ntarget == 0)
//		e->target = ft_lstnew(".", 2);
//	else 
//	{
//		e->target = ft_lstnew(argv[i], sizeof(char) * strlen(argv[i]) + 1);
//		i++;
//		while (i < argc)
//		{	
//			ft_lstappend(&(e->target), 
//					ft_lstnew(argv[i], sizeof(char) * strlen(argv[i]) + 1));
//			i++;
//		}
//		clean_target(e);
//	}
//}




void get_files(char **argv, int opts, t_list *ents, t_list *dirs)
{
	t_data data;

	data.dirent = NULL;
//	printav(argv);
	while (*argv)
	{	
		if (stat(*argv, &data.stat) < 0)
		{
			printf("ls: %s: %s\n", *argv, strerror(errno));	
			argv++;
			continue ;
		}
		data.path = ft_strdup(*argv);
		if (S_ISDIR(data.stat.st_mode))  
			ft_lstadd(&dirs, ft_lstnew(&data, sizeof(data))); 		
		else
			ft_lstadd(&ents, ft_lstnew(&data, sizeof(data))); 		
		argv++;
	}	

	(void)opts;
	(void)dirs;
}

int get_opt(int argc, char **argv, int *opts)
{
	int i; 

	i = 1;
	while (i < argc && argv[i][0] == '-' && argv[i][1] != '\0')
	{
		if (strcmp(argv[i], "--") == 0)
		{
			i++;
			break;
		}
		while (*++argv[i] != '\0')
		{
			if (*argv[i] == 'l')
				*opts |= FT_LIST;	
			else if (*argv[i] == 'R')
				*opts |= FT_RECURSIVE;	
			else if (*argv[i] == 'a')
				*opts |= FT_DOT;	
			else if (*argv[i] == 'r')
				*opts |= FT_REVERSE;	
			else if (*argv[i] == 't')
				*opts |= FT_TSORT;	
			else 
				ls_usage(*argv[i]);	
		}	
		i++;
	}
	
	return (i);
}	

void printav(char **av)
{
	while (*av)
		printf("%s\n", *av++);
}

void ft_print_lst(t_list *head)
{
	while (head)
	{
		ft_printf("%s ", (char *)((t_data *)(head->content)->data).path);
		head = head->next;	
	}		
	ft_printf("\n");
}

static int cmp_av(void const *a, void const *b)
{	
	char const *pa = *(const char**)a;
	char const *pb = *(const char**)b;

	return (ft_strcmp(pa, pb)); 
}

int parse_ls(int argc, char **argv, t_list *ents, t_list *dirs)
{
	int opts;
	int nb_opts;

	opts = 0;
	nb_opts = get_opt(argc, argv, &opts);
	qsort(argv + nb_opts, argc - nb_opts, sizeof(char *), cmp_av);
				
	if (argc - nb_opts == 0)
		get_files((char *[2]){".", NULL}, opts, ents, dirs);		
	else 
		get_files(argv + nb_opts, opts, ents, dirs);		
	
	ft_print_lst(ents);
	ft_print_lst(dirs);

	(void)ents;
	(void)dirs;
	return (opts); 
}
