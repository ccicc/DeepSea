// ds_types.h
// create by lq on 2018/08/15

#ifndef DS_TYPES_H_
#define DS_TYPES_H_

#ifdef __cplusplus
extern "C" {
#endif

#define DS_API          extern
#define DS_TRUE         (1)
#define DS_FALSE        (0)

typedef enum {
    DS_STATUS_OK,
    DS_STATUS_MEMOUT,
    DS_STATUS_FULL,
    DS_STATUS_EMPTY,
    DS_STATUS_NULL
} DS_STATUS;

#ifdef __cplusplus
}
#endif

#endif // DS_TYPES_H_