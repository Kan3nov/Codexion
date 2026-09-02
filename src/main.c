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

	valid = validation(argc, argv);
	if (valid)
		return (valid);
	thread_init(argv, atoi(argv[1]));
	return (0);
}

/*
	if (argc == 1)
	{
		argc = 9;
		argv = malloc(sizeof(char *) * 9);
		argv[0] = "meow"; // file name
		argv[1] = "1";  //coders number
		argv[2] = "800";  //time to burnout
		argv[3] = "200";  //time to compile
		argv[4] = "200";  //time to debug
		argv[5] = "200";  //time to refactor
		argv[6] = "10";  //number of compiles required
		argv[7] = "0";  //dongle cooldown
		argv[8] = "fifo";  //scheduling algorithm
	}
	free(argv);
*/