#include "main.h"
/**
 * handling_print - Prints an argument based on its type
 * @fmt: Formatted string in which to print the arguments.
 * @list: List of arguments to be printed.
 * @ind: current index of formated string
 * @buffer: Buffer array to handle print.
 * @flags: Calculates active flags
 * @width: get width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: 1 or 2;
 */
int handling_print(const char *fmt, int *ind, va_list list, char buffer[],
	int flags, int width, int precision, int size)
{
	int j, unknown_len = 0, printed_chars = -1;
	fmt_t fmt_types[] = {
		{'c', printing_char}, {'s', printing_string}, {'%', printing_percent},
		{'i', printing_int}, {'d', printing_int}, {'b', printing_binary},
		{'u', print_of_unsigned}, {'o', print_of_octal}, {'x', print_of_hexadecimal},
		{'X', print_of_hexa_upper},
		{'p', print_a_pointer}, {'S', print_a_non_printable},
		{'r', print_in_reverse}, {'R', printing_rot13string}, {'\0', NULL}
	};
	for (j = 0; fmt_types[j].fmt != '\0'; j++)
		if (fmt[*ind] == fmt_types[j].fmt)
			return (fmt_types[j].fn(list, buffer, flags, width, precision, size));

	if (fmt_types[j].fmt == '\0')
	{
		if (fmt[*ind] == '\0')
			return (-1);
		unknown_len += write(1, "%%", 1);
		if (fmt[*ind - 1] == ' ')
			unknown_len += write(1, " ", 1);
		else if (width)
		{
			--(*ind);
			while (fmt[*ind] != ' ' && fmt[*ind] != '%')
				--(*ind);
			if (fmt[*ind] == ' ')
				--(*ind);
			return (1);
		}
		unknown_len += write(1, &fmt[*ind], 1);
		return (unknown_len);
	}
	return (printed_chars);
}
