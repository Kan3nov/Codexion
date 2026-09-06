/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klafi <klafi@learner.42.tech>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/24 11:41:01 by klafi             #+#    #+#             */
/*   Updated: 2026/09/06 09:23:21 by klafi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/codexion.h"

int	is_digit(char c)
{
	const char	*digits = "0123456789";
	int			i;

	i = 0;
	while (i < 10)
	{
		if (c == digits[i])
			return (1);
		i++;
	}
	return (0);
}

int	int_check(char *num)
{
	int	i;

	i = 0;
	while (num[i] == '-' || num[i] == '+')
		i++;
	while (num[i])
	{
		if (!is_digit(num[i]))
			return (0);
		i++;
	}
	return (1);
}

int	zero_check(char *num)
{
	int	i;

	i = 0;
	while (num[i] == '-' || num[i] == '+')
		i++;
	while (num[i])
	{
		if (num[i] != '0')
			return (0);
		i++;
	}
	return (1);
}

int	validation(int argc, char *argv[])
{
	int	i;

	i = 0;
	if (argc != 9)
		return (printf("Invalid number of arguments, should be exactly 8.\n"),
			1);
	while (++i < 7)
		if (!int_check(argv[i]) || atoi(argv[i]) <= 0)
			return (printf("Invalid integer value for argument %d\n", i), 1);
	if (!int_check(argv[7]) || (atoi(argv[7]) <= 0 && !zero_check(argv[7])))
		return (printf("Invalid integer value for argument %d\n", 7), 1);
	if (strcmp(argv[8], "fifo") && strcmp(argv[8], "edf"))
		return (printf("Invalid scheduling algorithm\n"), 1);
	return (0);
}
