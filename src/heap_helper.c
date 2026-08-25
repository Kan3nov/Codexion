/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klafi <klafi@learner.42.tech>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/25 12:00:08 by klafi             #+#    #+#             */
/*   Updated: 2026/08/25 14:25:48 by klafi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/heap.h"

int parent(int child)
{
	return (child - 1) / 2;
}

int left_c(int parent)
{
	return parent * 2  + 1;
}

int right_c(int parent)
{
	return parent * 2  + 2;
}

int main(void)
{
	float x;
	x = 5/3;
	printf("%.2f\n", 5.3/3);
}