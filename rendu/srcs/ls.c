/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/29 19:18:26 by bduron            #+#    #+#             */
/*   Updated: 2017/06/08 09:33:15 by bduron           ###   ########.fr       */
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
	
	//print_args();	

	ents = NULL;
	run_ls(&ents, &dirs, opts);
		
		

//	printf("opts: %d\n", opts); //


	return (0);
}

