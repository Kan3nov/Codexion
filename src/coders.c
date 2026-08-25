/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coders.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klafi <klafi@learner.42.tech>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/24 11:40:51 by klafi             #+#    #+#             */
/*   Updated: 2026/08/25 13:55:31 by klafi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../headers/codexion.h"

int compile(void *coder)
{
	return (0);
}

void coders_init(char *argv[], pthread_mutex_t *dongles, pthread_t *coders)
{
	int				i;
	t_coder			*c;
	t_time			t;
	t_queue			*q1;
	t_queue			*q2;

	i = 0;
	gettimeofday(&t, NULL);
	while(i < (int) argv[1])
		c = malloc(sizeof(t_coder));
		c->argv = argv;
		c->cid = i;
		c->dongles = dongles;
		c->last_comp = t.tv_sec * 1000 + t.tv_usec / 1000;
		if (pthread_create(&coders[i], NULL, &compile, c) != 0)
			return (1);
		i++;
}

int thread_init(char *argv[])
{
	int				coder_num;
	int 			i;
	pthread_t 		*coders;
	pthread_mutex_t *dongles;
	

	coder_num = atoi(argv[1]);
	coders = malloc(sizeof(pthread_t) * coder_num);
	i = 0;
	while(i < coder_num)
	{
		pthread_mutex_init(&dongles[i], NULL);
		i++;
	}
	coders_init(argv, dongles, coders);
}