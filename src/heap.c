/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klafi <klafi@learner.42.tech>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/24 14:07:04 by klafi             #+#    #+#             */
/*   Updated: 2026/08/25 13:46:03 by klafi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/heap.h"

// priority for all coders
int pr(t_coder *coder)
{
	if (strcmp(coder->argv[8], "edf") == 0)
		return (coder->last_comp + coder->argv[2]);
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
	if (strcpm(elem->argv[], "fifo") == 0)
		elem->arv_time = time.tv_sec * 1000 + time.tv_usec / 1000;
	if (q->len == q->limit)
		return (printf("Error, inserting an element when queue is full"));
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
