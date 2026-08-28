
#include "../headers/codexion.h"


void	debug_and_refactor(t_coder *coder, pthread_mutex_t *output,
							t_arg *g_env)
{
	size_t	time;
	t_time	now;
	int		debug_time;
	int		refactor_time;

	print_state("is debugging", g_env, coder);
	debug_time = atoi(g_env->argv[4]);
	usleep(debug_time * 1000);
	print_state("is refactoring", g_env, coder);
	refactor_time = atoi(g_env->argv[5]);
	usleep(refactor_time * 1000);
}

void	*compile(t_coder *coder, t_arg *g_env, int q1, int q2)
{
	t_time	now;
	int		compile_time;

	pthread_mutex_lock(&(g_env->dongles[q1]));
	print_state("has taken a dongle", g_env, coder);
	pthread_mutex_lock(&(g_env->dongles[q2]));
	print_state("has taken a dongle", g_env, coder);
	print_state("is compiling", g_env, coder);
	compile_time = atoi(g_env->argv[3]);
	usleep(compile_time * 1000);
	poll_queues(q1, q2, g_env->q_locks, g_env->queues);
	coder->comp_num++;
	pthread_mutex_unlock(&(g_env->dongles[q1]));
	pthread_mutex_unlock(&(g_env->dongles[q2]));
	gettimeofday(&now, NULL);
	coder->last_comp = ((size_t) now.tv_sec) * 1000000 + now.tv_usec;
	g_env->don_cd[q1] = coder->last_comp + atoi(coder->argv[7]) * 1000;
	g_env->don_cd[q2] = g_env->don_cd[q1];
	debug_and_refactor(coder, g_env->output, g_env);
}

void	*code(void *arg)
{
	int				q1;
	int				q2;
	t_queue 		*queues;
	t_coder			*coder;
	pthread_mutex_t	*q_locks;
	t_time			time;
	t_code_arg		*c_arg;
	t_arg			*g_env;
	size_t			now;
	

	g_env = ((t_code_arg *) arg)->g_env;
	coder = ((t_code_arg *) arg)->coder;
	queues = g_env->queues;
	q_locks = g_env->q_locks;
	q1 = coder->cid;
	q2 = (coder->cid + 1) % atoi(g_env->argv[1]);
	while (1)
	{
		// if (num_reserved == num_coders - 1);
		// 		continue;
		gettimeofday(&time, NULL);
		now = ((size_t) time.tv_sec) * 1000000 + time.tv_usec;
		if (top(&queues[q1]) == coder->cid)
		{
			if (top(&queues[q2]) == coder->cid && now > g_env->don_cd[q1] && now > g_env->don_cd[q2])
				compile(coder, g_env, q1, q2);
			else
				insert_queue(coder, q_locks, queues, q2);
		}
		else
			insert_queue(coder, q_locks, queues, q1);
	}
	return ((void*) NULL);
}
