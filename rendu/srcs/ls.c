/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/29 19:18:26 by bduron            #+#    #+#             */
/*   Updated: 2017/05/29 20:49:54 by bduron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

void env_init(t_env *e)
{
	e->opts = 0;
//	e->files = NULL;
	e->target = NULL;

}

void get_target(int argc, char **argv, int i, t_env *e)
{
	int j;

	e->target = (char **)malloc(sizeof(char *) * (argc - i + 1));
	j = 0;
	while (i < argc)
		e->target[j++] = argv[i++];
	e->target[j] = '\0';
}

int get_opt(int argc, char **argv, t_env *e)
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
				e->opts |= FT_LIST;	
			else if (*argv[i] == 'R')
				e->opts |= FT_RECURSIVE;	
			else if (*argv[i] == 'a')
				e->opts |= FT_HIDDEN;	
			else if (*argv[i] == 'r')
				e->opts |= FT_REVERSE;	
			else if (*argv[i] == 't')
				e->opts |= FT_TSORT;	
			else 
				return (ERR_WRONGOPT);
		}	
		i++;
	}
	return (i);
}	



int main(int argc, char **argv)
{
	t_env e;

	env_init(&e);

	if ((e.nopts = get_opt(argc, argv, &e)) < 0)
	{
		printf("error\n"); // improve error put Usage()
		exit(1);
	}

	get_target(argc, argv, e.nopts, &e);		
			

	printf("opts: %d\n", e.opts); //
	while (*e.target)	//
		printf("%s\n", *e.target++); //


	return (0);
}

