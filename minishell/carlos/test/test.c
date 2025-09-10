#include "test.h"

int	ft_strcmp_equal(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s1[i] == s2[i] && s1[i] != '=' && s2[i] != '=')
		i++;
	if ((s1[i] == '=' || s1[i] == 0) && (s2[i] == '=' || s2[i] == 0))
		return (0);
	if (s2[i] == '=')
		return (1);
	if (s1[i] == '=')
		return (-1);
	return ((unsigned char) s1[i] - (unsigned char) s2[i]);
}

int	main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)env;
	ft_printf(1, "%d\n", ft_strcmp_equal(argv[1], argv[2]));
	return (0);
}
