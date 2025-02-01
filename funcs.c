#include "./main.h"

int _putchar(char c)
{
    return write(1, &c, 1);
}

int _puts(char *str, char *buffer, int *index)
{
    int count = 0;

    while (*str)
    {
        count += append_buffer(buffer, *str, index);
        str++;
    }
    return count;
}

int print_number(long n, char *buffer, int *index)
{
    int count = 0;
    if (n < 0)
    {
        count += append_buffer(buffer, '-', index);
        n = -n;
    }
    if (n / 10)
    {
        count += print_number(n / 10, buffer, index);
    }
    count += append_buffer(buffer, (n % 10) + '0', index);
    return count;
}

int print_binary(unsigned long n, char *buffer, int *index)
{
    int count = 0, i = 0;
    int binary[64];
    if (n == 0)
    {
        return append_buffer(buffer, '0', index);
    }
    while (n > 0)
    {
        binary[i++] = n % 2;
        n /= 2;
    }
    while (--i >= 0)
    {
        count += append_buffer(buffer, binary[i] + '0', index);
    }
    return count;
}

int print_unsigned(unsigned long n, char *buffer, int *index)
{
    int count = 0;
    if (n / 10)
    {
        count += print_unsigned(n / 10, buffer, index);
    }
    count += append_buffer(buffer, (n % 10) + '0', index);
    return count;
}

int print_octal(unsigned long n, char *buffer, int *index)
{
    int count = 0, i = 0;
    int octal[64];
    if (n == 0)
    {
        return append_buffer(buffer, '0', index);
    }
    while (n > 0)
    {
        octal[i++] = n % 8;
        n /= 8;
    }
    while (--i >= 0)
    {
        count += append_buffer(buffer, octal[i] + '0', index);
    }
    return count;
}

int print_hex(unsigned long n, char *buffer, int *index, int uppercase)
{
    int count = 0, i = 0;
    char hex[64];
    if (n == 0)
    {
        return append_buffer(buffer, '0', index);
    }
    while (n > 0)
    {
        int remainder = n % 16;
        hex[i++] = remainder < 10 ? remainder + '0' : remainder - 10 + (uppercase ? 'A' : 'a');
        n /= 16;
    }
    while (--i >= 0)
    {
        count += append_buffer(buffer, hex[i], index);
    }
    return count;
}


int print_special_string(char *str, char *buffer, int *index)
{
    int count = 0;
    while (*str)
    {
        if (*str >= 32 && *str < 127)
        {
            count += append_buffer(buffer, *str, index);
        }
        else
        {
            count += append_buffer(buffer, '\\', index);
            count += append_buffer(buffer, 'x', index);
            count += print_hex(*str, buffer, index, 1);
        }
        str++;
    }
    return count;
}


int append_buffer(char *buffer, char c, int *index)
{
    buffer[*index] = c;
    (*index)++;
    if(*index == 1024)
    {
        flush_buffer(buffer, index);
    }
    return 1;
}

void flush_buffer(char *buffer, int *index)
{
    write(1, buffer, *index);
    *index = 0;
}

int handle_length_modifier(char specifier, va_list args, char *buffer, int *index, char length)
{
    if (length == 'l')
    {
        switch (specifier)
        {
        case 'd': case 'i':
            return print_number(va_arg(args, long), buffer, index);
            break;
        case 'u':
            return print_unsigned(va_arg(args, unsigned long), buffer, index);
            break;
        case 'o':
            return print_octal(va_arg(args, unsigned long), buffer, index);
            break;
        case 'x':
            return print_hex(va_arg(args, unsigned long), buffer, index, 0);
            break;
        case 'X':
            return print_hex(va_arg(args, unsigned long), buffer, index, 1);
            break;
        }
    }
    else if (length == 'h')
    {
        switch (specifier)
        {
        case 'd': case 'i':
            return print_number((short)va_arg(args, int), buffer, index);
            break;
        case 'u':
            return print_unsigned((unsigned short)va_arg(args, int), buffer, index);
            break;
        case 'o':
            return print_octal((unsigned short)va_arg(args, int), buffer, index);
            break;
        case 'x':
            return print_hex((unsigned short)va_arg(args, int), buffer, index, 0);
            break;
        case 'X':
            return print_hex((unsigned short)va_arg(args, int), buffer, index, 1);
            break;
        }
    }
    return 0;
}

/*
int _puts(char *str)
{
    int count = 0;

    while(str[count] != '\0')
    {
        _putchar(str[count]);
        count++;
    }

    return count;
}

int print_number(int n)
{
    int count = 0;
    
    if(n < 0)
    {
        n = -n;
        count += _putchar('-');
    }

    if(n == 0)
    {
        count += _putchar('0');
    }

    if(n/10)
    {
        count += print_number(n/10);
    }

    count += _putchar(n%10 + '0');

    return count;
}


int print_binary(int n)
{
    int count = 0;
    int i = 0;
    int binary[32];

    if(n == 0)
    {
        count += _putchar('0');
    }

    while(n > 0)
    {
        binary[i] = n % 2;
        n = n / 2;
        i++;
    }

    i--;

    while(i >= 0)
    {
        count += _putchar(binary[i] + '0');
        i--;
    }

    return count;
}

int print_unsigned(unsigned int n)
{
    int count = 0;

    if(n == 0)
    {
        count += _putchar('0');
    }

    if(n/10)
    {
        count += print_unsigned(n/10);
    }

    count += _putchar(n%10 + '0');

    return count;
}

int print_octal(unsigned int n)
{
    int count = 0;
    int i = 0;
    int octal[32];

    if(n == 0)
    {
        count += _putchar('0');
    }

    while(n > 0)
    {
        octal[i] = n % 8;
        n = n / 8;
        i++;
    }

    i--;

    while(i >= 0)
    {
        count += _putchar(octal[i] + '0');
        i--;
    }

    return count;
}

int print_hex(unsigned int n)
{
    int count = 0;
    int i = 0;
    int hex[32];

    if(n == 0)
    {
        count += _putchar('0');
    }

    while(n > 0)
    {
        hex[i] = n % 16;
        n = n / 16;
        i++;
    }

    i--;

    while(i >= 0)
    {
        if(hex[i] < 10)
        {
            count += _putchar(hex[i] + '0');
        }
        else
        {
            count += _putchar(hex[i] - 10 + 'a');
        }
        i--;
    }

    return count;
}

int print_HEX(unsigned int n)
{
    int count = 0;
    int i = 0;
    int hex[32];

    if(n == 0)
    {
        count += _putchar('0');
    }

    while(n > 0)
    {
        hex[i] = n % 16;
        n = n / 16;
        i++;
    }

    i--;

    while(i >= 0)
    {
        if(hex[i] < 10)
        {
            count += _putchar(hex[i] + '0');
        }
        else
        {
            count += _putchar(hex[i] - 10 + 'A');
        }
        i--;
    }

    return count;
}

int print_special_string(char *str)
{
    int count = 0;

    while(*str)
    {
        if(*str >= 32 && *str < 127)
        {
            count += _putchar(*str);
        }
        else
        {
            count += _putchar('\\');
            count += _putchar('x');
            count += print_hex(*str);
        }
        str++;
    }

    return count;
}*/