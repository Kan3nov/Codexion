/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   main.c											 :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: klafi <klafi@learner.42.tech>			  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2026/08/24 11:18:05 by klafi			 #+#	#+#			 */
/*   Updated: 2026/08/24 11:20:07 by klafi			###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "../headers/codexion.h"
int	main(int argc, char *argv[])
{
	int	valid;
	t_coder *c1;
	t_coder *c2;
	t_queue *q1;
	t_time time;

	valid = validation(argc, argv);
	if (valid)
		return (valid);
//	thread_init(argv);

	c1 = malloc(sizeof(t_coder));
	c2 = malloc(sizeof(t_coder));
	q1 = malloc(sizeof(t_queue));
	q1->array = malloc(sizeof(t_coder) * 2);
	q1->len = 0;
	q1->limit= 2;
	for (int i = 0; i < 2; i++)
	{
		q1->array[i] = NULL;
	}
	c1->cid = 0;
	gettimeofday(&time, NULL);
	c1->last_comp = (size_t) time.tv_sec * 1000000  + time.tv_usec;
	c2->cid = 1;
	gettimeofday(&time, NULL);
	c2->last_comp = (size_t) time.tv_sec * 1000000  + time.tv_usec;
	c1->argv = argv;
	c2->argv = argv;
	insert(q1, c1);
	insert(q1, c2);
	for (int i = 0; i < 2; i++)
	{
		printf("%d\n", q1->array[i]->cid);
	}
	
	return (0);
}