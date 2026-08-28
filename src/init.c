
#include "../headers/codexion.h"

int	coders_init(t_arg *g_env, pthread_t *coders_th)
{
	int				i;
	t_coder			*c;
	t_coder			**coders;
	int				coder_num;
	t_time			t;
	t_code_arg		*c_arg;

	gettimeofday(&t, NULL);
	coders = malloc(sizeof(t_coder *) * atoi(g_env->argv[1]));
	coder_num = atoi(g_env->argv[1]);
	g_env->coders = coders;
	i = 0;
	while(i < coder_num)
	{
		c = malloc(sizeof(t_coder));
		c->cid = i;
		c->last_comp = ((size_t) t.tv_sec) * 1000000 + t.tv_usec;
		c->comp_num = 0;
		c->start_time = c->last_comp;
		c->argv = g_env->argv;
		coders[i++] = c;
	}
	i = 0;
	while(i < coder_num)
	{
		c_arg = malloc(sizeof(t_code_arg));
		c_arg->coder = coders[i];
		c_arg->g_env = g_env;
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
	int				i;

	*g_env = malloc(sizeof(t_arg));
	dongles = malloc(sizeof(pthread_mutex_t) * coder_num);
	q_locks = malloc(sizeof(pthread_mutex_t) * coder_num);
	output =  malloc(sizeof(pthread_mutex_t));
	dongles_cooldown = malloc(sizeof(size_t) * coder_num);
	pthread_mutex_init(output, NULL);
	i = 0;
	while(i < coder_num)
	{
		pthread_mutex_init(&dongles[i], NULL);
		pthread_mutex_init(&q_locks[i], NULL);
		dongles_cooldown[i++] = 0;
	}
	(*g_env)->argv = argv;
	(*g_env)->dongles = dongles;
	(*g_env)->output = output;
	(*g_env)->q_locks = q_locks;
	(*g_env)->queues = queues;
	(*g_env)->don_cd = dongles_cooldown;
}		

int thread_init(char *argv[])
{
	int				coder_num;
	pthread_t 		*coders;
	t_queue			*queues;
	t_arg			*g_env;
	pthread_t		monitor;

	coder_num = atoi(argv[1]);
	queues_init(&queues, coder_num);
	glob_env_init(argv, &g_env, coder_num, queues);
	coders = malloc(sizeof(pthread_t) * coder_num);
	coders_init(g_env, coders);
	monitor_init(g_env, &monitor);
	pthread_join(monitor, NULL);
}

void monitor_init(t_arg *g_env, pthread_t *monitor_th)
{
	pthread_create(monitor_th, NULL, &monitor, (void *) g_env);
}