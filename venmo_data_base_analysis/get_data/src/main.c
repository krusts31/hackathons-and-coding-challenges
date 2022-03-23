/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/12 09:51:36 by mraasvel      #+#    #+#                 */
/*   Updated: 2020/12/12 14:49:25 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "header.h"
#include "libft.h"

int	main(int argc, const char *argv[])
{
	if (argc == 1)
		return (0);
	if (ft_atoi(argv[1]) == 1)
		get_keyword_matches("files/notes.txt", 1);
	else if (ft_atoi(argv[1]) == 2)
		get_keyword_matches("files/comment_one.txt", 2);
	else if (ft_atoi(argv[1]) == 3)
		get_keyword_matches("files/comment_two.txt", 3);
	return (0);
}
