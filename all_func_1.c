#include "main.h"

/************************* PRINT OF CHAR *************************/

/**
 * print_char - Prints a char
 * @types: List a of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: minimum width of printed char
 * @precision: Precision specification printed char
 * @size: Size specifier of printed char
 * Return: Number of chars printed
 */
int printing_char(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char b = va_arg(types, int);

	return (handle_the_write_char(b, buffer, flags, width, precision, size));
}
/************************* PRINT OF A STRING *************************/
/**
 * printing_string - Prints a string
 * @types: List a of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width of printed string.
 * @precision: Precision specification
 * @size: Size specifier of printed string
 * Return: Number of chars printed
 */
int printing_string(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int length = 0, k;
	char *str = va_arg(types, char *);

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	if (str == NULL)
	{
		str = "(null)";
		if (precision >= 6)
			str = "      ";
	}

	while (str[length] != '\0')
		length++;

	if (precision >= 0 && precision < length)
		length = precision;

	if (width > length)
	{
		if (flags & F_MINUS)
		{
			write(1, &str[0], length);
			for (k = width - length; k > 0; k--)
				write(1, " ", 1);
			return (width);
		}
		else
		{
			for (k = width - length; k > 0; k--)
				write(1, " ", 1);
			write(1, &str[0], length);
			return (width);
		}
	}

	return (write(1, str, length));
}
/************************* PRINT A PERCENT SIGN *************************/
/**
 * printing_percent - Prints a percent sign
 * @types: Lista of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width of printed a percent sign.
 * @precision: Precision specification
 * @size: Size specifier of percent sign.
 * Return: Number of chars printed
 */
int printing_percent(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	UNUSED(types);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	return (write(1, "%%", 1));
}

/************************* PRINTING INT *************************/
/**
 * printing_int - Print int
 * @types: Lista of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width of printed int.
 * @precision: Precision specification
 * @size: Size specifier of printed in
 * Return: Number of chars printed
 */
int printing_int(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int k = BUFF_SIZE - 2;
	int is_negative = 0;
	long int m = va_arg(types, long int);
	unsigned long int num;

	m = convert_the_size_number(m, size);

	if (m == 0)
		buffer[k--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';
	num = (unsigned long int)m;

	if (m < 0)
	{
		num = (unsigned long int)((-1) * m);
		is_negative = 1;
	}

	while (num > 0)
	{
		buffer[k--] = (num % 10) + '0';
		num /= 10;
	}

	k++;

	return (write_the_number(is_negative, k, buffer,
				 flags, width, precision, size));
}

/************************* PRINTING BINARY *************************/
/**
 * printing_binary - Prints an unsigned number
 * @types: List of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Numbers of char printed.
 */
int printing_binary(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	unsigned int s, t, k, sum;
	unsigned int a[32];
	int count;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	s = va_arg(types, unsigned int);
	t = 2147483648; /* (2 ^ 31) */
	a[0] = s / t;
	for (k = 1; k < 32; k++)
	{
		t /= 2;
		a[k] = (s / t) % 2;
	}
	for (k = 0, sum = 0, count = 0; k < 32; k++)
	{
		sum += a[k];
		if (sum || k == 31)
		{
			char y = '0' + a[k];

			write(1, &y, 1);
			count++;
		}
	}
	return (count);
}
