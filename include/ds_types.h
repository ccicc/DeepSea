// ds_types.h
// create by lq on 2018/11/17
//

#ifndef DSTYPES_H_INCLUDE_
#define DSTYPES_H_INCLUDE_

#ifdef __cplusplus
extern "C" {
#endif

#define DS_API extern
#define DS_MAXCHAR (2 << 7)
#define DS_TRUE (1)
#define DS_FALSE (0)

typedef int DS_BOOL;
typedef enum {
    DS_STATUS_OK,
    DS_STATUS_NULL,
    DS_STATUS_OUTMEM,
    DS_STATUS_FULL,
    DS_STATUS_EMPTY
} DS_STATUS;

#ifdef __cplusplus
}
#endif

#endif // DSTYPES_H_INCLUDE_