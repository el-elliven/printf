#include "main.h"

/**
 * get_precision - Calculates the precision for printing
 * @format: place holder to print arguments
 * @i: List of arguments to be printed.
 * @list: list of arguments.
 *
 * Return: Precision.
 */
int get_precision(const char *format, int *i, va_list list)
{
	int current_arg = *i + 1;
	int precision = -1;

	if (format[current_arg] != '.')
		return (precision);

	precision = 0;

	for (current_arg += 1; format[current_arg] != '\0'; current_arg++)
	{
		if (is_digit(format[current_arg]))
		{
			precision *= 10;
			precision += format[current_arg] - '0';
		}
		else if (format[current_arg] == '*')
		{
			current_arg++;
			precision = va_arg(list, int);
			break;
		}
		else
			break;
	}

	*i = current_arg - 1;

	return (precision);
}
