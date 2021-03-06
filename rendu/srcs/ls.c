/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/29 19:18:26 by bduron            #+#    #+#             */
/*   Updated: 2017/06/22 17:11:01 by bduron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

int		main(int argc, char **argv)
{
	int		opts;
	t_list	*ents;
	t_list	*dirs;

	ents = NULL;
	dirs = NULL;
	opts = parse_ls(argc, argv, &ents, &dirs);
	if (ents)
	{
		ls_display_flush(ents, dirs, opts);
		ft_lstdel(&ents, ls_ents_free);
	}
	ents = NULL;
	if (opts & FT_REVERSE)
		ft_lstrev(&dirs);
	run_ls(&ents, &dirs, opts);
	ft_lstdel(&dirs, ls_dirs_free);
	return (0);
}
