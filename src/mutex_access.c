/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_access.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klafi <klafi@learner.42.tech>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/29 10:46:42 by klafi             #+#    #+#             */
/*   Updated: 2026/09/08 14:07:00 by klafi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/codexion.h"

t_coder	*poll_queue(t_arg *g_env)
{
	t_coder	*coder;

	pthread_mutex_lock(g_env->q_lock);
	coder = poll(&g_env->queue);
	pthread_mutex_unlock(g_env->q_lock);
	return (coder);
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
		printf("%d %d %s\n", (int)(time / 1000), c->cid + 1, state);
	}
	else
		printf("%d %d %s\n", (int)(time / 1000), c->cid + 1, state);
	pthread_mutex_unlock(g_env->output);
}

void	insert_queue(t_coder *coder, t_arg *g_env)
{
	if (!coder || !g_env)
		return ;
	pthread_mutex_lock(g_env->q_lock);
	insert(&g_env->queue, coder);
	pthread_mutex_unlock(g_env->q_lock);
}

void	man_queue(t_arg *g_env, int coder_num, t_coder **coders)
{
	int		i;
	t_time	time;

	gettimeofday(&time, NULL);
	i = 0;
	pthread_mutex_lock(g_env->q_lock);
	while (coder_num--)
	{
		if (top(g_env) == -1)
			continue ;
		if (is_available(g_env->coders[top(g_env)], g_env, &time))
		{
			pthread_cond_signal(&g_env->acq_dong[top(g_env)]);
			poll_queue(g_env);
		}
		else
			coders[i++] = poll_queue(g_env);
	}
	while (i > 0)
		insert_queue(coders[--i], g_env);
	pthread_mutex_unlock(g_env->q_lock);
}
