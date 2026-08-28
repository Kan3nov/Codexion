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


// dongle cooldown, number of philosophers, freeing mallocs
#include "../headers/codexion.h"
int	main(int argc, char *argv[])
{
	int	valid;
	t_coder *c1;
	t_coder *c2;
	t_queue *q1;
	t_time time;

	if (argc == 1)
	{
		argc = 9;
		argv = malloc(sizeof(char *) * 9);
		argv[0] = "meow"; // file name
		argv[1] = "4";  //coders number
		argv[2] = "1000";  //time to burnout
		argv[3] = "100";  //time to compile
		argv[4] = "100";  //time to debug
		argv[5] = "100";  //time to refactor
		argv[6] = "4";  //number of compiles required
		argv[7] = "50";  //dongle cooldown
		argv[8] = "fifo";  //scheduling algorithm

	}
	valid = validation(argc, argv);
	if (valid)
		return (valid);
	thread_init(argv);
	return (0);
}
/*
	// testing ==========================================
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
	c1->argv = argv;
	c2->argv = argv;
	gettimeofday(&time, NULL);
	c2->last_comp = (size_t) time.tv_sec * 1000000  + time.tv_usec;
	insert(q1, c1);
	insert(q1, c2);
	printf("inserting: \n");
	for (int i = 0; i < 2; i++)
		printf("%d\n", q1->array[i]->cid);
	printf("polling: \n");
	for (int i = 0; i < 2; i++)
		printf("%d\n", poll(q1)->cid);
	insert(q1, c2);
	insert(q1, c1);
	printf("inserting in reverse order then polling : \n");
	for (int i = 0; i < 2; i++)
		printf("%d\n", poll(q1)->cid);
*/