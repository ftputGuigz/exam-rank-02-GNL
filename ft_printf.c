#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>

typedef struct 	s_switch
{
	int width;
	int precision;

}				t_switch;

typedef struct	s_flags
{
	int 	i;
	int 	count;
	int		len;
	int 	negative;
	int		width;
	int 	precision;
	t_switch sw;
}				t_flags;

void	init_flags(t_flags *flags)
{
	flags->i = 0;
	flags->count = 0;
}

void	clear_flags(t_flags *flags)
{
	flags->negative = 0;
	flags->width = 0;
	flags->precision = 0;
	flags->len = 0;
	flags->sw.width = 0;
	flags->sw.precision = 0;
}

void	putchar(char c)
{
	write(1, &c, 1);
}

int		ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int		is_num(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

void	set_flags(const char *str, t_flags *flags)
{
	flags->i++;
	if (is_num(str[flags->i]))
	{
		while (is_num(str[flags->i]))
		{
			flags->sw.width = 1;
			flags->width = (flags->width * 10) + (str[flags->i++] - 48);
		}
	}
	if (str[flags->i] == '.')
	{
		flags->sw.precision = 1;
		flags->i++;
		while (is_num(str[flags->i]))
			flags->precision = (flags->precision * 10) + (str[flags->i++] - 48);
	}
}

void	print_x_char(int len, char c, t_flags *flags)
{
	int i = 0;
	while (i < len)
	{
		putchar(c);
		i++;
		flags->count++;
	}
}

void	putstr_len(char *str, int len, t_flags *flags)
{
	int i = 0;
	while (i < len)
		putchar(str[i++]);
	flags->count += len;
}

void	print_s(t_flags *flags, char *str)
{
	flags->i++;
	if(!str)
		str = "(null)";
	flags->len = ft_strlen(str);
	if (flags->sw.precision && flags->precision < flags->len)
		flags->len = flags->precision;
	print_x_char(flags->width - flags->len, ' ', flags);
	putstr_len(str, flags->len, flags);
}


void	putnbr_base(long nb, int base_len, char *base)
{
	if (nb >= base_len)
		putnbr_base(nb / base_len, base_len, base);
		putnbr_base(nb % base_len, base_len, base);
	else
		putchar(base[nb]);
}


int		get_size_base(long i, int base)
{
	int count = 1;
	while(i > 0)
	{
		i /= base;
		count++;
	}
	return (count);
}

void	print_d(t_flags *flags, long i)
{
	flags->i++;
	if (i < 0)
	{
		flags->negative = 0;
		i *= -1;
	}
	flags->len = get_size_base(i, 10);
	if (i == 0 && flags->sw.precision)
		flags->len = 0;
	if (flags->sw.precision && flags->precision > flags->len)
		flags->zeros_count = flags->precision - flags->len;
	if (flags->negative)
		flags->len++;
	return;
}

void	print_x(t_flags *flags, long i)
{
	return;
}

int	ft_printf(const char *str, ...)
{
	va_list arg;
	t_flags flags;

	va_start(arg, str);
	init_flags(&flags);
	while (str[flags.i])
	{
		if (str[flags.i] == '%')
		{
			clear_flags(&flags);
			set_flags(str, &flags);
			if (str[flags.i] == 's')
				print_s(&flags, va_arg(arg, char*));
			else if (str[flags.i] == 'd')
				print_d(&flags, (long)va_arg(arg, int));
			else if (str[flags.i] == 'x')
				print_x(&flags, (long)va_arg(arg, unsigned int));

		}
		else
		{
			putchar(str[flags.i]);
			flags.count++;
			flags.i++;
		}
	}
	va_end(arg);
	return (flags.count);
}
