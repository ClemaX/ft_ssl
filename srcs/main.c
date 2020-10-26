#include <ft_ssl.h>

int	main(int ac, char *const *av)
{
	t_ssl_cmd	*cmd;
	t_ssl_err	err;

	if ((err = ssl_parse_cmd(&cmd, ac, av)) != SSL_EOK)
		return (err);
	return (SSL_EOK);
}
