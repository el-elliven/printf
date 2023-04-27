#include "main.h"

/**
 * get_size - generate the size to cast the an argument
 * @format: place holder to print arguments
 * @i: arguments to be printed.
 *
 * Return: size_is.
 */
int get_size(const char *format, int *i)
{
	int current_arg = *i + 1;
	int size_is = 0;

	if (format[current_arg] == 'l')
		size_is = S_LONG;
	else if (format[current_arg] == 'h')
		size_is = S_SHORT;

	if (size_is == 0)
		*i = current_arg - 1;
	else
		*i = current_arg;

	return (size_is);
}
