/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/29 19:18:26 by bduron            #+#    #+#             */
/*   Updated: 2017/06/08 09:44:55 by bduron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

void ls_usage(char opt)
{
	printf("ls: illegal option -- %c\n", opt);
	printf("usage: ls [-Ralrt] [file ...]\n");
	exit(1);
} 

void get_files(char **argv, int opts, t_list **ents, t_list **dirs)
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
		//printf("Copied data: %s\n", data.path);// 
		if (S_ISDIR(data.stat.st_mode))  
			ft_lstaddback(dirs, ft_lstnew(&data, sizeof(data))); 		
		else
			ft_lstaddback(ents, ft_lstnew(&data, sizeof(data))); 		
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
		if (ft_strcmp(argv[i], "--") == 0)
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

int parse_ls(int argc, char **argv, t_list **ents, t_list **dirs)
{
	int opts;
	int nb_opts;

	opts = 0;
	nb_opts = get_opt(argc, argv, &opts);
	qsort(argv + nb_opts, argc - nb_opts, sizeof(char *), cmp_av); //FT_QSORT
				
	if (argc - nb_opts > 1)
		opts |= FT_DIRNAME;

	if (argc - nb_opts == 0)
		get_files((char *[2]){".", NULL}, opts, ents, dirs);		
	else 
		get_files(argv + nb_opts, opts, ents, dirs);		
	
//	ft_print_lst(*ents);
//	ft_print_lst(*dirs);

	(void)ents;
	(void)dirs;
	return (opts); 
}
