#include "main.h"

/**
 * flag_func - gets the number of flags
 * @var_fmt: Formatted string in which to print the arguments
 * @i: take a parameter.
 * Return: Flags:
 */
int flag_func(const char *var_fmt, int *i)
{
	/* - + 0 # ' ' */
	/* 1 2 4 8  16 */
	int j, k;
	int flags = 0;
	const char FLAGS_CH[] = {'-', '+', '0', '#', ' ', '\0'};
	const int FLAGS_ARR[] = {F_MINUS, F_PLUS, F_ZERO, F_HASH, F_SPACE, 0};

	for (k = *i + 1; var_fmt[k] != '\0'; k++)
	{
		for (j = 0; FLAGS_CH[j] != '\0'; j++)
			if (var_fmt[k] == FLAGS_CH[j])
			{
				flags |= FLAGS_ARR[j];
				break;
			}

		if (FLAGS_CH[j] == 0)
			break;
	}

	*i = k - 1;

	return (flags);
}
