/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_libft.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 12:16:55 by bduron            #+#    #+#             */
/*   Updated: 2017/06/07 17:48:06 by bduron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* functions to add to le libft */

#include "ls.h"



void ft_lstinsert(t_list *dst, t_list *src)
{
	t_list *tmp;
	t_list *src_end;

	if (!src || !dst)
		return ;	

	tmp = dst->next;
	dst->next = src;
	src_end = src;
	while (src_end->next)
		src_end = src_end->next;
	src_end->next = tmp;	
}

//void ft_qsort(void *base, size_t nel, size_t width, int (*compar)(const void *, const void *))

//////////////////////////////////// MERGE SORT ///////////////////////////////////////////////

int ls_cmpname(t_list *a, t_list *b);
void ft_lstsort(t_list **headref, int (*lstcmp)());
t_list *sortedmerge(t_list *a, t_list *b, int (*lstcmp)());
void ft_lstsplit(t_list *source, t_list **front, t_list** back);


int ls_cmpname(t_list *a, t_list *b)
{
	char *name_a;
	char *name_b;

	name_a = ((t_data *)a->content)->dirent->d_name;
	name_b = ((t_data *)b->content)->dirent->d_name;

	return (ft_strcmp(name_a, name_b));
}

void ft_lstsort(t_list **headref, int (*lstcmp)())
{
	t_list *head = *headref;
	t_list *a;
	t_list *b;

	head = *headref;

	/* Base case -- length 0 or 1 */
	if ((head == NULL) || (head->next == NULL))
		return;

	/* Split head into 'a' and 'b' sublists */
	ft_lstsplit(head, &a, &b); 

	/* Recursively sort the sublists */
	ft_lstsort(&a, lstcmp);
	ft_lstsort(&b, lstcmp);

	/* answer = merge the two sorted lists together */
	*headref = sortedmerge(a, b, lstcmp);
}

t_list *sortedmerge(t_list *a, t_list *b, int (*lstcmp)())
{
	t_list *result = NULL;

	/* Base cases */
	if (a == NULL)
		return(b);
	else if (b == NULL)
		return(a);

	/* Pick either a or b, and recur */
	if (lstcmp(a, b) < 0) // (a->data <= b->data) 	//!\\ CMP function
	{
		result = a;
		result->next = sortedmerge(a->next, b, lstcmp);
	}
	else
	{
		result = b;
		result->next = sortedmerge(a, b->next, lstcmp);
	}
	return(result);
}

void ft_lstsplit(t_list *source, t_list **front, t_list** back)
{
	t_list *fast;
	t_list *slow;
	if (source == NULL || source->next == NULL)
	{
		/* length < 2 cases */
		*front = source;
		*back = NULL;
	}
	else
	{
		slow = source;
		fast = source->next;

		/* Advance 'fast' two nodes, and advance 'slow' one node */
		while (fast != NULL)
		{
			fast = fast->next;
			if (fast != NULL)
			{
				slow = slow->next;
				fast = fast->next;
			}
		}

		/* 'slow' is before the midpoint in the list, so split it in two
		 *       at that point. */
		*front = source;
		*back = slow->next;
		slow->next = NULL;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////