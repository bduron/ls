/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_ents_free.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/14 12:07:22 by bduron            #+#    #+#             */
/*   Updated: 2017/06/14 12:51:38 by bduron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

void ls_ents_free(void *p, size_t size)
{
	t_data	*data;

	data = (t_data *)p;

	if (data)
	{
	
		ft_strdel(&data->path);
		if (data->dirent)
			ft_memdel((void **)&data->dirent);
		free(data);
	}
	(void)size;
}

//void ls_fmt_free(t_fmt *fmt)
//{
//
//
//}
