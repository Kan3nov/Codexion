/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coders.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klafi <klafi@learner.42.tech>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/24 11:40:51 by klafi             #+#    #+#             */
/*   Updated: 2026/08/26 16:37:37 by klafi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/codexion.h"

void	*compile(t_coder *coder, pthread_mutex_t *output)
{
	t_time	now;
	size_t	time;
	int		compile_time;

	pthread_mutex_lock(&(coder->dongles[coder->cid]));
	pthread_mutex_lock(&(coder->dongles[(coder->cid + 1) %
		atoi(coder->argv[1])]));
	gettimeofday(&now, NULL);
	time = (size_t) now.tv_sec * 1000000 + now.tv_usec;
	time = time - coder->start_time;
	printf("%d %d is compiling", (int) (time / 1000), coder->cid);
	compile_time = atoi(coder->argv[3]);
	usleep(compile_time * 1000);
	pthread_mutex_unlock(&(coder->dongles[coder->cid]));
	pthread_mutex_unlock(&(coder->dongles[(coder->cid + 1) %
		atoi(coder->argv[1])]));
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
	q2 = (coder->cid + 1) % atoi(coder->argv[1]);
	while (1)
	{
		// if (num_reserved == num_coders - 1);
		// 		continue;
		if (top(&queues[q1]) == coder->cid)
		{
			if (top(&queues[q2]) == coder->cid)
			{
				compile(coder, ((t_arg *) arg)->output);
				//poll(q1)
				//poll(q2)
			}
			else
			{
				pthread_mutex_lock(&q_locks[coder->cid]);
				insert(&queues[q2], coder);
				pthread_mutex_unlock(&q_locks[coder->cid]);
				// pthread_cond_wait()
			}
		}
		else
		{
			pthread_mutex_lock(&q_locks[coder->cid]);
			insert(&queues[q1], coder);
			pthread_mutex_unlock(&q_locks[coder->cid]);
			// pthread_cond_wait()
		}
	}
	return ((void*) NULL);
}

int	coders_init(char *argv[], pthread_mutex_t *dongles, pthread_t *coders,
				t_queue *queues, pthread_mutex_t *q_locks,
				pthread_mutex_t *output)
{
	int				i;
	t_coder			*c;
	t_arg			*arg;
	t_time			t;

	i = 0;
	gettimeofday(&t, NULL);
	while(i < (int) atoi(argv[1]))
		c = malloc(sizeof(t_coder));
		arg = malloc(sizeof(t_arg));
		c->argv = argv;
		c->cid = i;
		c->dongles = dongles;
		c->last_comp = (size_t) t.tv_sec * 1000000 + t.tv_usec;
		c->comp_num = 0;
		c->start_time = c->last_comp;
		arg->coder = c;
		arg->queues = queues;
		arg->q_locks = q_locks;
		arg->output = output;
		if (pthread_create(&coders[i], NULL, &code, arg) != 0)
			return (1);
		i++;
	return (0);
}

void queues_init(t_queue *queues, int coder_num)
{
	int	i;
	
	i = 0;
	queues = malloc(sizeof(t_queue) * coder_num);
	while(i < coder_num)
	{
		queues[i].array = malloc(sizeof(t_coder) * 2);
		queues[i].array[0] = NULL;
		queues[i].array[1] = NULL;
		queues[i].len = 0;
		queues[i].limit = 2;
		i++;
	}
}

int thread_init(char *argv[])
{
	int				coder_num;
	int				i;
	pthread_t 		*coders;
	pthread_mutex_t *dongles;
	pthread_mutex_t *q_locks;
	pthread_mutex_t *output;
	t_queue			*queues;

	coder_num = atoi(argv[1]);
	coders = malloc(sizeof(pthread_t) * coder_num);
	dongles = malloc(sizeof(pthread_mutex_t) * coder_num);
	output =  malloc(sizeof(pthread_mutex_t));
	q_locks = malloc(sizeof(pthread_mutex_t) * coder_num);
	i = 0;
	while(i < coder_num)
	{
		pthread_mutex_init(&dongles[i], NULL);
		pthread_mutex_init(&q_locks[i], NULL);
		i++;
	}
	queues_init(queues, coder_num);
	coders_init(argv, dongles, coders, queues, q_locks, output);
}