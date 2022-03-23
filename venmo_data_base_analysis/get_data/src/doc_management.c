/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   doc_management.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/12 10:38:21 by mraasvel      #+#    #+#                 */
/*   Updated: 2020/12/12 14:49:35 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "header.h"
#include "libft.h"

/*
** Vector functions for array of strings.
*/

t_docs	*doc_init(size_t initial_size)
{
	t_docs	*doc;

	if (initial_size == 0)
		initial_size = 2;
	doc = (t_docs*)malloc(1 * sizeof(doc));
	if (doc == NULL)
		return (NULL);
	doc->doc_ids = (char**)malloc(initial_size * sizeof(char*));
	if (doc->doc_ids == NULL)
	{
		free(doc);
		return (NULL);
	}
	doc->nmemb = 0;
	doc->size = initial_size;
	return (doc);
}

int	doc_realloc(t_docs *docs)
{
	char	**new_ids;
	int		new_size;

	new_size = docs->size * 2;
	new_ids = (char**)malloc(new_size * sizeof(char*));
	if (new_ids == NULL)
		return (error);
	ft_memcpy(new_ids, docs->doc_ids, docs->nmemb * sizeof(char*));
	free(docs->doc_ids);
	docs->doc_ids = new_ids;
	docs->size = new_size;
	return (success);
}

int	doc_pushback(t_docs *docs, char *id)
{
	if (docs->nmemb == docs->size)
	{
		if (doc_realloc(docs) == error)
			return (error);
	}
	docs->doc_ids[docs->nmemb] = ft_strdup(id);
	if (docs->doc_ids[docs->nmemb] == NULL)
		return (error);
	docs->nmemb += 1;
	return (success);
}

void	ft_free_doc(t_docs *docs)
{
	size_t	i;

	i = 0;
	while (i < docs->nmemb)
	{
		free(docs->doc_ids[i]);
		i++;
	}
	free(docs->doc_ids);
	free(docs);
}
