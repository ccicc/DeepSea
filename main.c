// main.c
// create by lq on 2018/08/15

#include "include/ds_stack.h"

int main(void)
{
    DsStack* stack = ds_stack_init(0);

    ds_stack_push(stack, "aaa");
    ds_stack_push(stack, "bbb");
    ds_stack_push(stack, "ccc");
    ds_stack_push(stack, "ddd");

    char* str = NULL;
    while((ds_stack_pop(stack, (void**)&str)) == DS_OK)
    {
        fputs(str, stdout);
        fputc('\n', stdout);
    }

    ds_stack_destroy(&stack);
    ds_stack_destroy(&stack);

    getchar();
    return 0;
}
