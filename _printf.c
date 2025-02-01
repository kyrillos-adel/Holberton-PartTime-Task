#include "main.h"

#include "main.h"

int _printf(const char *format, ...)
{
    char buffer[1024];
    int index = 0;
    int number_of_characters = 0;
    int i;
    va_list args;
    char length = 'h'; /* default length modifier (Short) */

    if (!format || (format[0] == '%' && format[1] == '\0'))
        return -1;

    va_start(args, format);

    for (i = 0; format[i] != '\0'; i++)
    {
        if (format[i] == '%')
        {
            i++;
            if (format[i] == 'l' || format[i] == 'h')
            {
                length = format[i];
                i++;
            }
            switch (format[i])
            {
                case 'c':
                    number_of_characters += append_buffer(buffer, va_arg(args, int), &index);
                    break;
                case 's':
                {
                    char *str = va_arg(args, char *);
                    if (!str) str = "(null)";
                    while (*str)
                        number_of_characters += append_buffer(buffer, *str++, &index);
                    break;
                }
                case '%':
                    number_of_characters += append_buffer(buffer, '%', &index);
                    break;
                case 'd': case 'i': case 'u': case 'o': case 'x': case 'X':
                    number_of_characters += handle_length_modifier(format[i], args, buffer, &index, length);
                    break;
                default:
                    number_of_characters += append_buffer(buffer, '%', &index);
                    number_of_characters += append_buffer(buffer, format[i], &index);
            }
        }
        else
        {
            number_of_characters += append_buffer(buffer, format[i], &index);
        }
    }

    va_end(args);
    flush_buffer(buffer, &index);
    return number_of_characters;
}



/*
int _printf(const char *format, ...)
{
    unsigned int no_of_characters = 0;
    unsigned int i;

    va_list args;
    va_start(args, format);

    for(i = 0; format[i] != '\0'; i++)
    {
        if(!format || (format[i] == '%' && format[i+1] == '\0'))
        {
            return -1;
        }
        if(format[i] == '%')
        {
            i++;
            switch(format[i])
            {
                case 'c':
                    no_of_characters += _putchar(va_arg(args, int));
                    break;
                case 's':
                    no_of_characters += _puts(va_arg(args, char *));
                    break;
                case '%':
                    no_of_characters += _putchar('%');
                    break;
                case 'd':
                    no_of_characters += print_number(va_arg(args, int));
                    break;
                case 'i':
                    no_of_characters += print_number(va_arg(args, int));
                    break;
                case 'b':
                    no_of_characters += print_binary(va_arg(args, int));
                    break;
                case 'u':
                    no_of_characters += print_unsigned(va_arg(args, unsigned int));
                    break;
                case 'o':
                    no_of_characters += print_octal(va_arg(args, unsigned int));
                    break;
                case 'x':
                    no_of_characters += print_hex(va_arg(args, unsigned int));
                    break;
                case 'X':
                    no_of_characters += print_HEX(va_arg(args, unsigned int));
                    break;
                default:
                    no_of_characters += _putchar('%');
                    no_of_characters += _putchar(format[i]);
            }
        }
        else if(format[i] != '%')    
        {
            no_of_characters += _putchar(format[i]);
        }
    }

    va_end(args);
    return no_of_characters;
}*/