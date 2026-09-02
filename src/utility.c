/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klafi <klafi@learner.42.tech>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/29 10:47:36 by klafi             #+#    #+#             */
/*   Updated: 2026/09/02 10:03:49 by klafi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/codexion.h"

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
		pthread_mutex_destroy(&(g_env->q_locks[coder_num]));
		free(g_env->queues[coder_num].array);
		free(g_env->coders[coder_num]);
		free(c_args[coder_num]);
	}
	pthread_mutex_destroy(g_env->output);
	free(g_env->output);
	free(g_env->q_locks);
	free(g_env->dongles);
	free(g_env->coders);
	free(coders_th);
	free(g_env->don_cd);
	free(g_env->queues);
	free(c_args);
	free(g_env);
}
