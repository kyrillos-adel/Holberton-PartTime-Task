#ifndef _MAIN_H_
#define _MAIN_H_

#include <stdarg.h>
#include <unistd.h>
#include <stdlib.h>

int _printf(const char *format, ...);
int _putchar(char c);

int _puts(char *str, char *buffer, int *index);
int print_number(long n, char *buffer, int *index);
int print_binary(unsigned long n, char *buffer, int *index);
int print_unsigned(unsigned long n, char *buffer, int *index);
int print_octal(unsigned long n, char *buffer, int *index);
int print_hex(unsigned long n, char *buffer, int *index, int uppercase);
int print_special_string(char *str, char *buffer, int *index);

int append_buffer(char *buffer, char c, int *index);
void flush_buffer(char *buffer, int *index);

int handle_length_modifier(char specifier, va_list args, char *buffer, int *index, char length);

/*
int _puts(char *str);
int print_number(int n);
int print_binary(int n);
int print_unsigned(unsigned int n);
int print_octal(unsigned int n);
int print_hex(unsigned int n);
int print_HEX(unsigned int n);
int print_special_string(char *str);
*/


#endif /* _MAIN_H_ */