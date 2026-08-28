/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coders.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klafi <kanan.lafi@learner.42.tech>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/24 11:40:51 by klafi             #+#    #+#             */
/*   Updated: 2026/08/28 09:32:01 by klafi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/codexion.h"

void print_state(char *state, t_arg *g_env, t_coder *c)
{
	t_time	now;
	size_t	time;

	gettimeofday(&now, NULL);
	time = (size_t) now.tv_sec * 1000000 + now.tv_usec;
	time = time - c->start_time;
	pthread_mutex_lock(g_env->output);
	printf("%d %d %s\n", (int) (time / 1000), c->cid, state);
	pthread_mutex_unlock(g_env->output);
}

void	debug_and_refactor(t_coder *coder, pthread_mutex_t *output,
							t_arg *g_env)
{
	size_t	time;
	t_time	now;
	int		debug_time;
	int		refactor_time;

	print_state("is debugging", g_env, coder);
	debug_time = atoi(g_env->argv[4]);
	usleep(debug_time * 1000);
	print_state("is refactoring", g_env, coder);
	refactor_time = atoi(g_env->argv[5]);
	usleep(refactor_time * 1000);
}

void poll_queues(int q1, int q2, pthread_mutex_t *q_locks, t_queue *queues)
{
	pthread_mutex_lock(&q_locks[q1]);
	poll(&queues[q1]);
	pthread_mutex_unlock(&q_locks[q1]);
	pthread_mutex_lock(&q_locks[q2]);
	poll(&queues[q2]);
	pthread_mutex_unlock(&q_locks[q2]);
}


void	*compile(t_coder *coder, t_arg *g_env, int q1, int q2)
{
	t_time	now;
	int		compile_time;

	pthread_mutex_lock(&(g_env->dongles[q1]));
	print_state("has taken a dongle", g_env, coder);
	pthread_mutex_lock(&(g_env->dongles[q2]));
	print_state("has taken a dongle", g_env, coder);
	print_state("is compiling", g_env, coder);
	compile_time = atoi(g_env->argv[3]);
	usleep(compile_time * 1000);
	poll_queues(q1, q2, g_env->q_locks, g_env->queues);
	// gettimeofday(&now, NULL);
	// *dongle_cooldown = now.tv_sec * 1000000 + time.tv_usec + coder->argv[7] * 1000
	coder->comp_num++;
	pthread_mutex_unlock(&(g_env->dongles[q1]));
	pthread_mutex_unlock(&(g_env->dongles[q2]));
	gettimeofday(&now, NULL);
	coder->last_comp = (size_t) now.tv_sec * 1000000 + now.tv_usec;
	debug_and_refactor(coder, g_env->output, g_env);
}

void	*code(void *arg)
{
	int				q1;
	int				q2;
	t_queue 		*queues;
	t_coder			*coder;
	pthread_mutex_t	*q_locks;

	queues = ((t_arg *) arg)->queues;
	coder = ((t_arg *) arg)->coder;
	q_locks = ((t_arg *) arg)->q_locks;
	q1 = coder->cid;
	q2 = (coder->cid + 1) % atoi(((t_arg *) arg)->argv[1]);
	while (1)
	{
		// if (num_reserved == num_coders - 1);
		// 		continue;
		if (top(&queues[q1]) == coder->cid)
		{
			if (top(&queues[q2]) == coder->cid) // *now > *dongle_cooldown
				compile(coder, ((t_arg *) arg), q1, q2);
			else
			{
				pthread_mutex_lock(&q_locks[q2]);
				insert(&queues[q2], coder);
				pthread_mutex_unlock(&q_locks[q2]);
			}
		}
		else
		{
			pthread_mutex_lock(&q_locks[q1]);
			insert(&queues[q1], coder);
			pthread_mutex_unlock(&q_locks[q1]);
		}
	}
	return ((void*) NULL);
}
