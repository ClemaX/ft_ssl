#ifndef MD5_H
# define MD5_H

# include <ssl_cmd.h>

# define MD5_OPTS	"spqr"

t_ssl_err	md5_get_cmd(t_ssl_cmd *cmd, int ac, const char **av);
t_ssl_err	md5_exec_cmd(t_ssl_cmd *cmd);

#endif
