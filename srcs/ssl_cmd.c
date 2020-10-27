#include <ssl_cmd.h>

t_ssl_err md5_digest(t_ssl_data **dest, const t_ssl_data *data, size_t data_size)
{
	*dest = NULL;
	write(1, data, data_size);
	return (SSL_EOK);
}

t_ssl_opt	ssl_get_opt(const char * str)
{
	int			pos;
	t_ssl_opt	opt;
	t_ssl_opt	opts = 0;

	if (*str == '-')
	{
		str++;
		while (*str && (pos = ft_strpos(SSL_OPTS, *str)) != -1)
		{
			opt = 1 << pos;
			opts |= opt;
			str++;
		}
	}
	return (*str ? 0 : opts);
}

t_ssl_cmd	*ssl_get_cmd(char *const name)
{
	static t_ssl_cmd		cmds[1] = {
		{
			.name="md5",
			.exec=&md5_digest,
			.opts=0,
			.chunk_size=64
		}
	};
	const size_t			len = ft_strlen(name);
	size_t					i;

	i = 0;
	while (i < sizeof(cmds) / sizeof(*cmds))
	{
		if (!ft_strncmp(cmds[i].name, name, len))
			return (&cmds[i]);
		i++;
	}
	return (NULL);
}

t_ssl_err	ssl_parse_cmd(t_ssl_cmd **cmd, int ac, char *const *av)
{
	int			i;
	int			j;
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
	while (i < ac && (opt = ssl_get_opt(av[i])))
	{
		(*cmd)->opts |= opt;
		i++;
		if ((*cmd)->opts & SSL_OSTRING)
		{
			if (i >= ac)
			{
				ft_dprintf(2, "ft_ssl: Error: '-s' option must be followed by a string argument!\n");
				return (SSL_EINVAL);
			}
			(*cmd)->data = av[i++];
		}
	}
	if (!((*cmd)->fds = malloc(sizeof((*cmd)->fds) * (ac - i + 1))))
	{
		ft_dprintf(2, "ft_ssl: Error: could not allocate memory!\n");
		return (SSL_EALLOC);
	}
	j = 0;
	while (i < ac)
	{
		ft_dprintf(2, "Opening %s...\n", av[i]);
		
		if (((*cmd)->fds[j] = open(av[i], O_RDONLY)) == -1)
		{
			ft_dprintf(2, "ft_ssl: %s: %s!\n", av[i], strerror(errno));
			return (SSL_EOPEN);
		}
		i++;
		j++;
	}
	(*cmd)->fds[j] = -1;
	return (SSL_EOK);
}
