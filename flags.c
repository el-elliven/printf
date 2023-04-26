#include "main.h"

/**
 * get_the_flags - Calculates active flags
 * @format: Formatted string in which to print the arguments
 * @i: take a parameter.
 * Return: Flags:
 */
int get_the_flags(const char *format, int *i)
{
	/* - + 0 # ' ' */
	/* 1 2 4 8  16 */
	int b, curr;
	int flags = 0;
	const char FLAGS_CH[] = {'-', '+', '0', '#', ' ', '\0'};
	const int FLAGS_ARR[] = {F_MINUS, F_PLUS, F_ZERO, F_HASH, F_SPACE, 0};

	for (curr = *i + 1; format[curr] != '\0'; curr++)
	{
		for (b = 0; FLAGS_CH[b] != '\0'; b++)
			if (format[curr] == FLAGS_CH[b])
			{
				flags |= FLAGS_ARR[b];
				break;
			}

		if (FLAGS_CH[b] == 0)
			break;
	}

	*i = curr - 1;

	return (flags);
}
