/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klafi <klafi@learner.42.tech>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/29 10:44:19 by klafi             #+#    #+#             */
/*   Updated: 2026/09/05 09:31:56 by klafi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/codexion.h"

int	coders_init(int coder_num, t_arg *g_env, t_coder **coders)
{
	int				i;
	t_coder			*c;
	t_time			t;

	i = 0;
	gettimeofday(&t, NULL);
	while (i < coder_num)
	{
		c = malloc(sizeof(t_coder));
		if (!c)
			return (1);
		c->cid = i;
		c->last_comp = ((size_t) t.tv_sec) * 1000000 + t.tv_usec;
		c->comp_num = 0;
		c->start_time = c->last_comp;
		c->argv = g_env->argv;
		coders[i++] = c;
	}
	return (0);
}

int	queues_init(t_queue **queues, int coder_num)
{
	int	i;

	i = 0;
	*queues = malloc(sizeof(t_queue) * coder_num);
	if (!*queues)
		return (1);
	while (i < coder_num)
	{
		(*queues)[i].array = malloc(sizeof(t_coder) * 2);
		if (!(*queues)[i].array)
			return (1);
		(*queues)[i].array[0] = NULL;
		(*queues)[i].array[1] = NULL;
		(*queues)[i].len = 0;
		(*queues)[i].limit = 2;
		i++;
	}
	return (0);
}

int	glob_env_init(char **argv, t_arg **g_env,
	int coder_num, t_queue *queues)
{
	if (mem_alloc(g_env, coder_num))
		return (1);
	while (--coder_num >= 0)
	{
		pthread_mutex_init(&(*g_env)->dongles[coder_num], NULL);
		pthread_mutex_init(&(*g_env)->q_locks[coder_num], NULL);
		(*g_env)->don_cd[coder_num] = 0;
		(*g_env)->d_avail[coder_num] = 1;
	}
	(*g_env)->argv = argv;
	(*g_env)->queues = queues;
	return (pthread_mutex_init((*g_env)->output, NULL), 0);
}

int	thread_init(char *argv[], int coder_num)
{
	pthread_t		*coders_th;
	t_queue			*queues;
	t_arg			*g_env;
	pthread_t		monitor;
	t_code_arg		**c_args;

	coder_num = atoi(argv[1]);
	coders_th = malloc(sizeof(pthread_t) * coder_num);
	g_env = malloc(sizeof(t_arg));
	if (!coders_th || !g_env)
		return (1);
	if (queues_init(&queues, coder_num))
		return (1);
	if (glob_env_init(argv, &g_env, coder_num, queues))
		return (1);
	if (coders_start(g_env, coders_th, &c_args))
		return (1);
	if (monitor_init(g_env, &monitor))
		return (1);
	pthread_join(monitor, NULL);
	while (coder_num-- > 0)
		pthread_join(coders_th[coder_num], NULL);
	free_all(g_env, c_args, atoi(argv[1]), coders_th);
	return (0);
}

int	monitor_init(t_arg *g_env, pthread_t *monitor_th)
{
	if (pthread_create(monitor_th, NULL, &monitor, (void *) g_env) != 0)
		return (1);
	return (0);
}
