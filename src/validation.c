/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klafi <kanan.lafi@learner.42.tech>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/24 11:41:01 by klafi             #+#    #+#             */
/*   Updated: 2026/09/04 16:57:44 by klafi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/codexion.h"

int	validation(int argc, char *argv[])
{
	int	i;

	i = 1;
	if (argc != 9)
	{
		printf("Invalid number of arguments, should be exactly 8.\n");
		return (1);
	}
	while (i < argc - 1)
	{
		if (atoi(argv[i]) <= 0 && !(i == 7 && argv[7][0] == '0'))
		{
			printf("Invalid integer value for argument %d\n", i);
			return (1);
		}
		i++;
	}
	if (strcmp(argv[8], "fifo") && strcmp(argv[8], "edf") && strcmp(argv[8], "lifo"))
	{
		printf("Invalid scheduling algorithm\n");
		return (1);
	}
	return (0);
}
