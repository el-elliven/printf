#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>

/** void and memory **/
#define UNUSED(x) (void)(x)
#define BUFF_SIZE 1024

/** flags used in code **/
#define F_MINUS 1
#define F_PLUS 2
#define F_ZERO 4
#define F_HASH 8
#define F_SPACE 16

/** sizes of characters used in the code **/
#define S_LONG 2
#define S_SHORT 1

/**
 * struct fmt - Struct op
 *
 * @fmt: The format.
 * @fn: The function associated.
 */
struct fmt
{
	char fmt;
	int (*fn)(va_list, char[], int, int, int, int);
};


/**
 * typedef struct fmt fmt_t - Struct op
 *
 * @fmt: The format.
 * @fm_t: The function associated.
 */
typedef struct fmt fmt_t;

int _printf(const char *format, ...);
int handling_print(const char *fmt, int *i,
va_list list, char buffer[], int flags, int width, int precision, int size);

/******* Declaration of all the functions *********/

/*** Funtions for printing of characters and strings ***/
int printing_char(va_list types, char buffer[],
	int flags, int width, int precision, int size);
int printing_string(va_list types, char buffer[],
	int flags, int width, int precision, int size);
int printing_percent(va_list types, char buffer[],
	int flags, int width, int precision, int size);

/*** Functions for printing all digit types ***/
int printing_int(va_list types, char buffer[],
	int flags, int width, int precision, int size);
int printing_binary(va_list types, char buffer[],
	int flags, int width, int precision, int size);
int print_of_unsigned(va_list types, char buffer[],
	int flags, int width, int precision, int size);
int print_of_octal(va_list types, char buffer[],
	int flags, int width, int precision, int size);
int print_of_hexadecimal(va_list types, char buffer[],
	int flags, int width, int precision, int size);
int print_of_hexa_upper(va_list types, char buffer[],
	int flags, int width, int precision, int size);

int print_hexa_lu(va_list types, char map_to[],
char buffer[], int flags, char flag_ch, int width, int precision, int size);

/*** Function for printing the non printable type characters ***/
int print_a_non_printable(va_list types, char buffer[],
	int flags, int width, int precision, int size);

/*** Funcion for printing memory address ***/
int print_a_pointer(va_list types, char buffer[],
	int flags, int width, int precision, int size);

/*** Funcitions for handling other specifiers ***/
int get_the_flags(const char *format, int *i);
int get_the_width(const char *format, int *i, va_list list);
int get_the_precision(const char *format, int *i, va_list list);
int get_the_size(const char *format, int *i);

/*** Function for printing string in reverse ***/
int print_in_reverse(va_list types, char buffer[],
	int flags, int width, int precision, int size);

/*** Function for printing a string in rot 13 ***/
int printing_rot13string(va_list types, char buffer[],
	int flags, int width, int precision, int size);

/*** width handler ***/
int handle_the_write_char(char c, char buffer[],
	int flags, int width, int precision, int size);
int write_the_number(int is_positive, int ind, char buffer[],
	int flags, int width, int precision, int size);
int write_the_num(int ind, char bff[], int flags, int width, int precision,
	int length, char padd, char extra_c);
int write_the_pointer(char buffer[], int ind, int length,
	int width, int flags, char padd, char extra_c, int padd_start);

int write_the_unsgnd(int is_negative, int ind,
char buffer[],
	int flags, int width, int precision, int size);

/****************** utils ******************/
int is_char_printable(char);
int append_the_hexa_code(char, char[], int);
int is_the_digit(char);

long int convert_the_size_number(long int num, int size);
long int convert_the_size_unsgnd(unsigned long int num, int size);

#endif /* MAIN_H */
