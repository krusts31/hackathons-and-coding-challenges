/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/12 17:07:11 by mraasvel      #+#    #+#                 */
/*   Updated: 2020/12/12 18:18:18 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include "../../libft/libft.h"

typedef struct	s_user
{
	char	*username;
	int		amount;
}				t_user;

int	update_user(char *line, t_user *user)
{
	size_t	i;
	char	**strings;

	i = 0;
	strings = ft_split(line, ',');
	if (strings == NULL)
		return (-1);
	if (strings[0] == NULL)
	{
		ft_free_split(strings);
		return (0);
	}
	while (user[i].username != NULL)
	{
		if (ft_strcmp(strings[0], user[i].username) == 0)
		{
			user[i].amount += 1;
			break ;
		}
		i++;
	}
	if (user[i].username == NULL)
	{
		user[i].username = ft_strdup(strings[0]);
		if (user[i].username == NULL)
			return (-1);
		user[i].amount = 1;
	}
	ft_free_split(strings);
	return (0);
}

void	sort_users(t_user *users)
{
	int	key;
	char	*key2;
	int	i;
	int	j;

	i = 1;
	while (users[i].username != NULL)
	{
		key = users[i].amount;
		key2 = users[i].username;
		j = i - 1;
		while (j >= 0)
		{
			if (key < users[j].amount)
			{
				users[i].amount = users[j].amount;
				users[i].username = users[j].username;
			}
			else
				break;
			j--;
		}
		users[j + 1].amount = key;
		users[j + 1].username = key2;
		i++;
	}
	for (int i = 0; users[i].username != 0; i++)
	{
		printf("%d: %s\n", users[i].amount, users[i].username);
		free(users[i].username);
	}
	free(users);
}

int	main(void)
{
	int		fd;
	int		ret;
	int		max;
	int		j;
	char	*line;
	t_user	*users;

	fd = open("../note_data.txt", O_RDONLY);
	if (fd == -1)
		return (0);
	users = (t_user*)ft_calloc(158444, sizeof(t_user));
	if (users == NULL)
		return (0);
	ret = 1;
	while (ret > 0)
	{
		ret = ft_getline(fd, &line);
		if (ret == -1)
			return (0);
		update_user(line, users);
		free(line);
	}
	max = 0;
	for (int i = 0; users[i].username != NULL; i++)
	{
		if (users[i].amount > max)
			j = i;
	}
	printf("%d: %s\n", users[j].amount, users[j].username);
	for (int i = 0; users[i].username != 0; i++)
	{
		free(users[i].username);
	}
	free(users);
	return (0);
}
