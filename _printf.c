#include "main.h"

void print_buffer(char buffer[], int *buffer_count);

/**
 * _printf - Printf function
 * @var_fmt: formart variable
 * Return: Printed chars.
 */
int _printf(const char *var_fmt, ...)
{
	int i, printed = 0, p_str = 0;
	int flags, width, precision, size, buffer_count = 0;
	va_list list;
	char buffer[BUFF_SIZE];

	if (var_fmt == NULL)
		return (-1);

	va_start(list, var_fmt);

	for (i = 0; var_fmt && var_fmt[i] != '\0'; i++)
	{
		if (var_fmt[i] != '%')
		{
			buffer[buffer_count++] = var_fmt[i];
			if (buffer_count == BUFF_SIZE)
				print_buffer(buffer, &buffer_count);
			/* write(1, &var_fmt[i], 1);*/
			p_str++;
		}
		else
		{
			print_buffer(buffer, &buffer_count);
			flags = flag_func(var_fmt, &i);
			width = get_width(var_fmt, &i, list);
			precision = get_precision(var_fmt, &i, list);
			size = get_size(var_fmt, &i);
			++i;
			printed = handle_print(var_fmt, &i, list, buffer,
				flags, width, precision, size);
			if (printed == -1)
				return (-1);
			p_str += printed;
		}
	}

	print_buffer(buffer, &buffer_count);

	va_end(list);

	return (p_str);
}

/**
 * print_buffer - Prints the contents of the buffer if it exist
 * @buffer: Array of chars
 * @buffer_count: Index at which to add next char, represents the length
 */
void print_buffer(char buffer[], int *buffer_count)
{
	if (*buffer_count > 0)
		write(1, &buffer[0], *buffer_count);

	*buffer_count = 0;
}
