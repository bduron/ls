/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/29 19:18:26 by bduron            #+#    #+#             */
/*   Updated: 2017/05/31 16:57:22 by bduron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

int main(int argc, char **argv)
{
	t_env e;

	env_init(&e);
	e.nopts = get_opt(argc, argv, &e);
	get_target(argc, argv, e.nopts, &e);		


//	printf("opts: %d\n", e.opts); //
	run_ls(&e);

	//free(e.target);

	return (0);
}
