/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   monitor.c										  :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: klafi <kanan.lafi@learner.42.tech>		 +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2026/08/29 10:42:57 by klafi			 #+#	#+#			 */
/*   Updated: 2026/08/29 10:43:36 by klafi			###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "../headers/codexion.h"

int	check_comps(t_arg *g_env)
{
	int		i;
	int		coders_num;
	int		comps_needed;
	t_coder	**coders;

	coders_num = atoi(g_env->argv[1]);
	comps_needed = atoi(g_env->argv[6]);
	coders = g_env->coders;
	i = 0;
	while (i < coders_num)
	{
		if (coders[i]->comp_num < comps_needed)
			return (0);
		i++;
	}
	print_state("All coders finished their compiles", g_env, NULL);
	return (1);
}

int	check_burnout(t_arg *g_env)
{
	size_t	now;
	t_time	time;
	size_t	burn_time;
	int		i;

	i = 0;
	gettimeofday(&time, NULL);
	now = (size_t) time.tv_sec * 1000000 + time.tv_usec;
	while (i < atoi(g_env->argv[1]))
	{
		burn_time = atoi(g_env->argv[2]) * 1000;
		if ((g_env->coders[i]->last_comp + burn_time) / 1000 < now / 1000)
			return (print_state("burned out", g_env, g_env->coders[i]), 1);
		i++;
	}
	return (0);
}

int	cooldown(int q1, int q2, t_arg *g_env)
{
	size_t			now;
	t_time			time;

	gettimeofday(&time, NULL);
	now = ((size_t) time.tv_sec) * 1000000 + time.tv_usec;
	return (now > g_env->don_cd[q1] && now > g_env->don_cd[q2]);
}

int	is_available(t_coder *c, t_arg *g_env)
{
	if (g_env->d_avail[c->q1] && g_env->d_avail[c->q2]
			&& cooldown(c->q1, c->q2, g_env))
	{
		g_env->d_avail[c->q1] = 0;
		g_env->d_avail[c->q1] = 0;
		return (1);
	}
	return (0);
}

void signal_coders(t_arg *g_env)
{
	int	coder_num;

	coder_num = atoi(g_env->argv[1]);
	while (coder_num--)
		if (is_available(g_env->coders[top(g_env)], g_env))
			pthread_cond_signal(&g_env->acq_dong[coder_num]);
		else
			poll_queue(g_env);
}

void	*monitor(void *arg)
{
	t_arg	*g_env;

	g_env = (t_arg *) arg;
	while (!check_burnout(g_env) && !check_comps(g_env))
		;
	return (NULL);
}
