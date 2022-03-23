/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   generate_mongo_queries.c                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/12 14:07:15 by mraasvel      #+#    #+#                 */
/*   Updated: 2020/12/12 15:07:45 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "header.h"

/*
** input: ObjectId(5bbe28d54f3b13b02929c047)
** output: {"_id":{"$oid":"5bbe28d54f3b13b02929c047"}}
*/

char	*extract_id_string(char *object_id)
{
	char	*number;
	size_t	i;
	size_t	start;

	i = 0;
	while (object_id[i] != '(')
		i++;
	start = i + 1;
	while (object_id[i] != ')')
		i++;
	number = ft_substr(object_id + start, 0, i - start);
	if (number == NULL)
		return (NULL);
	return (number);
}

/*
** {"_id":{"$oid":"5bbe28d54f3b13b02929c047"}}, {"_id":{"$oid":"5bc6a78a4f3b13b029a02ce4"}}
*/

int	put_id(char *id)
{
	ft_putstr("{\"_id\":{\"$oid\":\"");
	ft_putstr(id);
	ft_putstr("\"}}");
	return (success);
}

/*
** Outputs mongodb queries for finding all IDs withing docs
*/

int	generate_query(char *start_of_query, t_docs *docs, char *end_of_query)
{
	size_t	i;
	char	*id;

	ft_putstr(start_of_query);
	i = 0;
	while (i < docs->nmemb)
	{
		id = extract_id_string(docs->doc_ids[i]);
		if (id == NULL)
			return (error);
		put_id(id);
		if (i != docs->nmemb - 1)
			ft_putstr(", ");
		i++;
	}
	ft_putstr(end_of_query);
	return (success);
}

int	generate_note_query(char *start_of_query, t_docs *docs, char *end_of_query)
{
	char	*id;
	size_t	i;

	i = 0;
	while (i < docs->nmemb)
	{
		ft_putstr(start_of_query);
		id = extract_id_string(docs->doc_ids[i]);
		if (id == NULL)
			return (error);
		put_id(id);
		free(id);
		ft_putstr(end_of_query);
		if (i != docs->nmemb - 1)
			write(1, "\n", 1);
		i++;
	}
	return (success);
}
