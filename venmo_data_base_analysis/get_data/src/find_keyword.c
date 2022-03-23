/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   find_keyword.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/12 10:36:26 by mraasvel      #+#    #+#                 */
/*   Updated: 2020/12/12 17:55:49 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include "header.h"
#include "libft.h"

const char	*keywords[] =
{
	"1p",
	"5meOdmt",
	"dissociatives",
	"noids",
	"1P_LSD",
	"dissonautuniverse",
	"nootropics",
	"2cb",
	"dmt",
	"opiates",
	"4acodmt",
	"DPH",
	"PCP",
	"adderall",
	"dxm",
	"phenibut",
	"afinil",
	"fentanyl",
	"PoppyTea",
	"alcohol",
	"kava",
	"psilocybinmushrooms",
	"ambien",
	"ketamine",
	"researchchemicals",
	"amt",
	"kombucha",
	"salvia",
	"anabolic",
	"kratom",
	"steroids",
	"lean",
	"stims",
	"ayahuasca",
	"lsa",
	"thesaviorsubstances",
	"benzodiazepines",
	"lsd",
	"treedibles",
	"cannabis",
	"mdma",
	"trees",
	"cannabisextracts",
	"memantinehcl",
	"cocaine",
	"mescaline",
	"cigarettes",
	"meth",
	"drugcombos",
	"modafinil",
	"mre",
	"drugs",
	"line",
	"coke",
	"alcohol",
	"high",
	"shroom",
	"weed",
	"meth",
	"shrooms",
	"crack",
	"grass",
	"dope",
	"edibles",
	"acid",
	"heroin",
	"booze",
	"guns",
	"sative",
	"indica",
	"molly",
	"mdma",
	"morphine",
	"speed",
	"opium",
	"kandy",
	"not drugs",
	"steroids",
	"lean",
	"sizzurp",
	"flakka",
	"kush",
	"smack",
	"420",
	"sex",
	"blow",
	"head",
	"strip",
	"sugar",
	"daddy",
	"loyal",
	"spoil",
	"mommy",
	"milk",
	"strip",
	"drank",
	"nudes",
	"glizzy",
	"mushroom",
	"pill",
	"eggplant",
	"banana",
	"aubergine",
	"peach",
	"water",
	"needle",
	"xxx",
	"i love you",
	"will you marry me",
	"password",
	"pas",
	"kill",
	"fuck",
	NULL
};

static void	ft_strtolower(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != 0)
	{
		str[i] = ft_tolower(str[i]);
		i++;
	}
}

static size_t	get_keyword_size(void)
{
	size_t	i;

	i = 0;
	while (keywords[i] != NULL)
		i++;
	return (i);
}

void			print_keyword_appearances(int *keyword_appearances, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		fprintf(stderr, "%s: %d\n", keywords[i], keyword_appearances[i]);
		i++;
	}
}

size_t	ft_strings_size(char **strings)
{
	size_t	i;

	i = 0;
	while (strings[i] != NULL)
		i++;
	return (i);
}

int	find_match(char *line, t_docs *docs, int *key_appears)
{
	char	**strings;
	size_t	i;
	int		found;

	strings = ft_split(line, ',');
	if (strings == NULL)
		return (error);
	if (ft_strings_size(strings) != 2)
		return (success);
	i = 0;
	found = 0;
	ft_strtolower(strings[0]);
	while (keywords[i] != NULL)
	{
		if (strstr(strings[0], keywords[i]) != NULL)
		{
			found = 1;
			key_appears[i] += 1;
			break ;
		}
		i++;
	}
	if (keywords[i] == NULL)
	{
		ft_free_split(strings);
		return (success);
	}
	doc_pushback(docs, strings[1]);
	ft_free_split(strings);
	return (success);
}

int	read_in_data(char *pathname, t_docs *docs, int type)
{
	int		fd;
	int		ret;
	char	*line;
	int		total_keys;
	int		*key_appears;

	fd = open(pathname, O_RDONLY);
	if (fd == -1)
	{
		perror(pathname);
		return (error);
	}
	ret = 1;
	total_keys = get_keyword_size();
	key_appears = (int*)ft_calloc(total_keys, sizeof(int));
	if (key_appears == NULL)
		return (error);
	while (ret > 0)
	{
		ret = ft_getline(fd, &line);
		if (ret == -1)
			return (error);
		if (*line != '\0');
			find_match(line, docs, key_appears);
		free(line);
	}
	if (type == 1)
		print_keyword_appearances(key_appears, total_keys);
	close(fd);
	return (success);
}

int	print_doc_ids(t_docs *docs)
{
	size_t	i;

	i = 0;
	while (i < docs->nmemb)
	{
		printf("%s\n", docs->doc_ids[i]);
		i++;
	}
	return (success);
}

int	get_keyword_matches(char *pathname, int type)
{
	t_docs	*docs;
	int		ret;

	docs = doc_init(0);
	if (docs == NULL)
		return (error);
	ret = read_in_data(pathname, docs, type);
	if (ret == error)
	{
		ft_free_doc(docs);
		return (error);
	}
	if (type == 1)
		generate_note_query("mongoexport -d test -c venmo -f 'payment.actor.username,payment.actor.display_name,date_created,note' -q '", docs, " ' --type=csv --noHeaderLine");
	else if (type == 2)
		generate_query("mongoexport -d test -c venmo -f 'comments.data.0.user.username,comments.data.0.user.display_name,comments.data.0.date_created,comments.data.0.message' -q '{ $or: [", docs, "] }' --type=csv --noHeaderLine -o files/comment_one_data.txt");
	else if (type == 3)
		generate_query("mongoexport -d test -c venmo -f 'comments.data.0.user.username,comments.data.0.user.display_name,comments.data.0.date_created,comments.data.0.message' -q '", docs, "' --type=csv --noHeaderLine -o files/comment_two_data.txt");
	write(1, "\n", 1);
	ft_free_doc(docs);
	return (success);
}
