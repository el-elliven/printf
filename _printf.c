#include "main.h"

void print_buffer(char buffer[], int *buff_ind);

/**
 * _printf - Printf function
 * @format: format.
 * Return: Printed chars.
 */
int _printf(const char *fmt, ...)
{
	int count, printed = 0, printed_chars = 0;
	int flags, width, precision, size, buff_ind = 0;
	va_list arglist;
	char buffer[BUFF_SIZE];

	if (fmt == NULL)
		return (-1);

	va_start(arglist, fmt);

	for (count = 0; fmt && fmt[count] != '\0'; count++)
	{
		if (fmt[count] != '%')
		{
			buffer[buff_ind++] = fmt[count];
			if (buff_ind == BUFF_SIZE)
				print_buffer(buffer, &buff_ind);
			/* write(1, &fmt[i], 1);*/
			printed_chars++;
		}
		else
		{
			print_buffer(buffer, &buff_ind);
			flags = get_flags(fmt, &count);
			width = get_width(format, &count, list);
			precision = get_precision(fmt, &count, arglist);
			size = get_size(fmt, &count);
			++i;
			printed = handle_print(fmt, &count, arglist, buffer,
				flags, width, precision, size);
			if (printed == -1)
				return (-1);
			printed_chars += printed;
		}
	}

	print_buffer(buffer, &buff_ind);

	va_end(arglist);

	return (printed_chars);
}

/**
 * print_buffer - print out content of the buffer(that if it exist 
 * @buffer: Array of chars
 * @buff_ind: Index at which to add next char, represents the length.
 */
void print_buffer(char buffer[], int *buff_ind)
{
	if (*buff_ind > 0)
		write(1, &buffer[0], *buff_ind);

	*buff_ind = 0;
}
