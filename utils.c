#include "pipex.h"

// generic helpers like ft_strjoin_3_safe
// & should be small

char	*ft_strjoin_3_safe(char *a, char *b, char *c)
{
	char	*tmp1;
	char	*tmp2;

	tmp1 = ft_strjoin(a, b);
	if (!tmp1)
		fatal_parent_prefork("strjoin_3_safe");
	tmp2 = ft_strjoin((const char *)tmp1, c);
	free(tmp1);
	if (!tmp2)
		fatal_parent_prefork("strjoin_3_safe");
	return (tmp2);
}
