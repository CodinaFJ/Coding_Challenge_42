#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (*(s + i))
		i++;
	return (i);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	write(fd, s, i);
}

void	*ft_memchr(const void *s, int c, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		if ((*((unsigned char *)s + i)) == (unsigned char)c)
			return ((void *) s + i);
		i++;
	}
	return (NULL);
}

char	*ft_strchr(const char *s, int c)
{
	return (ft_memchr(s, c, ft_strlen(s) + 1));
}

int	ft_islower(int c)
{
	if (c >= (int) 'a' && c <= (int) 'z')
		return (1);
	return (0);
}

int	ft_toupper(int c)
{
	if (ft_islower(c))
		return (c - 32);
	return (c);
}

int	check_pawn(char **argv, int m, int n)
{
	int	i = 0;
	int j = -1;

	//printf("Check pawn line: %d column %d\n", m, n + 1);
	if (m == 1)
		return (0);
	i = m - 1;
	j = n - 1;
	if (j >= 0)
	{
		if (argv[i][j] == 'K')
			return (1);
	}
	i = m - 1;
	j = n + 1;
	if (j < ft_strlen(argv[i]))
	{
		if (argv[i][j] == 'K')
			return (1);
	}
	return (0);
}

int check_rook(int argc, char **argv, int m, int n)
{
	int i = 1;
	int j = n;

	while (i < argc)
	{
		if (argv[i][j] == 'K')
			return (1);
		i++;
	}

	i = m;
	j = 0;

	while (argv[i][j])
	{
		if (argv[i][j] == 'K')
			return (1);
		j++;
	}

	return (0);
}

int check_bishop(int argc, char **argv, int m, int n)
{
	int i = m;
	int j = n;

	while (i < argc && argv[i][j])
	{
		if (argv[i][j] == 'K')
			return (1);
		i++;
		j++;
	}

	i = m;
	j = n;

	while (i > 0 && argv[i][j])
	{
		if (argv[i][j] == 'K')
			return (1);
		i--;
		j++;
	}

	i = m;
	j = n;

	while (i > 0 && j >= 0)
	{
		if (argv[i][j] == 'K')
			return (1);
		i--;
		j--;
	}

	i = m;
	j = n;

	while (i < argc && j >= 0)
	{
		if (argv[i][j] == 'K')
			return (1);
		i++;
		j--;
	}

	return (0);
}

int check_knight(int argc, char **argv, int m, int n)
{
	int i = m - 2;
	int j = n - 1;

	if (i > 0 && j >= 0 && i < argc && i < argc)
	{
		if (argv[i][j] == 'K')
			return (1);
	}
		
	j = n + 1;

	if (i > 0 && j >= 0 && i < argc && i < argc)
	{
		if (argv[i][j] == 'K')
			return (1);
	}

	j = n + 2;
	i = m - 1;

	if (i > 0 && j >= 0 && i < argc && i < argc)
	{
		if (argv[i][j] == 'K')
			return (1);
	}

	j = n + 2;
	i = m + 1;

	if (i > 0 && j >= 0 && i < argc && i < argc)
	{
		if (argv[i][j] == 'K')
			return (1);
	}

	i = m + 2;
	j = n + 1;

	if (i > 0 && j >= 0 && i < argc && i < argc)
	{
		if (argv[i][j] == 'K')
			return (1);
	}

	i = m + 2;
	j = n - 1;

	if (i > 0 && j >= 0 && i < argc && i < argc)
	{
		if (argv[i][j] == 'K')
			return (1);
	}

	j = n - 2;
	i = m + 1;

	if (i > 0 && j >= 0 && i < argc && i < argc)
	{
		if (argv[i][j] == 'K')
			return (1);
	}

	j = n - 2;
	i = m - 1;

	if (i > 0 && j >= 0 && i < argc && i < argc)
	{
		if (argv[i][j] == 'K')
			return (1);
	}

	return (0);
}

int	chess(int argc, char **argv)
{
	int	i = 0;
	int j = -1;

	while (++i < argc)
	{
		j = -1;
		while (argv[i][++j])
		{
			if (argv[i][j] == 'P')
				if (check_pawn(argv, i ,j))
					return (1);
			if (argv[i][j] == 'R')
				if (check_rook(argc, argv, i ,j))
					return (1);
			if (argv[i][j] == 'B')
				if (check_bishop(argc, argv, i ,j))
					return (1);
			if (argv[i][j] == 'Q')
			{
				if (check_bishop(argc, argv, i ,j))
					return (1);
				if (check_rook(argc, argv, i ,j))
					return (1);
			}
			if (argv[i][j] == 'H')
				if (check_knight(argc, argv, i ,j))
					return (1);
		}
	}
	return (0);
}

int validate_input(int argc, char **argv)
{
    int board_size;
    int i = 1;
    int j = -1;

    board_size = ft_strlen(argv[1]);
    while (++i < argc)
    {
        if (board_size != ft_strlen(argv[i]))
            return (1);
        while (argv[i][++j])
            ft_toupper(argv[i][j]);
    }
	return (0);
}

int main(int argc, char **argv)
{
    (void) argv;
    if (argc == 1)
	{
        ft_putstr_fd("\n", 1);
		return (0);
	}
    if (validate_input(argc, argv) == 0)
	{
        if (chess(argc, argv) == 0)
			ft_putstr_fd("Fail\n", 1);
		else
			ft_putstr_fd("Success\n", 1);
	}
	else
	{
		ft_putstr_fd("\n", 1);
		return (0);
	}
    return (0);
}