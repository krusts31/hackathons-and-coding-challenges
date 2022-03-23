#include "interface.h"

void	ft_profileadd_back(p_list **head, p_list *new)
{
	p_list	*temp;

	temp = *head;
	if (temp == 0)
	{
		*head = new;
		return ;
	}
	while (temp->next != 0)
		temp = temp->next;
	temp->next = new;
}

p_list	*ft_profilenew(char *content[])
{
	p_list	*profile_ptr;

	profile_ptr = (p_list*)malloc(sizeof(p_list));
	if (profile_ptr == 0)
		return (0);
	profile_ptr->username = content[0];
	profile_ptr->displayname = content[1];
	profile_ptr->date = content[2];
	profile_ptr->comment = content[3];
	profile_ptr->next = 0;
	return (profile_ptr);
}
