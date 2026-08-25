/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klafi <klafi@learner.42.tech>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/24 14:07:04 by klafi             #+#    #+#             */
/*   Updated: 2026/08/25 16:06:34 by klafi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/heap.h"

// priority for all coders
int pr(t_coder *coder)
{
	if (strcmp(coder->argv[8], "edf") == 0)
		return (coder->last_comp + atoi(coder->argv[2]));
	else if (strcmp(coder->argv[8], "fifo"))
		return (coder->arv_time);
}

void insert(t_queue *q, t_coder *elem)
{
	int		current;
	void	*temp;
	t_time time;

	current = q->len;
	gettimeofday(&time, NULL);
	elem->arv_time = time.tv_sec * 1000 + time.tv_usec / 1000;
	if (q->len == q->limit)
		return (printf("Error, inserting an element when queue is full"),
			(void) 0);
	else if (q->len == 0)
		(q->array)[0] = elem;
	else
		while (current != 0 || pr(q->array[parent(current)]) > pr(q->array[current]))
		{
			temp = (q->array)[current];
			(q->array)[current] = (q->array)[parent(current)];
			(q->array)[parent(current)] = temp;
			current = parent(current);
		}
	q->len++;
}
int main(void)
{
	t_coder *c1;
	t_coder *c2;
	t_queue *q1;
	t_time time;

	c1 = malloc(sizeof(t_coder));
	c2 = malloc(sizeof(t_coder));
	q1 = malloc(sizeof(t_queue));
	q1->array = malloc(sizeof(t_coder) * 2);
	q1->len = 0;
	q1->limit= 2;

	c1->cid = 0;
	gettimeofday(&time, NULL);
	c1->last_comp = time.tv_sec * 1000  + time.tv_usec / 1000;
	c2->cid = 1;
	gettimeofday(&time, NULL);
	c2->last_comp = time.tv_sec * 1000  + time.tv_usec / 1000;
	insert(q1, c1);
	insert(q1, c2);
	for (int i = 0; i < 2; i++)
	{
		printf("%d\n", q1->array[i]->cid);
	}

}

void build_heap(void *array)
{
	
}

void heapify(void *array, int idx)
{
	
}

void *pop(t_queue *q)
{
	
}
