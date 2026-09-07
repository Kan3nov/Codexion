/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klafi <klafi@learner.42.tech>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/24 14:07:04 by klafi             #+#    #+#             */
/*   Updated: 2026/09/07 08:51:46 by klafi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/heap.h"

// priority for all coders
size_t	pr(t_coder *coder)
{
	if (!coder)
		return (-1);
	if (strcmp(coder->argv[8], "edf") == 0)
		return (coder->last_comp + atoi(coder->argv[2]) * 1000);
	else if (strcmp(coder->argv[8], "fifo") == 0)
		return (coder->arv_time);
	else
		return (-1);
}

void	insert(t_queue *q, t_coder *elem)
{
	int		current;
	void	*temp;
	t_time	time;

	if (q->len == q->limit || !q || !elem)
		return ;
	current = 0;
	while (current < q->len)
		if (q->array[current++]->cid == elem->cid)
			return ;
	current = q->len;
	q->array[current] = elem;
	gettimeofday(&time, NULL);
	elem->arv_time = (size_t) time.tv_sec * 1000000 + time.tv_usec;
	while (current != 0
		&& pr(q->array[parent(current)]) > pr(q->array[current]))
	{
		temp = (q->array)[current];
		(q->array)[current] = (q->array)[parent(current)];
		(q->array)[parent(current)] = temp;
		current = parent(current);
	}
	q->len++;
}

void	heapify_down(t_queue *q, int current)
{
	int		left;
	int		right;
	int		smallest;
	t_coder	*temp;

	smallest = current;
	while (1)
	{
		left = left_c(smallest);
		right = right_c(smallest);
		if (left < q->len && pr(q->array[left]) < pr(q->array[current]))
			smallest = left;
		if (right < q->len && pr(q->array[right]) < pr(q->array[current]))
			smallest = right;
		if (smallest != current)
		{
			temp = q->array[current];
			q->array[current] = q->array[smallest];
			q->array[smallest] = temp;
			current = smallest;
		}
		else
			break ;
	}
}

t_coder	*poll(t_queue *q)
{
	t_coder	*result;

	if (q->len == 0)
		return (NULL);
	result = q->array[0];
	q->array[0] = q->array[q->len - 1];
	q->array[q->len-- - 1] = NULL;
	heapify_down(q, 0);
	return (result);
}

/*
void print_q(t_queue *q)
{
	int	i;

	i = 0;
	if (q->len == 0)
		printf("empty\n");
	while (i < q->len - 1)
	{
		if (q->array[i])
			printf("%d<-", q->array[i]->cid + 1);
		i++;
	}
	if (q->array[i])
		printf("%d\n", q->array[i]->cid + 1);
}
*/