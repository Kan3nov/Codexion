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

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>

typedef struct coder
{
	int				cid;
	int				last_comp;
	int				arv_time;
	char			**argv;
	pthread_mutex_t	*dongles;
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

int	validation(int argc, char *argv[]);
int thread_init(char *argv[]);
void insert(t_queue *q, t_coder *elem);
int top(t_queue *q);