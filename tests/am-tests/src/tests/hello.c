#include <amtest.h>

void hello()
{
    int *p = (int *)0x12569ae8;

    printf("p:%p p:%p\n", p, p+1);

    for (int i = 0; i < 10; i++)
    {
        putstr("Hello, AM World @ " __ISA__ "\n");
    }
}
