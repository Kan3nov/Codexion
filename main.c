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

#include "codexion.h"

int	validation(int argc, char *argv[])
{
	int	i;

	i = 1;
	if (argc < 9)
	{
		printf("One or more arguments are missing\n");
		return (1);
	}
	while (i < argc - 1)
	{
		if (!atoi(argv[i]))
		{
			printf("Invalid integer value for argument %d\n", i);
			return (1);
		}
		i++;
	}
	if (strcmp(argv[8], "fifo") && strcmp(argv[8], "edf"))
	{
		printf("Invalid scheduling algorithm\n");
		return (1);
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	int	valid;

	valid = validation(argc, argv);
	if (valid)
		return (valid);
	return (0);
}
