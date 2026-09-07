/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klafi <klafi@learner.42.tech>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/25 12:00:08 by klafi             #+#    #+#             */
/*   Updated: 2026/09/07 17:04:17 by klafi            ###   ########.fr       */
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

int	top(t_arg *g_env)
{
	int		result;

	pthread_mutex_lock(g_env->q_lock);
	if (g_env->queue.len != 0 && g_env->queue.array[0])
		result = g_env->queue.array[0]->cid;
	else
		result = -1;
	pthread_mutex_unlock(g_env->q_lock);
	return (result);
}
