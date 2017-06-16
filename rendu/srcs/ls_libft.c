/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_libft.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 12:16:55 by bduron            #+#    #+#             */
/*   Updated: 2017/06/14 12:54:23 by bduron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* functions to add to le libft */

#include "ls.h"

/////////// TIME //////////////

t_timestr *ft_timestr(time_t timestamp)
{
	char		*date;
	t_timestr	*time;

	time = (t_timestr*)malloc(sizeof(*time));	
	date = ctime(&timestamp);
	date[ft_strlen(date) - 1] = '\0';

	time->weekday = ft_strsub(date, 0, 3);
	time->month = ft_strsub(date, 4, 3);
	time->day = ft_strsub(date, 8, 2);
	time->hour = ft_strsub(date, 11, 2);
	time->minute = ft_strsub(date, 14, 2);
	time->second = ft_strsub(date, 17, 2);
	time->year = ft_isdigit(date[20]) ?
		ft_strsub(date, 20, 4) : ft_strsub(date, 24, 5);
	return (time);
}

void ft_timestr_del(t_timestr *time)
{
	free(time->weekday); 		
	free(time->day); 		
	free(time->month); 		
	free(time->hour); 		
	free(time->minute); 		
	free(time->second); 		
	free(time->year); 		
	free(time);
}

int		ft_time_isrecent(time_t event)
{
	time_t	now;

	now = time(&now);
	if (now - event >= 0 && now - event <= 6 * 365 / 12 * 24 * 60 * 60)
		return (1);
	else
		return (0);
}

//////////////////////////////


int ft_nblen(long n, int base)
{
    int len;

    if (base < 2)
        return (-1);

    len = (n < 0 && base == 10) ? 2 : 1;
    while (n /= base)
        len++;
    
    return (len);
}

/////////// LIST ///////////

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

void	ft_list_reverse(t_list **begin_list)
{
	t_list *current;
	t_list *prev;
	t_list *next;

	current = *begin_list;
	next = 0;
	prev = 0;
	while (current)
	{
		next = current->next;
		current->next = prev;
		prev = current;
		current = next;
	}
	*begin_list = prev;
}

void	ft_list_remove_if(t_list **begin_list, void *data_ref, int (*cmp)())
{
	t_list *tmp;
	t_list *prev;

	prev = 0;
	tmp = *begin_list;
	while (tmp)
	{
		if ((*cmp)(tmp->content, data_ref) == 0)
		{
			if (prev == 0)
				*begin_list = tmp->next;
			else
				prev->next = tmp->next;
			free(tmp);
		}
		prev = tmp;
		tmp = tmp->next;
	}
}

//void ft_qsort(void *base, size_t nel, size_t width, int (*compar)(const void *, const void *))

//////////////////////////////////// MERGE SORT ///////////////////////////////////////////////

void ft_lstsort(t_list **headref, int (*lstcmp)());
t_list *sortedmerge(t_list *a, t_list *b, int (*lstcmp)());
void ft_lstsplit(t_list *source, t_list **front, t_list** back);



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
