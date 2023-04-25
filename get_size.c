#include "main.h"

/**
 * get_size - Calculates the size to cast the argument
 * @var_fmt: Formatted string in which to print the arguments
 * @i: List of arguments to be printed.
 *
 * Return: Precision.
 */
int get_size(const char *var_fmt, int *i)
{
	int k = *i + 1;
	int size = 0;

	if (var_fmt[k] == 'l')
		size = S_LONG;
	else if (var_fmt[k] == 'h')
		size = S_SHORT;

	if (size == 0)
		*i = k - 1;
	else
		*i = k;

	return (size);
}
