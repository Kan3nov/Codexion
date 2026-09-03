/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   codexion.h										 :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: klafi <klafi@learner.42.tech>			  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2026/08/24 11:17:58 by klafi			 #+#	#+#			 */
/*   Updated: 2026/08/24 14:15:30 by klafi			###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <string.h>
# include <sys/time.h>
# include <time.h>

typedef struct coder
{
	int				cid;
	size_t			last_comp;
	size_t			arv_time;
	size_t			start_time;
	int				comp_num;
	char			**argv;
}	t_coder;

typedef struct timeval
{
	time_t		tv_sec; /* seconds */
	suseconds_t	tv_usec; /* microseconds */
}	t_time;

typedef struct queue
{
	t_coder	**array;
	int		len;
	int		limit;
}	t_queue;

typedef struct arg
{
	char			**argv;
	pthread_mutex_t	*dongles;
	t_queue			*queues;
	pthread_mutex_t	*q_locks;
	pthread_mutex_t	*output;
	t_coder			**coders;
	size_t			*don_cd;
	int				stop;
}	t_arg;

typedef struct code_arg
{
	t_arg	*g_env;
	t_coder	*coder;
}	t_code_arg;

int		coders_start(t_arg *g_env, pthread_t *coders_th, t_code_arg ***c_args);
void	free_all(t_arg *g_env, t_code_arg **c_args, int coder_num,
			pthread_t *coders_th);
int		validation(int argc, char *argv[]);
int		thread_init(char *argv[], int coder_num);
void	insert(t_queue *q, t_coder *elem);
int		top(t_queue *q);
t_coder	*poll(t_queue *q);

int		monitor_init(t_arg *g_env, pthread_t *monitor_th);
int		queues_init(t_queue **queues, int coder_num);
int		glob_env_init(char **argv, t_arg **g_env, int coder_num,
			t_queue *queues);
int		coders_init(int coder_num, t_arg *g_env, t_coder **coders);

void	*code(void *arg);
void	*monitor(void *arg);

void	poll_queues(int q1, int q2, pthread_mutex_t *q_locks, t_queue *queues);
void	insert_queue(t_coder *coder, pthread_mutex_t *q_locks,
			t_queue *queues, int q);
void	print_state(char *state, t_arg *g_env, t_coder *c);
#endif