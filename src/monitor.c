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
		{
			print_state("burned out", g_env, g_env->coders[i]);
			return (1);
		}
		i++;
	}
	return (0);
}

void	*monitor(void *arg)
{
	t_arg	*g_env;

	g_env = (t_arg *) arg;
	while (!check_burnout(g_env) && !check_comps(g_env))
		;
	return (NULL);
}
