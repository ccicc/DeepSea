// ds_stack.h
// create by lq on 2018/11/17
//

#ifndef DSSTACK_H_INCLUDE_
#define DSSTACK_H_INCLUDE_

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include "ds_types.h"

typedef struct DS_STACK DS_STACK;

DS_API DS_STACK* ds_stack_create(size_t);

DS_API DS_STATUS ds_stack_push(DS_STACK*, void*);

DS_API DS_STATUS ds_stack_pop(DS_STACK*, void**);

DS_API int ds_stack_counts(DS_STACK*);

DS_API DS_STATUS ds_stack_clear(DS_STACK*);

DS_API void ds_stack_destroy(DS_STACK**);

#ifdef __cplusplus
}
#endif

#endif  // DSSTACK_H_INCLUDE_