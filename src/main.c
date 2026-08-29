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


// number of philosophers, freeing mallocs
#include "../headers/codexion.h"
int	main(int argc, char *argv[])
{
	int	valid;

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
		argv[6] = "1";  //number of compiles required
		argv[7] = "50";  //dongle cooldown
		argv[8] = "edf";  //scheduling algorithm

	}
	valid = validation(argc, argv);
	if (valid)
		return (valid);
	thread_init(argv, atoi(argv[1]));
	free(argv);
	return (0);
}