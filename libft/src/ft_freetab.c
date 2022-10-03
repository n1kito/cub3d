#include "libft.h"

void	ft_freetab(char ***tab)
{
	int	i;

	if (*tab == NULL)
		return ;
	i = 0;
	while ((*tab)[i])
	{
		free((*tab)[i]);
		i++;
	}
	free(*tab);
	*tab = NULL;
}
