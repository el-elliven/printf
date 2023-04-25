#include "main.h"

/************************* WRITE HANDLE *************************/
/**
 * handle_write_char - Prints a string
 * @c: char types.
 * @buffer: Buffer array to handle print
 * @flags:  gets the number of flags.
 * @width: get width.
 * @precision: precision specifier
 * @size: specifies size
 *
 * Return: Number of chars printed.
 */
int handle_write_char(char c, char buffer[],
	int flags, int width, int precision, int size)
{ /* char is stored at left and paddinging at buffer's right */
	int i = 0;
	char padding = ' ';

	UNUSED(precision);
	UNUSED(size);

	if (flags & F_ZERO)
		padding = '0';

	buffer[i++] = c;
	buffer[i] = '\0';

	if (width > 1)
	{
		buffer[BUFF_SIZE - 1] = '\0';
		for (i = 0; i < width - 1; i++)
			buffer[BUFF_SIZE - i - 2] = padding;

		if (flags & F_MINUS)
			return (write(1, &buffer[0], 1) +
					write(1, &buffer[BUFF_SIZE - i - 1], width - 1));
		else
			return (write(1, &buffer[BUFF_SIZE - i - 1], width - 1) +
					write(1, &buffer[0], 1));
	}

	return (write(1, &buffer[0], 1));
}

/************************* WRITE NUMBER *************************/
/**
 * write_num - Prints a string
 * @is_negative: for list of arguments
 * @index: char types.
 * @buffer: Buffer array to handle print
 * @flags:  gets the number of flags
 * @width: get width.
 * @precision: precision specifier
 * @size: specifies size
 *
 * Return: Number of chars printed.
 */
int write_num(int is_negative, int index, char buffer[],
	int flags, int width, int precision, int size)
{
	int length = BUFF_SIZE - index - 1;
	char padding = ' ', xtra_ch = 0;

	UNUSED(size);

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padding = '0';
	if (is_negative)
		xtra_ch = '-';
	else if (flags & F_PLUS)
		xtra_ch = '+';
	else if (flags & F_SPACE)
		xtra_ch = ' ';

	return (write_num(index, buffer, flags, width, precision,
		length, padding, xtra_ch));
}

/**
 * write_num - Write a number using a bufffer
 * @index: Index at which the number starts on the buffer
 * @buffer: Buffer
 * @flags: Flags
 * @width: width
 * @prec: Precision specifier
 * @length: Number length
 * @padding: Pading char
 * @xtra_c: Extra char
 *
 * Return: Number of printed chars.
 */
int write_num(int index, char buffer[],
	int flags, int width, int prec,
	int length, char padding, char xtra_c)
{
	int i, padding_st = 1;

	if (prec == 0 && index == BUFF_SIZE - 2 && buffer[index] == '0' && width == 0)
		return (0); /* printf(".0d", 0)  no char is printed */
	if (prec == 0 && index == BUFF_SIZE - 2 && buffer[index] == '0')
		buffer[index] = padding = ' '; /* width is displayed with paddinging ' ' */
	if (prec > 0 && prec < length)
		padding = ' ';
	while (prec > length)
		buffer[--index] = '0', length++;
	if (xtra_c != 0)
		length++;
	if (width > length)
	{
		for (i = 1; i < width - length + 1; i++)
			buffer[i] = padding;
		buffer[i] = '\0';
		if (flags & F_MINUS && padding == ' ')/* Asign extra char to left of buffer */
		{
			if (xtra_c)
				buffer[--index] = xtra_c;
			return (write(1, &buffer[index], length) + write(1, &buffer[1], i - 1));
		}
		else if (!(flags & F_MINUS) && padding == ' ')/* extra char to left of buff */
		{
			if (xtra_c)
				buffer[--index] = xtra_c;
			return (write(1, &buffer[1], i - 1) + write(1, &buffer[index], length));
		}
		else if (!(flags & F_MINUS) && padding == '0')/* extra char to left of padding */
		{
			if (xtra_c)
				buffer[--padding_st] = xtra_c;
			return (write(1, &buffer[padding_st], i - padding_st) +
				write(1, &buffer[index], length - (1 - padding_st)));
		}
	}
	if (xtra_c)
		buffer[--index] = xtra_c;
	return (write(1, &buffer[index], length));
}

/**
 * write_unsigned - Writes an unsigned number
 * @is_negative: Number indexicating if the num is negative
 * @index: Index at which the number starts in the buffer
 * @buffer: Array of chars
 * @flags: Flags specifiers
 * @width: Width specifier
 * @precision: Precision specifier
 * @size: specifies size
 *
 * Return: Number of written chars.
 */
int write_unsigned(int is_negative, int index,
	char buffer[],
	int flags, int width, int precision, int size)
{
	/* The number is stored at the bufer's right and starts at position i */
	int length = BUFF_SIZE - index - 1, i = 0;
	char padding = ' ';

	UNUSED(is_negative);
	UNUSED(size);

	if (precision == 0 && index == BUFF_SIZE - 2 && buffer[index] == '0')
		return (0); /* printf(".0d", 0)  no char is printed */

	if (precision > 0 && precision < length)
		padding = ' ';

	while (precision > length)
	{
		buffer[--index] = '0';
		length++;
	}

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padding = '0';

	if (width > length)
	{
		for (i = 0; i < width - length; i++)
			buffer[i] = padding;

		buffer[i] = '\0';

		if (flags & F_MINUS) /* Asign extra char to left of buffer [buffer>padding]*/
		{
			return (write(1, &buffer[index], length) + write(1, &buffer[0], i));
		}
		else /* Asign extra char to left of paddinging [padding>buffer]*/
		{
			return (write(1, &buffer[0], i) + write(1, &buffer[index], length));
		}
	}

	return (write(1, &buffer[index], length));
}

/**
 * write_pointer - Write a memory address
 * @buffer: Arrays of chars
 * @index: Index at which the number starts in the buffer
 * @length: Length of number
 * @width: Wwidth specifier
 * @flags: Flags specifier
 * @padding: Char representing the paddinging
 * @xtra_c: Char representing extra char
 * @padding_st: Index at which paddinging should start
 *
 * Return: Number of written chars.
 */
int write_pointer(char buffer[], int index, int length,
	int width, int flags, char padding, char xtra_c, int padding_st)
{
	int i;

	if (width > length)
	{
		for (i = 3; i < width - length + 3; i++)
			buffer[i] = padding;
		buffer[i] = '\0';
		if (flags & F_MINUS && padding == ' ')/* Asign extra char to left of buffer */
		{
			buffer[--index] = 'x';
			buffer[--index] = '0';
			if (xtra_c)
				buffer[--index] = xtra_c;
			return (write(1, &buffer[index], length) + write(1, &buffer[3], i - 3));
		}
		else if (!(flags & F_MINUS) && padding == ' ')/* extra char to left of buffer */
		{
			buffer[--index] = 'x';
			buffer[--index] = '0';
			if (xtra_c)
				buffer[--index] = xtra_c;
			return (write(1, &buffer[3], i - 3) + write(1, &buffer[index], length));
		}
		else if (!(flags & F_MINUS) && padding == '0')/* extra char to left of padding */
		{
			if (xtra_c)
				buffer[--padding_st] = xtra_c;
			buffer[1] = '0';
			buffer[2] = 'x';
			return (write(1, &buffer[padding_st], i - padding_st) +
				write(1, &buffer[index], length - (1 - padding_st) - 2));
		}
	}
	buffer[--index] = 'x';
	buffer[--index] = '0';
	if (xtra_c)
		buffer[--index] = xtra_c;
	return (write(1, &buffer[index], BUFF_SIZE - index - 1));
}
