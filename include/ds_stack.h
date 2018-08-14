// d_stack.h
// create by lq on 2018/08/15

#ifndef DS_STACK_H_
#define DS_STACK_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include "ds_types.h"

typedef struct DsStack DsStack;

DS_API DsStack* ds_stack_init(size_t);

DS_API int ds_stack_push(DsStack*, void*);

DS_API int ds_stack_pop(DsStack*, void**);

DS_API void ds_stack_destroy(DsStack**);

#ifdef __cplusplus
}
#endif

#endif // DS_STACK_H_