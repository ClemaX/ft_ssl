#ifndef SSL_OPTS_H
# define SSL_OPTS_H

# include <errno.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdint.h>
# include <string.h>

# include <unistd.h>

# include <libft.h>

# define SSL_OSTDIN		0b00000001
# define SSL_OQUIET		0b00000010
# define SSL_OREV		0b00000100
# define SSL_OSTRING	0b00001000

# define SSL_OPTS		"pqrs"

typedef enum	e_ssl_err
{
	SSL_EOK = 0,
	SSL_ENOARG,
	SSL_EINVAL,
	SSL_EOPEN,
	SSL_EALLOC,
}				t_ssl_err;

typedef char t_ssl_data;
typedef uint8_t	t_ssl_opt;

typedef t_ssl_err (*t_ssl_exec)(t_ssl_data **dest, const t_ssl_data* data,
	size_t data_size);

typedef struct	s_ssl_cmd
{
	const char			*name;
	const t_ssl_exec	exec;
	t_ssl_opt			opts;
	int					*fds;
	const t_ssl_data	*data;
	const size_t		chunk_size;			
}               t_ssl_cmd;


t_ssl_cmd	*ssl_get_cmd(char *const name);
t_ssl_err	ssl_parse_cmd(t_ssl_cmd **cmd, int ac, char *const *av);

#endif
