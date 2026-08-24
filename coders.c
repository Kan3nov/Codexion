/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coders.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klafi <klafi@learner.42.tech>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/24 11:40:51 by klafi             #+#    #+#             */
/*   Updated: 2026/08/24 12:45:28 by klafi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "codexion.h"

int compile()
{
	return (0);
}

int thread_init(char *argv[])
{
	int	coder_num;
	int i;
	pthread_t *coders;
	pthread_mutex_t *dongles;
	

	coder_num = atoi(argv[1]);
	coders = malloc(sizeof(pthread_t) * coder_num);
	i = 0;
	while(i < coder_num)
		pthread_mutex_init(&dongles[i], NULL);
		i++;
	i = 0;
	while(i < coder_num)
		if (pthread_create(&coders[i], NULL, &compile, NULL) != 0)
			return (1);
		i++;
}