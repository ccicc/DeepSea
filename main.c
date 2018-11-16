// main.c
// create by lq on 2018/11/17
//

#include <stdio.h>
#include <stdlib.h>
#include "include/ds_stack.h"

int main(void)
{
    DS_STACK *stack = ds_stack_create(0);

    ds_stack_push(stack, "aa");
    ds_stack_push(stack, "bb");
    ds_stack_push(stack, "cc");

    char* str = NULL;

    while(DS_STATUS_OK == ds_stack_pop(stack, (void**)&str))
        printf("str = %s\n", str);
    
    ds_stack_destroy(&stack);

    getchar();
    return 0;
}
