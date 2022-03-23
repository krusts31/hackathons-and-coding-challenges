/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putstr_p.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/14 20:43:10 by mraasvel      #+#    #+#                 */
/*   Updated: 2020/11/14 20:46:57 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

/*
** Will put at most precision chars.
** Returns bytes written.
** Return -1 on write error, or NULL pointer.
*/

ssize_t	ft_putstr_p(char *str, ssize_t precision)
{
	ssize_t	len;

	if (str == 0)
		return (-1);
	if (precision == 0)
		return (0);
	len = ft_strlen(str);
	len = len < precision ? len : precision;
	return (write(1, str, len));
}
