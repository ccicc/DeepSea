// ds_stack.c
// create by lq on 2018/08/15

#include <stdlib.h>
#include "../include/ds_stack.h"

struct DsStack
{
    size_t size;
    size_t length;
    void** head;
};

DsStack* ds_stack_init(size_t size)
{
    DsStack* stack = (DsStack*)malloc(sizeof(DsStack));
    if(!stack) exit(DS_STATUS_MEMOUT);
    if(size <= 0) size = 10;
    stack->head = (void**)calloc(size, sizeof(void*));
    stack->size = size;
    stack->length = 0;
    return stack;
}

int ds_stack_counts(DsStack* stack)
{
    if(!stack) return DS_STATUS_NULL;
    return stack->length;
}

DS_STATUS ds_stack_push(DsStack* stack, void* data)
{
    if(!stack) return DS_STATUS_NULL;
    if(stack->length >= stack->size)exit(DS_STATUS_FULL);
    stack->head[stack->length++] = data;
    return DS_STATUS_OK;
}

DS_STATUS ds_stack_pop(DsStack* stack, void** data)
{
    if(!stack) return DS_STATUS_NULL;
    if(stack->length <= 0)exit(DS_STATUS_EMPTY);
    *data = stack->head[--stack->length];
    return DS_STATUS_OK;
}

DS_STATUS ds_stack_clear(DsStack* stack)
{
    if(!stack) return DS_STATUS_NULL;
    stack->length = 0;
    return DS_STATUS_OK;
}

void ds_stack_destroy(DsStack** in)
{
    if(*in)
    {
        DsStack* stack = *in;
        free(stack->head);
        free(stack);
        *in = NULL;
    }
}
