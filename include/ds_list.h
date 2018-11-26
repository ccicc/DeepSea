// ds_list.c
// create by lq on 2018/11/25
//

#ifndef DSLIST_H_INCLUDE_
#define DSLIST_H_INCLUDE_

#include <stddef.h>
#include "ds_types.h"

#ifdef __cplusplus
extern "C"
{
#endif

    typedef DsList DsList;
    typedef DsListIter DsListIter;

    // 创建链表
    DS_API DsList *ds_list_create(void);

    // 创建带有比较函数指针的链表
    DS_API DsList *ds_list_create_equal(DS_BOOL *(void *, void *));

    // 链表长度
    DS_API size_t ds_list_size(DsList *);

    // 插入链表元素
    DS_API DS_STATUS ds_list_insert(DsList *, int, void *);

    // 链首插入元素
    DS_API DS_STATUS ds_list_prepend(DsList *, void *);

    // 链尾插入元素
    DS_API DS_STATUS ds_list_append(DsList *, void *);

    // 获取链表元素
    DS_API DS_STATUS ds_list_get(DsList *, int, void **);

    // 销毁链表
    DS_API void ds_list_destroy(DsList **);

    // 创建链表迭代器
    DS_API DsListIter *ds_list_iter_create(DsList *);

    // 迭代器是否有下一个元素
    DS_API DS_BOOL ds_list_iter_hasNext(DsListIter *);

    // 获取迭代器的下一个元素
    DS_API DS_STATUS ds_list_iter_next(DsListIter *, void **);

    // 获取迭代器当前节点数据
    DS_API DS_STATUS ds_list_iter_val(DsListIter *, void **);

    // 销毁迭代器
    DS_API void ds_list_iter_destroy(DsListIter **);

#ifdef __cplusplus
}
#endif

#endif // DSLIST_H_INCLUDE_
