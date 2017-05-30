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

void ls_init(t_ls *ls)
{
	ls->opts = 0;
//	ls->files = NULL;

}

int get_opt(int argc, char **argv, t_ls *ls)
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
				ls->opts |= FT_LIST;	
			else if (*argv[i] == 'R')
				ls->opts |= FT_RECURSIVE;	
			else if (*argv[i] == 'a')
				ls->opts |= FT_HIDDEN;	
			else if (*argv[i] == 'r')
				ls->opts |= FT_REVERSE;	
			else if (*argv[i] == 't')
				ls->opts |= FT_TSORT;	
			else 
				return (ERR_WRONGOPT);
		}	
		i++;
	}

	while (i < argc)
	{
		printf("%s\n", argv[i]);
		i++;
	}

	return (0);
}	



int main(int argc, char **argv)
{
	t_ls ls;

	ls_init(&ls);
	if (get_opt(argc, argv, &ls))
		printf("error\n");

	printf("opts: %d\n", ls.opts);


	return (0);
}

