// ds_stack.h
// create by lq on 2018/11/17
//

#ifndef DSSTACK_H_INCLUDE_
#define DSSTACK_H_INCLUDE_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stddef.h>
#include "ds_types.h"

    typedef struct DsStack DsStack;

    DS_API DsStack *ds_stack_create(size_t);

    DS_API DS_STATUS ds_stack_push(DsStack *, void *);

    DS_API DS_STATUS ds_stack_pop(DsStack *, void **);

    DS_API int ds_stack_counts(DsStack *);

    DS_API DS_STATUS ds_stack_clear(DsStack *);

    DS_API void ds_stack_destroy(DsStack **);

#ifdef __cplusplus
}
#endif

#endif // DSSTACK_H_INCLUDE_
