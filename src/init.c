
#include "../headers/codexion.h"

int	coders_init(int coder_num, t_arg *g_env, t_coder **coders)
{
	int	i;
	t_coder			*c;
	t_time			t;

	i = 0;
	gettimeofday(&t, NULL);
	while(i < coder_num)
	{
		c = malloc(sizeof(t_coder));
		if (!c)
			return (1);
		c->cid = i;
		c->last_comp = ((size_t) t.tv_sec) * 1000000 + t.tv_usec;
		c->comp_num = 0;
		c->start_time = c->last_comp;
		c->argv = g_env->argv;
		coders[i++] = c;
	}
	return (0);
}
int	coders_start(t_arg *g_env, pthread_t *coders_th, t_code_arg ***c_args)
{
	int				i;
	t_coder			**coders;
	int				coder_num;
	t_code_arg		*c_arg;

	coders = malloc(sizeof(t_coder *) * atoi(g_env->argv[1]));
	coder_num = atoi(g_env->argv[1]);
	*c_args = malloc(sizeof(t_code_arg *) * coder_num);
	coders_init(coder_num, g_env, coders);
	g_env->coders = coders;
	i = 0;
	while(i < coder_num)
	{
		c_arg = malloc(sizeof(t_code_arg));
		c_arg->coder = coders[i];
		c_arg->g_env = g_env;
		(*c_args)[i] = c_arg;
		if (pthread_create(&coders_th[i++], NULL, &code, c_arg) != 0)
			return (1);
	}
	return (0);
}

void queues_init(t_queue **queues, int coder_num)
{
	int	i;
	
	i = 0;
	*queues = malloc(sizeof(t_queue) * coder_num);
	while(i < coder_num)
	{
		(*queues)[i].array = malloc(sizeof(t_coder) * 2);
		(*queues)[i].array[0] = NULL;
		(*queues)[i].array[1] = NULL;
		(*queues)[i].len = 0;
		(*queues)[i].limit = 2;
		i++;
	}
}

void	glob_env_init(char **argv, t_arg **g_env, int coder_num, t_queue *queues)
{
	pthread_mutex_t *dongles;
	pthread_mutex_t *q_locks;
	pthread_mutex_t *output;
	size_t			*dongles_cooldown;

	*g_env = malloc(sizeof(t_arg));
	dongles = malloc(sizeof(pthread_mutex_t) * coder_num);
	q_locks = malloc(sizeof(pthread_mutex_t) * coder_num);
	output =  malloc(sizeof(pthread_mutex_t));
	dongles_cooldown = malloc(sizeof(size_t) * coder_num);
	pthread_mutex_init(output, NULL);
	while(--coder_num >= 0)
	{
		pthread_mutex_init(&dongles[coder_num], NULL);
		pthread_mutex_init(&q_locks[coder_num], NULL);
		dongles_cooldown[coder_num] = 0;
	}
	(*g_env)->argv = argv;
	(*g_env)->dongles = dongles;
	(*g_env)->output = output;
	(*g_env)->q_locks = q_locks;
	(*g_env)->queues = queues;
	(*g_env)->don_cd = dongles_cooldown;
	(*g_env)->stop = 0;
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

int thread_init(char *argv[], int coder_num)
{
	pthread_t 		*coders_th;
	t_queue			*queues;
	t_arg			*g_env;
	pthread_t		monitor;
	t_code_arg		**c_args;

	coder_num = atoi(argv[1]);
	queues_init(&queues, coder_num);
	glob_env_init(argv, &g_env, coder_num, queues);
	coders_th = malloc(sizeof(pthread_t) * coder_num);
	coders_start(g_env, coders_th, &c_args);
	monitor_init(g_env, &monitor);
	pthread_join(monitor, NULL);
	while (coder_num-- > 0)
		pthread_join(coders_th[coder_num], NULL);
	free_all(g_env, c_args, atoi(argv[1]), coders_th);
	return (0);
}

void monitor_init(t_arg *g_env, pthread_t *monitor_th)
{
	pthread_create(monitor_th, NULL, &monitor, (void *) g_env);
}