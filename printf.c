#include "main.h"

void print_buffer(char buffer[], int *buffer_index);

/**
 * _printf - prints array of characters
 * @format: format.
 * Return: characters
 */
int _printf(const char *format, ...)
{
	int i, x_print = 0, y_print = 0;
	int flags, width, precision, size, buffer_index = 0;
	va_list arglist;
	char buffer[BUFF_SIZE];

	if (format == NULL)
		return (-1);

	va_start(arglist, format);

	for (i = 0; format && format[i] != '\0'; i++)
	{
		if (format[i] != '%')
		{
			buffer[buffer_index++] = format[i];
			if (buffer_index == BUFF_SIZE)
				print_buffer(buffer, &buffer_index);
			/* write(1, &format[i], 1);*/
			y_print++;
		}
		else
		{
			print_buffer(buffer, &buffer_index);
			flags = get_flags(format, &i);
			width = get_width(format, &i, arglist);
			precision = get_precision(format, &i, arglist);
			size = get_size(format, &i);
			++i;
			x_print = handle_print(format, &i, arglist, buffer,
				flags, width, precision, size);
			if (x_print == -1)
				return (-1);
			y_print += x_print;
		}
	}

	print_buffer(buffer, &buffer_index);

	va_end(arglist);

	return (y_print);
}

/**
 * print_buffer - Prints the contents of the buffer if it exist
 * @buffer: an array of characters
 * @buffer_index: Index at which to add next char, represents the length.
 */
void print_buffer(char buffer[], int *buffer_index)
{
	if (*buffer_index > 0)
		write(1, &buffer[0], *buffer_index);

	*buffer_index = 0;
}

