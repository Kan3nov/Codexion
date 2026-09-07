/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coders.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klafi <klafi@learner.42.tech>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/29 10:38:43 by klafi             #+#    #+#             */
/*   Updated: 2026/09/07 17:03:25 by klafi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/codexion.h"

void	debug_and_refactor(t_coder *coder, t_arg *g_env)
{
	int		debug_time;
	int		refactor_time;
	t_time	now;

	print_state("is debugging", g_env, coder);
	gettimeofday(&now, NULL);
	coder->last_comp = ((size_t) now.tv_sec) * 1000000 + now.tv_usec;
	debug_time = atoi(g_env->argv[4]);
	usleep(debug_time * 1000);
	print_state("is refactoring", g_env, coder);
	refactor_time = atoi(g_env->argv[5]);
	usleep(refactor_time * 1000);
}

void	*compile(t_coder *coder, t_arg *g_env, int q1, int q2)
{
	int		compile_time;
	t_time	now;

	pthread_mutex_lock(&(g_env->dongles[q1]));
	print_state("has taken a dongle", g_env, coder);
	while (q1 == q2 && !g_env->stop)
		;
	if (q1 == q2)
		return (pthread_mutex_unlock(&(g_env->dongles[q1])), NULL);
	pthread_mutex_lock(&(g_env->dongles[q2]));
	print_state("has taken a dongle", g_env, coder);
	print_state("is compiling", g_env, coder);
	compile_time = atoi(g_env->argv[3]);
	usleep(compile_time * 1000);
	coder->comp_num++;
	gettimeofday(&now, NULL);
	coder->last_comp = ((size_t) now.tv_sec) * 1000000 + now.tv_usec;
	g_env->don_cd[q1] = coder->last_comp + atoi(coder->argv[7]) * 1000;
	g_env->don_cd[q2] = coder->last_comp + atoi(coder->argv[7]) * 1000;
	pthread_mutex_unlock(&(g_env->dongles[q1]));
	pthread_mutex_unlock(&(g_env->dongles[q2]));
	g_env->d_avail[q1] = 1;
	g_env->d_avail[q2] = 1;
	return (debug_and_refactor(coder, g_env), NULL);
}

void	*code(void *arg)
{
	t_arg			*g_env;
	t_coder			*coder;

	g_env = ((t_code_arg *) arg)->g_env;
	coder = ((t_code_arg *) arg)->coder;
	insert_queue(coder, g_env);
	while (!g_env->stop)
	{
		pthread_mutex_lock(&g_env->coders_exec[coder->cid]);
		pthread_cond_wait(&g_env->acq_dong[coder->cid],
			&g_env->coders_exec[coder->cid]);
		compile(coder, g_env, coder->q1, coder->q2);
		insert_queue(coder, g_env);
		pthread_mutex_unlock(&g_env->coders_exec[coder->cid]);
	}
	return ((void *) NULL);
}
