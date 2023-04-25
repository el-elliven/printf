#include "main.h"

/**
 * get_precision - Calculates the precision for printing
 * @var_fmt: Formatted string in which to print the arguments
 * @i: List of arguments to be printed.
 * @list: list of arguments.
 *
 * Return: Precision.
 */
int get_precision(const char *var_fmt, int *i, va_list list)
{
	int k = *i + 1;
	int precision = -1;

	if (var_fmt[k] != '.')
		return (precision);

	precision = 0;

	for (k += 1; var_fmt[k] != '\0'; k++)
	{
		if (is_digit(var_fmt[k]))
		{
			precision *= 10;
			precision += var_fmt[k] - '0';
		}
		else if (var_fmt[k] == '*')
		{
			k++;
			precision = va_arg(list, int);
			break;
		}
		else
			break;
	}

	*i = k - 1;

	return (precision);
}
