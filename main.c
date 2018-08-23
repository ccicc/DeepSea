// main.c
// create by lq on 2018/08/15

#include <ds_stack.h>

int main(void)
{
    DsStack* stack = ds_stack_init(0);

    ds_stack_push(stack, "aaa");
    ds_stack_push(stack, "bbb");
    ds_stack_push(stack, "ccc");
    ds_stack_push(stack, "ddd");

    printf("counts = %d\n", ds_stack_counts(stack));

    char* str;
    int res;
    while((res = ds_stack_pop(stack, (void**)&str)) == DS_STATUS_OK)
    {
        printf("str = %s\n", str);
    }
    
    return 0;
}
