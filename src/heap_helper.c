/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klafi <kanan.lafi@learner.42.tech>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/25 12:00:08 by klafi             #+#    #+#             */
/*   Updated: 2026/08/29 10:42:26 by klafi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/heap.h"

int	parent(int child)
{
	return ((child - 1) / 2);
}

int	left_c(int parent)
{
	return (parent * 2 + 1);
}

int	right_c(int parent)
{
	return (parent * 2 + 2);
}

int	top(t_queue *q)
{
	if (q->len != 0)
		return (q->array[0]->cid);
	else
		return (-1);
}
