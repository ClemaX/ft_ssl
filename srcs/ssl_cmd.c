#include <ssl_cmd.h>

t_ssl_err md5_digest(t_ssl_data **dest, t_ssl_data *data, size_t data_size)
{
	*dest = NULL;
	write(1, data, data_size);
	return (SSL_EOK);
}

t_ssl_opt	ssl_get_opt(char *const str)
{
	int	pos;

	if (*str == '-' && (pos = ft_strpos(SSL_OPTS, ++*str)) != -1 && !*str)
	{
		ft_dprintf(2, "opt: %c\n", --*str);
		return (1 << pos);
	}
	ft_dprintf(2, "opt: Done!\n");
	return (0);
}

t_ssl_cmd	*ssl_get_cmd(char *const name)
{
	static t_ssl_cmd		cmds[] = {
		{
			.name="md5",
			.exec=&md5_digest
		}
	};
	const size_t			len = ft_strlen(name);
	size_t					i;

	i = 0;
	while (i < sizeof(cmds) / sizeof(*cmds))
		if (!ft_strncmp(cmds[i++].name, name, len))
			return (&cmds[i]);
	return (NULL);
}

t_ssl_err	ssl_parse_cmd(t_ssl_cmd **cmd, int ac, char *const *av)
{
	int			i;
	t_ssl_opt	opt;

	i = 1;
	if (ac <= i)
	{
		ft_dprintf(2, "usage: ft_ssl command [command opts] [command args]\n");
		return (SSL_ENOARG);
	}
	if (!(*cmd = ssl_get_cmd(av[i])))
	{
		ft_dprintf(2, "ft_ssl: Error: '%s' is an invalid command.\n", av[i]);
		return (SSL_EINVAL);
	}
	i++;
	while (i < ac && (opt = ssl_get_opt(av[i++])))
		(*cmd)->opts |= opt;
	while (i < ac)
	{
		ft_dprintf(2, "TODO: Open %s...\n", av[i]);
		i++;
	}
	return (SSL_EOK);
}
