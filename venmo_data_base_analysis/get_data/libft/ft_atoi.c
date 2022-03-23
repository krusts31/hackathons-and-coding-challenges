/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atoi.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/26 12:56:28 by mraasvel      #+#    #+#                 */
/*   Updated: 2020/11/02 18:38:30 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

static int	ft_isspace(int c)
{
	if (c == '\r' || c == '\f' || c == '\n'
	|| c == '\v' || c == '\t' || c == ' ')
		return (8192);
	return (0);
}

int			ft_atoi(const char *nptr)
{
	int	nbr;
	int	negative;
	int	i;

	if (*(nptr) == 0)
		return (0);
	negative = 1;
	i = 0;
	while (ft_isspace(nptr[i]) != 0)
		i++;
	if (nptr[i] == '-')
		negative = -negative;
	if (nptr[i] == '+' || nptr[i] == '-')
		i++;
	nbr = 0;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		nbr = (nbr * 10) + (nptr[i] - '0');
		i++;
	}
	return (nbr * negative);
}
