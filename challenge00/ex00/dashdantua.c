#include <unistd.h>

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

int	ft_isdigit(int c)
{
	if (c >= (int) '0' && c <= (int) '9')
		return (1);
	return (0);
}

int	ft_isspace(int c)
{
	if ((unsigned char) c == ' ' || (unsigned char) c == '\t'
		|| (unsigned char) c == '\n' || (unsigned char) c == '\r'
		|| (unsigned char) c == '\v' || (unsigned char) c == '\f')
		return (1);
	return (0);
}

int	ft_atoi(const char *nptr)
{
	int	    i;
	char	neg;
	int		num;

	i = 0;
	neg = 0;
	num = 0;
	while (ft_isspace(nptr[i]))
		i++;
	if (*(nptr + i) == '-' || *(nptr + i) == '+')
	{
		neg = *(nptr + i);
		i++;
	}
	while (ft_isdigit((int)*(nptr + i)))
	{
		num = (num * 10) + (int)(*(nptr + i) - '0');
		i++;
	}
	if (neg == '-')
		return (-num);
	return (num);
}

void    print_line(int gap, int filling)
{
    int i;

    i = -1;
    while (++i < gap)
        ft_putchar_fd(' ', 1);
    ft_putchar_fd('/', 1);
    i = -1;
    while (++i < filling)
        ft_putchar_fd('*', 1);
    ft_putchar_fd('\\', 1);
    ft_putchar_fd('\n', 1);
}

void    print_line_door(int gap, int filling, int door_size)
{
    int i;
    int j;

    j = -1;
    i = -1;
    while (++i < gap)
        ft_putchar_fd(' ', 1);
    ft_putchar_fd('/', 1);
    i = -1;
    while (++i < filling/2)
        ft_putchar_fd('*', 1);
    while (++j < door_size)
    {
        ft_putchar_fd('|', 1);
        i++;
    }
    while (++i <= filling)
        ft_putchar_fd('*', 1);
    ft_putchar_fd('\\', 1);
    ft_putchar_fd('\n', 1);
}

void    print_line_door_knot(int gap, int filling, int door_size)
{
    int i;
    int j;

    j = -1;
    i = -1;
    while (++i < gap)
        ft_putchar_fd(' ', 1);
    ft_putchar_fd('/', 1);
    i = -1;
    while (++i < filling/2)
        ft_putchar_fd('*', 1);
    while (++j < door_size)
    {
        if (j + 1  == door_size - 1)
            ft_putchar_fd('$', 1);
        else
            ft_putchar_fd('|', 1);
        i++;
    }
    while (++i <= filling)
        ft_putchar_fd('*', 1);
    ft_putchar_fd('\\', 1);
    ft_putchar_fd('\n', 1);
}

int     calculate_gap(int current_local_line, int current_level, int total_levels)
{
    int gap;

    gap = 0;
    while (current_level <= total_levels)
    {
        gap += 2 + current_level - current_local_line;
        current_level++;
        if (current_level > total_levels)
            break;
        current_local_line = 1;
        gap += (current_level / 2) + 2;
    }
    return (gap);
}

int     calculate_filling(int total_line, int current_level, int total_levels)
{
    int i = 1;
    int filling;

    (void) total_levels;
    filling = 0;
    filling += 1 + 2 * (total_line - 1);
    while (i <= current_level)
    {
        i++;
        if (i > current_level)
            break;
        filling += ((i / 2) + 1) * 2;
    }
    return (filling);
}

int calc_door_size(int total_levels)
{
    int aux;

    aux = total_levels;
    if (total_levels % 2 == 0)
    {
        aux--;
    }
    if (aux == 0)
        return (1);
    return (aux);
}

void    print_level(int current_level, int total_levels, int *current_total_line)
{
    int level_lines;
    int current_local_line;

    current_local_line = 1;
    level_lines = 2 + current_level;
    while (current_local_line <= level_lines)
    {
        print_line(calculate_gap(current_local_line, current_level, total_levels),
                    calculate_filling(*current_total_line, current_level, total_levels));
        current_local_line++;
        (*current_total_line)++;
    }
}

void    print_last_level(int current_level, int total_levels, int *current_total_line)
{
    int level_lines;
    int current_local_line;
    int door_size;

    current_local_line = 1;
    level_lines = 2 + current_level;
    door_size = calc_door_size(total_levels);
    while (current_local_line <= level_lines - door_size)
    {
        print_line(calculate_gap(current_local_line, current_level, total_levels),
                    calculate_filling(*current_total_line, current_level, total_levels));
        current_local_line++;
        (*current_total_line)++;
    }
    while (current_local_line <= level_lines)
    {
        if (total_levels > 4 && current_local_line == level_lines - (door_size / 2))
        {
            print_line_door_knot(calculate_gap(current_local_line, current_level, total_levels),
                    calculate_filling(*current_total_line, current_level, total_levels),
                    door_size);
        }
        else
        {
            print_line_door(calculate_gap(current_local_line, current_level, total_levels),
                        calculate_filling(*current_total_line, current_level, total_levels),
                        door_size);
        }
        current_local_line++;
        (*current_total_line)++;
    }
}

void  dashdantua(int final_level)
{
    int current_total_line = 1;
    int current_level = 1;

    while (current_level < final_level)
    {
        print_level(current_level, final_level, &current_total_line);
        current_level++;
    }
    print_last_level(current_level, final_level, &current_total_line);
}

int main(int argc, char **argv)
{
    if (argc != 2)
        return (1);
    if (ft_atoi(argv[1]) < 1)
        return (2);
    dashdantua(ft_atoi(argv[1]));
    return (0);
}
