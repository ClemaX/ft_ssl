#include <ft_ssl.h>

t_ssl_err	ssl_exec_cmd(t_ssl_cmd *cmd)
{
	t_ssl_err	err;
	t_ssl_data	*digest;
	t_ssl_data	*chunk;
	size_t		read_size;

	err = SSL_EOK;
	if (cmd->opts & SSL_OSTRING
	&& (err = cmd->exec(&digest, cmd->data, ft_strlen(cmd->data))))
	{
		ft_dprintf(2, "ft_ssl: Error: command '%s' returned with abnormal code %d!\n", cmd->name, err);
		return (err);
	}
	if (!cmd->fds)
		return (err);
	if (!(chunk = malloc(sizeof(*chunk) * cmd->chunk_size)))
	{
		ft_dprintf(2, "ft_ssl: Error allocating %zu bytes chunk!\n", cmd->chunk_size);
		return (SSL_EALLOC);
	}
	while (*cmd->fds != -1 && err == SSL_EOK)
	{
		ft_dprintf(2, "processing fd %d...\n", *cmd->fds);
		while ((read_size = read(*cmd->fds, chunk, cmd->chunk_size)) > 0)
		{
			ft_dprintf(2, "chunk: '%.20s...'[%3zu bytes]\n", chunk, read_size);
			if ((err = cmd->exec(&digest, chunk, read_size)))
				ft_dprintf(2, "chunk: '%.20s...'[%3zu bytes] returned abnormal code %d!\n", chunk, read_size, err);
		}
		close(*cmd->fds);
		*cmd->fds = -1;
		cmd->fds++;
	}
	free(chunk);
	return (err);
}

int	main(int ac, char *const *av)
{
	t_ssl_cmd	*cmd;
	t_ssl_err	err;

	if ((err = ssl_parse_cmd(&cmd, ac, av)) != SSL_EOK)
		return (err);
	if ((err = ssl_exec_cmd(cmd)))
		return (err);
	return (SSL_EOK);
}
