// ds_stack.c
// create by lq on 2018/11/17
//

#include <stdlib.h>
#include <string.h>
#include "./../include/ds_stack.h"

struct DS_STACK
{
    size_t max;
    int index;
    void** elems;
};

DS_STACK* ds_stack_create(size_t size)
{
    DS_STACK* stack = (DS_STACK*)malloc(sizeof(DS_STACK));
    memset(stack, 0, sizeof(DS_STACK));
    if(NULL == stack)
        exit(DS_STATUS_OUTMEM);
    if(size <= 0) size = 16;
    stack->elems = (void**)malloc(sizeof(void**));
    if(NULL == stack->elems)
        exit(DS_STATUS_OUTMEM);
    stack->max = size;
    stack->index = 0;
    return stack;
}

DS_STATUS ds_stack_push(DS_STACK* stack, void* data)
{
    if(NULL == stack)
        return DS_STATUS_NULL;
    if(stack->index >= stack->max)
        return DS_STATUS_FULL;
    stack->elems[stack->index++] = data;
    return DS_STATUS_OK;
}

DS_STATUS ds_stack_pop(DS_STACK* stack, void** data)
{
    if(NULL == stack)
        return DS_STATUS_NULL;
    if(stack->index <= 0)
        return DS_STATUS_EMPTY;
    if(data)
        *data = stack->elems[--stack->index];
    return DS_STATUS_OK;
}

int ds_stack_counts(DS_STACK *stack)
{
    return stack->index;
}

DS_STATUS ds_stack_clear(DS_STACK* stack)
{
    if(NULL == stack)
        return DS_STATUS_NULL;
    stack->index = 0;
    return DS_STATUS_OK;
}

void ds_stack_destroy(DS_STACK **in)
{
    if(NULL != *in)
    {
        DS_STACK* stack = *in;
        free(stack->elems);
        free(stack);
        *in = NULL;
    }
}
