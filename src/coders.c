/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coders.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klafi <kanan.lafi@learner.42.tech>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/29 10:38:43 by klafi             #+#    #+#             */
/*   Updated: 2026/08/29 10:39:37 by klafi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/codexion.h"

void	debug_and_refactor(t_coder *coder, t_arg *g_env)
{
	int		debug_time;
	int		refactor_time;

	print_state("is debugging", g_env, coder);
	debug_time = atoi(g_env->argv[4]);
	usleep(debug_time * 1000);
	print_state("is refactoring", g_env, coder);
	refactor_time = atoi(g_env->argv[5]);
	usleep(refactor_time * 1000);
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
	coder->comp_num++;
	pthread_mutex_unlock(&(g_env->dongles[q1]));
	pthread_mutex_unlock(&(g_env->dongles[q2]));
	gettimeofday(&now, NULL);
	coder->last_comp = ((size_t) now.tv_sec) * 1000000 + now.tv_usec;
	g_env->don_cd[q1] = coder->last_comp + atoi(coder->argv[7]) * 1000;
	g_env->don_cd[q2] = g_env->don_cd[q1];
	debug_and_refactor(coder, g_env);
	return (NULL);
}

int	cooldown(int q1, int q2, t_arg *g_env)
{
	size_t			now;
	t_time			time;

	gettimeofday(&time, NULL);
	now = ((size_t) time.tv_sec) * 1000000 + time.tv_usec;
	return (now > g_env->don_cd[q1] && now > g_env->don_cd[q2]);
}

void	*code(void *arg)
{
	int				q1;
	int				q2;
	t_arg			*g_env;
	t_coder			*coder;

	g_env = ((t_code_arg *) arg)->g_env;
	coder = ((t_code_arg *) arg)->coder;
	q1 = coder->cid;
	q2 = (coder->cid + 1) % atoi(g_env->argv[1]);
	while (!g_env->stop)
	{
		if (top(&g_env->queues[q1]) == coder->cid)
		{
			if (top(&g_env->queues[q2]) == coder->cid
				&& cooldown(q1, q2, g_env))
				compile(coder, g_env, q1, q2);
			else
				insert_queue(coder, g_env->q_locks, g_env->queues, q2);
		}
		else
			insert_queue(coder, g_env->q_locks, g_env->queues, q1);
	}
	return ((void *) NULL);
}
