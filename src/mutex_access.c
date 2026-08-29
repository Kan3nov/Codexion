/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_access.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klafi <kanan.lafi@learner.42.tech>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/29 10:46:42 by klafi             #+#    #+#             */
/*   Updated: 2026/08/29 10:47:32 by klafi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/codexion.h"

void	poll_queues(int q1, int q2, pthread_mutex_t *q_locks, t_queue *queues)
{
	pthread_mutex_lock(&q_locks[q1]);
	poll(&queues[q1]);
	pthread_mutex_unlock(&q_locks[q1]);
	pthread_mutex_lock(&q_locks[q2]);
	poll(&queues[q2]);
	pthread_mutex_unlock(&q_locks[q2]);
}

void	print_state(char *state, t_arg *g_env, t_coder *c)
{
	t_time	now;
	size_t	time;

	gettimeofday(&now, NULL);
	time = (size_t) now.tv_sec * 1000000 + now.tv_usec;
	if (c)
		time = time - c->start_time;
	pthread_mutex_lock(g_env->output);
	if (g_env->stop == 1)
		return (pthread_mutex_unlock(g_env->output), (void) 0);
	if (!c)
	{
		g_env->stop = 1;
		printf("%s\n", state);
	}
	else if (strcmp("burned out", state) == 0)
	{
		g_env->stop = 1;
		printf("%d %d %s\n", (int)(time / 1000), c->cid, state);
	}
	else
		printf("%d %d %s\n", (int)(time / 1000), c->cid, state);
	pthread_mutex_unlock(g_env->output);
}

void	insert_queue(t_coder *coder,
	pthread_mutex_t *q_locks, t_queue *queues, int q)
{
	pthread_mutex_lock(&q_locks[q]);
	insert(&queues[q], coder);
	pthread_mutex_unlock(&q_locks[q]);
}
