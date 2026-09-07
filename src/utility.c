/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klafi <klafi@learner.42.tech>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/29 10:47:36 by klafi             #+#    #+#             */
/*   Updated: 2026/09/07 17:10:05 by klafi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/codexion.h"

int	mem_alloc2(t_arg **g_env, int coder_num);

int	coders_start(t_arg *g_env, pthread_t *coders_th, t_code_arg ***c_args)
{
	int				i;
	t_coder			**coders;
	int				coder_num;
	t_code_arg		*c_arg;

	coders = malloc(sizeof(t_coder *) * atoi(g_env->argv[1]));
	coder_num = atoi(g_env->argv[1]);
	*c_args = malloc(sizeof(t_code_arg *) * coder_num);
	if (!coders || !*c_args)
		return (1);
	coders_init(coder_num, g_env, coders);
	g_env->coders = coders;
	i = 0;
	while (i < coder_num)
	{
		c_arg = malloc(sizeof(t_code_arg));
		if (!c_arg)
			return (1);
		c_arg->coder = coders[i];
		c_arg->g_env = g_env;
		(*c_args)[i] = c_arg;
		if (pthread_create(&coders_th[i++], NULL, &code, c_arg) != 0)
			return (1);
	}
	return (0);
}

void	free_all(t_arg *g_env, t_code_arg **c_args, int coder_num,
					pthread_t *coders_th)
{
	while (--coder_num >= 0)
	{
		pthread_mutex_destroy(&(g_env->dongles[coder_num]));
		pthread_cond_destroy(&(g_env->acq_dong[coder_num]));
		pthread_mutex_destroy(&(g_env->coders_exec[coder_num]));
		free(g_env->queues[coder_num].array);
		free(g_env->coders[coder_num]);
		free(c_args[coder_num]);
	}
	pthread_mutex_destroy(g_env->output);
	pthread_mutex_destroy(g_env->q_lock);
	free(g_env->output);
	free(g_env->coders_exec);
	free(g_env->acq_dong);
	free(g_env->d_avail);
	free(g_env->q_lock);
	free(g_env->dongles);
	free(g_env->coders);
	free(coders_th);
	free(g_env->don_cd);
	free(g_env->queues);
	free(c_args);
	free(g_env);
}

int	mem_alloc(t_arg **g_env, int coder_num)
{
	pthread_mutex_t	*dongles;
	pthread_mutex_t	*q_lock;
	pthread_mutex_t	*output;
	size_t			*dongles_cooldown;
	int				*d_avail;

	dongles = malloc(sizeof(pthread_mutex_t) * coder_num);
	q_lock = malloc(sizeof(pthread_mutex_t));
	output = malloc(sizeof(pthread_mutex_t));
	dongles_cooldown = malloc(sizeof(size_t) * coder_num);
	d_avail = malloc(sizeof(int) * coder_num);
	if (!*g_env || !dongles || !q_lock || !output
		|| !dongles_cooldown || !d_avail)
		return (1);
	pthread_mutex_init(q_lock, NULL);
	(*g_env)->dongles = dongles;
	(*g_env)->output = output;
	(*g_env)->q_lock = q_lock;
	(*g_env)->don_cd = dongles_cooldown;
	(*g_env)->stop = 0;
	(*g_env)->d_avail = d_avail;
	return (mem_alloc2(g_env, coder_num));
}

int	mem_alloc2(t_arg **g_env, int coder_num)
{
	pthread_cond_t	*acq_dong;
	pthread_mutex_t	*coders_exec;

	acq_dong = malloc(sizeof(pthread_cond_t) * coder_num);
	coders_exec = malloc(sizeof(pthread_mutex_t) * coder_num);
	while (--coder_num >= 0)
		pthread_mutex_init(&coders_exec[coder_num], NULL);
	if (!acq_dong)
		return (1);
	(*g_env)->acq_dong = acq_dong;
	return (0);
}

void	determine_dongles(t_coder *coder, t_arg *g_env)
{
	if (coder->cid % 2 == 0)
	{
		coder->q1 = coder->cid;
		coder->q2 = (coder->cid + 1) % atoi(g_env->argv[1]);
	}
	else
	{
		coder->q1 = (coder->cid + 1) % atoi(g_env->argv[1]);
		coder->q2 = coder->cid;
	}
}

