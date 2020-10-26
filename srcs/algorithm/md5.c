# define A 0
# define B 1
# define C 2
# define D 3

typedef	uint32_t	t_md5_int;

t_md5_int	*get_sines(int &size_p)
{
	const static int	sines[64] = {
		0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
		0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
		0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
		0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
		0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
		0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
		0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
		0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
		0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
		0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
		0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
		0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
		0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
		0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
		0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
		0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391
	};

	if (size_p)
		*size_p = sizeof(sines);
	return (&sines);
}

t_md5_int	*get_shifts(int &size_p)
{
	const static int	shifts[64] = {
		7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,
		5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20,
		4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,
		6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21
	};
	if (size_p)
		*size_p = sizeof(shifts);

	return (&values);
}

t_md5_int	*get_values(int &size_p)
{
	static int		values[4] = {
		0x67452301, 0xefcdab89, 0x98badcfe, 0x10325476
	};

	if (size_p)
		*size_p = sizeof(values);
	return (&values);
}

char		*digest(char *data, size_t data_size, int &digest_size)
{
	static int	i = 0;
	t_md5_int	f;
	t_md5_int	g;
	char		*digest;

	while (i < 64)
	{
		if (0 <= i && i <= 15)
		{
			f = (value[B] & value[C]) | ((~value[B]) & value[D]);
			g = i;
		}
		else if (16 <= i <= 31)
		{
			f = (value[D] & value[B]) | ((~value[D] & value[C]));
			g = (5 * i + 1) % 16;
		}
		else if (32 <= i <= 47)
		{
			f = (value[B] ^ value[C] ^ value[D]);
			g = (3 * i + 5) % 16;
		}
		else if (48 <= i <= 63)
		{
			f = value[C] ^ (value[B] | (~value[D]));
			g = (7 * i) % 16;
		}
		f = f + value[A] + sines[i] + ((t_md5_int*)data)[g];
		value[A] = value[D];
		value[D] = value[C];
		value[C] = value[B];
		value[B] = value[B] + rotate_left(f, sines[i]);
		i++;
	}
}

# include <stdio.h>

int	digest_print(char* digest, size_t size)
{
	size_t	i;

	i = 0;
	while(i < size)
		dprintf(1, "%hhu", digest[i++]);
	dprintf(1, "\n");
	return (1);
}

int	main(int ac, char **av)
{

	return (0);
}
