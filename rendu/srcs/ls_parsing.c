/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/29 19:18:26 by bduron            #+#    #+#             */
/*   Updated: 2017/06/22 19:43:44 by bduron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

void	ls_usage(char opt)
{
	ft_printf("ls: illegal option -- %c\n", opt);
	ft_printf("usage: ls [-Ralrt] [file ...]\n");
	exit(1);
}

void	get_files(char **argv, int opts, t_list **ents, t_list **dirs)
{
	t_data data;

	data.dirent = NULL;
	while (*argv)
	{
		if (lstat(*argv, &data.stat) < 0)
		{
			ft_printf("ls: %s: %s\n", *argv, strerror(errno));
			argv++;
			continue ;
		}
		if (S_ISDIR(data.stat.st_mode))
			ft_lstaddback(dirs, ft_lstnew(*argv, ft_strlen(*argv) + 1));
		else
		{
			data.path = ft_strdup(*argv);
			ft_lstaddback(ents, ft_lstnew(&data, sizeof(data)));
		}
		argv++;
	}
	(void)opts;
}

void	get_opt_switch(char c, int *opts)
{
	if (c == 'l')
		*opts |= FT_LIST;
	else if (c == 'R')
		*opts |= FT_RECURSIVE;
	else if (c == 'a')
		*opts |= FT_DOT;
	else if (c == 'r')
		*opts |= FT_REVERSE;
	else if (c == 't')
		*opts |= FT_TSORT;
	else
		ls_usage(c);
}

int		get_opt(int argc, char **argv, int *opts)
{
	int i;

	i = 1;
	while (i < argc && argv[i][0] == '-' && argv[i][1] != '\0')
	{
		if (ft_strcmp(argv[i], "--") == 0)
		{
			i++;
			break ;
		}
		while (*++argv[i] != '\0')
			get_opt_switch(*argv[i], opts);
		i++;
	}
	return (i);
}

int		parse_ls(int argc, char **argv, t_list **ents, t_list **dirs)
{
	int opts;
	int nb_opts;

	opts = 0;
	nb_opts = get_opt(argc, argv, &opts);
	ft_strsort(argv + nb_opts, &ft_strcmp);
	if (argc - nb_opts > 1)
		opts |= FT_DIRNAME;
	if (argc - nb_opts == 0)
		get_files((char *[2]){".", NULL}, opts, ents, dirs);
	else
		get_files(argv + nb_opts, opts, ents, dirs);
	return (opts);
}
