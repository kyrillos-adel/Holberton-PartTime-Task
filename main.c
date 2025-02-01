#include <stdio.h>
#include "./main.h"

int main()
{
    int x = _printf("Hello, World!%x\n", 123);
    int y = printf("Hello, World!%X\n", 123);
    printf("%d\n%d", x, y);
    return 0; 
}
