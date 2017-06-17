#include <stdio.h>
#include <stdlib.h>
#include "jval.h"
#include "jrb.h"

int main()
{
    Jval a;
    a = new_jval_i(5);

    printf("Hello world! %d\n",jval_i(a));
    return 0;
}
