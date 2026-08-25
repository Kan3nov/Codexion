/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coders.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klafi <klafi@learner.42.tech>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/24 11:40:51 by klafi             #+#    #+#             */
/*   Updated: 2026/08/25 14:59:37 by klafi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../headers/codexion.h"

int compile(t_coder *coder)
{
	t_queue	q1;
	t_queue	q2;

	q1 = coder->queues[coder->cid];
	q2 = coder->queues[(coder->cid + 1) % atoi(coder->argv[1])];
	pthread_mutex_lock(&(coder->dongles[coder->cid]));
	while (1)
	{
		if (top(q1) == coder->cid && top(q2) == coder->cid)
		{
			//poll(q1)
			//poll(q2)
		}
		else
			insert(q1, coder);
			// pthread_cond_wait()
		pthread_mutex_unlock(&(coder->dongles[coder->cid]));
	}
	return (0);
}

void coders_init(char *argv[], pthread_mutex_t *dongles, pthread_t *coders,
				t_queue *queues)
{
	int				i;
	t_coder			*c;
	t_time			t;

	i = 0;
	gettimeofday(&t, NULL);
	while(i < (int) argv[1])
		c = malloc(sizeof(t_coder));
		c->argv = argv;
		c->cid = i;
		c->dongles = dongles;
		c->last_comp = t.tv_sec * 1000 + t.tv_usec / 1000;
		c->queues = queues;
		if (pthread_create(&coders[i], NULL, &compile, c) != 0)
			return (1);
		i++;
}

int thread_init(char *argv[])
{
	int				coder_num;
	int				i;
	pthread_t 		*coders;
	pthread_mutex_t *dongles;
	t_queue			*queues;

	coder_num = atoi(argv[1]);
	coders = malloc(sizeof(pthread_t) * coder_num);
	queues = malloc(sizeof(t_queue) * coder_num);
	i = 0;
	while(i < coder_num)
	{
		pthread_mutex_init(&dongles[i++], NULL);
		queues[i].array = malloc(sizeof(t_coder) * 2);
		queues[i].array[0] = NULL;
		queues[i].array[1] = NULL;
		queues[i].len = 0;
		queues[i].limit = 2;
	}
	coders_init(argv, dongles, coders, queues);
}