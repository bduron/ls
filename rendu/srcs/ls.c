/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/29 19:18:26 by bduron            #+#    #+#             */
/*   Updated: 2017/06/16 20:37:01 by bduron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

int main(int argc, char **argv)
{
	int		opts;
	t_list	*ents;
	t_list	*dirs;

	ents = NULL;
	dirs = NULL;
	opts = parse_ls(argc, argv, &ents, &dirs);

	if (ents)  // ls_sort(&ents, opts);
	{
		ls_display_flush(ents, dirs, opts);
		ft_lstdel(&ents, ls_ents_free); 
//		printf("FLUSHED\n");
	}
	ents = NULL; // 
	if (opts & FT_REVERSE)
		ft_list_reverse(&dirs);
	run_ls(&ents, &dirs, opts);

	ft_lstdel(&dirs, ls_dirs_free); 

//	ft_printf("Dirs End: ");
//	ft_print_lst(dirs);

	return (0);
}

