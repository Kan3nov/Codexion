/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klafi <klafi@learner.42.tech>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/24 11:41:01 by klafi             #+#    #+#             */
/*   Updated: 2026/08/25 13:41:20 by klafi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/codexion.h"

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