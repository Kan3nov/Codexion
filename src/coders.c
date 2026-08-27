/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coders.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klafi <klafi@learner.42.tech>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/24 11:40:51 by klafi             #+#    #+#             */
/*   Updated: 2026/08/27 14:12:09 by klafi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/codexion.h"

void	debug_and_refactor(t_coder *coder, pthread_mutex_t *output,
							t_arg *g_env)
{
	size_t	time;
	t_time	now;
	int		debug_time;
	int		refactor_time;

	gettimeofday(&now, NULL);
	time = (size_t) now.tv_sec * 1000000 + now.tv_usec;
	time = time - coder->start_time;
	pthread_mutex_lock(output);
	printf("%d %d is debugging\n", (int) (time / 1000), coder->cid);
	pthread_mutex_unlock(output);
	debug_time = atoi(g_env->argv[4]);
	usleep(debug_time * 1000);
	gettimeofday(&now, NULL);
	time = (size_t) now.tv_sec * 1000000 + now.tv_usec;
	time = time - coder->start_time;
	pthread_mutex_lock(output);
	printf("%d %d is refactoring\n", (int) (time / 1000), coder->cid);
	pthread_mutex_unlock(output);
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
	size_t	time;
	int		compile_time;

	pthread_mutex_lock(&(g_env->dongles[q1]));
	pthread_mutex_lock(&(g_env->dongles[q2]));
	gettimeofday(&now, NULL);
	time = (size_t) now.tv_sec * 1000000 + now.tv_usec;
	time = time - coder->start_time;
	pthread_mutex_lock(g_env->output);
	printf("%d %d is compiling\n", (int) (time / 1000), coder->cid);
	pthread_mutex_unlock(g_env->output);
	compile_time = atoi(g_env->argv[3]);
	usleep(compile_time * 1000);
	poll_queues(q1, q2, g_env->q_locks, g_env->queues);
	// gettimeofday(&now, NULL);
	// *dongle_cooldown = now.tv_sec * 1000000 + time.tv_usec + coder->argv[7] * 1000
	coder->comp_num++;
	pthread_mutex_unlock(&(g_env->dongles[q1]));
	pthread_mutex_unlock(&(g_env->dongles[q2]));
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

int	coders_init(t_arg *g_env, pthread_t *coders)
{
	int				i;
	t_coder			*c;
	t_time			t;

	i = 0;
	gettimeofday(&t, NULL);
	while(i < (int) atoi(g_env->argv[1]))
	{
		c = malloc(sizeof(t_coder));
		c->cid = i;
		c->last_comp = (size_t) t.tv_sec * 1000000 + t.tv_usec;
		c->comp_num = 0;
		c->start_time = c->last_comp;
		c->argv = g_env->argv;
		g_env->coder = c;
		if (pthread_create(&coders[i], NULL, &code, g_env) != 0)
			return (1);
		i++;
	}
	return (0);
}

void queues_init(t_queue **queues, int coder_num)
{
	int	i;
	
	i = 0;
	*queues = malloc(sizeof(t_queue) * coder_num);
	while(i < coder_num)
	{
		(*queues)[i].array = malloc(sizeof(t_coder) * 2);
		(*queues)[i].array[0] = NULL;
		(*queues)[i].array[1] = NULL;
		(*queues)[i].len = 0;
		(*queues)[i].limit = 2;
		i++;
	}
}

void	glob_env_init(char **argv, t_arg **g_env, int coder_num, t_queue *queues)
{
	pthread_mutex_t *dongles;
	pthread_mutex_t *q_locks;
	pthread_mutex_t *output;
	int				i;

	*g_env = malloc(sizeof(t_arg));
	dongles = malloc(sizeof(pthread_mutex_t) * coder_num);
	q_locks = malloc(sizeof(pthread_mutex_t) * coder_num);
	output =  malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(output, NULL);
	i = 0;
	while(i < coder_num)
	{
		pthread_mutex_init(&dongles[i], NULL);
		pthread_mutex_init(&q_locks[i], NULL);
		i++;
	}
	(*g_env)->argv = argv;
	(*g_env)->dongles = dongles;
	(*g_env)->output = output;
	(*g_env)->q_locks = q_locks;
	(*g_env)->queues = queues;
}

int thread_init(char *argv[])
{
	int				coder_num;
	pthread_t 		*coders;
	t_queue			*queues;
	t_arg			*g_env;

	coder_num = atoi(argv[1]);
	queues_init(&queues, coder_num);
	glob_env_init(argv, &g_env, coder_num, queues);
	coders = malloc(sizeof(pthread_t) * coder_num);
	coders_init(g_env, coders);
	while(1)
		;
}