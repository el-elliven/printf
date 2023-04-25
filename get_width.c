#include "main.h"

/**
 * get_width - Calculates the width for printing
 * @var_fmt: Formatted string in which to print the arguments.
 * @i: List of arguments to be printed.
 * @list: list of arguments.
 *
 * Return: width.
 */
int get_width(const char *var_fmt, int *i, va_list list)
{
	int k;
	int width = 0;

	for (k = *i + 1; var_fmt[k] != '\0'; k++)
	{
		if (is_digit(var_fmt[k]))
		{
			width *= 10;
			width += var_fmt[k] - '0';
		}
		else if (var_fmt[k] == '*')
		{
			k++;
			width = va_arg(list, int);
			break;
		}
		else
			break;
	}

	*i = k - 1;

	return (width);
}
