/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klafi <klafi@learner.42.tech>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/08 14:05:04 by klafi             #+#    #+#             */
/*   Updated: 2026/09/08 14:07:16 by klafi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/codexion.h"

int	cooldown(int q1, int q2, t_arg *g_env, t_time *time)
{
	size_t	now;

	now = ((size_t) time->tv_sec) * 1000000 + time->tv_usec;
	return (now > g_env->don_cd[q1] && now > g_env->don_cd[q2]);
}
