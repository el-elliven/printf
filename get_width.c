#include "main.h"

/**
 * get_width - Calculates the width for printing
 * @format: place holder to print arguments.
 * @i: List of arguments to be printed.
 * @list: list of arguments.
 *
 * Return: width.
 */
int get_width(const char *format, int *i, va_list list)
{
	int current_arg;
	int width = 0;

	for (current_arg = *i + 1; format[current_arg] != '\0'; current_arg++)
	{
		if (is_digit(format[current_arg]))
		{
			width *= 10;
			width += format[current_arg] - '0';
		}
		else if (format[current_arg] == '*')
		{
			current_arg++;
			width = va_arg(list, int);
			break;
		}
		else
			break;
	}

	*i = current_arg - 1;

	return (width);
}
