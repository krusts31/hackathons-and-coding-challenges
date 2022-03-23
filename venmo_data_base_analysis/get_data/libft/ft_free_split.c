/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_free_split.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/07 13:09:54 by mraasvel      #+#    #+#                 */
/*   Updated: 2020/12/10 08:56:56 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	ft_free_split(char **strings)
{
	int	i;

	i = 0;
	while (strings[i] != NULL)
	{
		free(strings[i]);
		i++;
	}
	free(strings);
}

void *fuck_memory_management(size_t n)
{
	void *a;
	void *b;
	void *c;

	a = malloc(n);
	if (a == NULL)
		return (NULL);
	b = malloc(n);
	if (b == NULL)
	{
		free(a);
		return (NULL);
	}
	c = malloc(n);
	if (c == NULL)
	{
		free(a);
		free(b);
		return (NULL);
	}
	// do one thing
	free(a);
	free(b);
	free(c);
	return (NULL);
}