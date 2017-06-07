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

int ls_cmpname(t_list *a, t_list *b)
{
	char *name_a;
	char *name_b;

	name_a = a->data->dirent->d_name

	return (ft_strcmp(a->data->dirent->d_name, ))

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
	if (lstcmp(a, b) > 0) // (a->data <= b->data) 	//!\\ CMP function
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



/* Link list node */
struct node
{
	int data;
	struct node* next;
};


/* function prototypes */
struct node* SortedMerge(struct node* a, struct node* b);
void FrontBackSplit(struct node* source,
		struct node** frontRef, struct node** backRef);

/* sorts the linked list by changing next pointers (not data) */
void MergeSort(struct node** headRef)
{
	struct node* head = *headRef;
	struct node* a;
	struct node* b;

	/* Base case -- length 0 or 1 */
	if ((head == NULL) || (head->next == NULL))
	{
		return;
	}

	/* Split head into 'a' and 'b' sublists */
	FrontBackSplit(head, &a, &b); 

	/* Recursively sort the sublists */
	MergeSort(&a);
	MergeSort(&b);

	/* answer = merge the two sorted lists together */
	*headRef = SortedMerge(a, b);
}

/* See http://www.geeksforgeeks.org/?p=3622 for details of this 
 *    function */
struct node* SortedMerge(struct node* a, struct node* b)
{
	struct node* result = NULL;

	/* Base cases */
	if (a == NULL)
		return(b);
	else if (b==NULL)
		return(a);

	/* Pick either a or b, and recur */
	if (a->data <= b->data)
	{
		result = a;
		result->next = SortedMerge(a->next, b);
	}
	else
	{
		result = b;
		result->next = SortedMerge(a, b->next);
	}
	return(result);
}

/* UTILITY FUNCTIONS */
/* Split the nodes of the given list into front and back halves,
 *      and return the two lists using the reference parameters.
 *           If the length is odd, the extra node should go in the front list.
 *                Uses the fast/slow pointer strategy.  */
void FrontBackSplit(struct node* source,
		struct node** frontRef, struct node** backRef)
{
	struct node* fast;
	struct node* slow;
	if (source==NULL || source->next==NULL)
	{
		/* length < 2 cases */
		*frontRef = source;
		*backRef = NULL;
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
		*frontRef = source;
		*backRef = slow->next;
		slow->next = NULL;
	}
}

/* Function to print nodes in a given linked list */
void printList(struct node *node)
{
	while(node!=NULL)
	{
		printf("%d ", node->data);
		node = node->next;
	}
}

/* Function to insert a node at the beginging of the linked list */
void push(struct node** head_ref, int new_data)
{
	/* allocate node */
	struct node* new_node =
		(struct node*) malloc(sizeof(struct node));

	/* put in the data  */
	new_node->data  = new_data;

	/* link the old list off the new node */
	new_node->next = (*head_ref);    

	/* move the head to point to the new node */
	(*head_ref)    = new_node;
} 

/* Drier program to test above functions*/
int main()
{
	/* Start with the empty list */
	struct node* res = NULL;
	struct node* a = NULL;

	/* Let us create a unsorted linked lists to test the functions
	 *    Created lists shall be a: 2->3->20->5->10->15 */
	push(&a, 15);
	push(&a, 10);
	push(&a, 5); 
	push(&a, 20);
	push(&a, 3);
	push(&a, 2); 

	/* Sort the above created Linked List */
	MergeSort(&a);

	printf("\n Sorted Linked List is: \n");
	printList(a);           

	getchar();
	return 0;
}

