// ds_list.c
// create by lq on 2018/11/25
//

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include "../include/ds_list.h"

typedef struct DsListEntry
{
    void *data;
    struct DsListEntry *next;
    struct DsListEntry *prev;
} DsListEntry;

struct DsList
{
    DsListEntry *entry;
    size_t size;
    DS_BOOL(*equal)(void *a, void *b);
};

struct DsListIter
{
    DsListEntry *head;
    DsListEntry *curr;
    size_t size;
    int index;
};

static DS_STATUS ds_entry_append(DsListEntry **entryAdd, DsListEntry *in)
{
    if (NULL == entryAdd || NULL == in)
        return DS_STATUS_NULL;
    if (NULL == *entryAdd)
        *entryAdd = in;
    else
    {
        DsListEntry *entry = *entryAdd;
        while (entry->next)
            entry = entry->next;
        entry->next = in;
        in->next = NULL;
        in->prev = entry;
    }
    return DS_STATUS_OK;
}

static DS_STATUS ds_entry_prepend(DsListEntry **entryAdd, DsListEntry *in)
{
    if (NULL == entryAdd || NULL == in)
        return DS_STATUS_NULL;
    if (NULL == *entryAdd)
        *entryAdd = in;
    else
    {
        DsListEntry *entry = *entryAdd;
        in->next = entry;
        in->prev = entry->prev;
        if (entry->prev)
            entry->prev->next = in;
        else
            *entryAdd = in;
        entry->prev = in;
    }
    return DS_STATUS_OK;
}

static DS_STATUS ds_entry_remove(DsListEntry **entryAdd)
{
    if (NULL == entryAdd || NULL == *entryAdd)
        return DS_STATUS_NULL;
    DsListEntry *entry = *entryAdd;
    if (NULL == entry->next && NULL == entry->prev)
        *entryAdd = NULL;
    else
    {
        if (entry->prev)
            entry->prev->next = entry->next;
        else
            *entryAdd = entry->next;

        if (entry->next)
            entry->next->prev = entry->prev;
    }
    free(entry);
    return DS_STATUS_OK;
}

DsList *ds_list_create(void)
{
    DsList *list = (DsList *)malloc(sizeof(DsList));
    if (NULL == list)
        exit(DS_STATUS_OUTMEM);
    list->entry = NULL;
    list->equal = NULL;
    list->size = 0;
    return list;
}

DsList *ds_list_create_equal(DS_BOOL (*equal)(void *a, void *b))
{
    DsList *list = ds_list_create();
    list->equal = equal;
    return list;
}

size_t ds_list_size(DsList *list)
{
    if (NULL == list)
        return 0;
    return list->size;
}

DS_STATUS ds_list_insert(DsList *list, int index, void *data)
{
    if (NULL == list)
        return DS_STATUS_NULL;
    if (index < 0 || index > list->size)
        return DS_STATUS_OUTMEM;

    DsListEntry *in = (DsListEntry *)malloc(sizeof(DsListEntry));
    if (NULL == in)
        return DS_STATUS_OUTMEM;
    in->data = data;
    in->next = NULL;
    in->prev = NULL;

    DS_STATUS status;

    // ! 这里需要获取list->entry的地址
    DsListEntry **entry = &list->entry;
    while ((*entry) && (*entry)->next && index > 0)
    {
        index--;
        // ! 需要改变的是entry的地址
        entry = &(*entry)->next;
    }

    if (index == list->size)
        status = ds_entry_append(entry, in);
    else
        status = ds_entry_prepend(entry, in);

    if (status != DS_STATUS_OK)
    {
        free(in);
        return DS_STATUS_NULL;
    }

    (list->size)++;
    return DS_STATUS_OK;
}

DS_STATUS ds_list_prepend(DsList *list, void *data)
{
    if (NULL == list)
        return DS_STATUS_NULL;
    DsListEntry *in = (DsListEntry *)malloc(sizeof(DsListEntry));
    if (NULL == in)
        return DS_STATUS_OUTMEM;
    in->data = data;
    in->prev = NULL;
    in->next = NULL;

    DsListEntry **entry = &list->entry;
    if (DS_STATUS_OK != ds_entry_prepend(entry, in))
    {
        free(in);
        return DS_STATUS_NULL;
    }

    (list->size)++;
    return DS_STATUS_OK;
}

DS_STATUS ds_list_append(DsList *list, void *data)
{
    if (NULL == list)
        return DS_STATUS_NULL;
    DsListEntry *in = (DsListEntry *)malloc(sizeof(DsListEntry));
    if (NULL == in)
        return DS_STATUS_OUTMEM;
    in->data = data;
    in->next = NULL;
    in->prev = NULL;

    if (DS_STATUS_OK != ds_entry_append(&list->entry, in))
    {
        free(in);
        return DS_STATUS_NULL;
    }

    (list->size)++;
    return DS_STATUS_OK;
}

DS_STATUS ds_list_remove(DsList *list, int index, void **pdata)
{
    if (NULL == list || NULL == list->entry)
        return DS_STATUS_NULL;
    if (index < 0 || index >= list->size)
        return DS_STATUS_OUTMEM;
    DsListEntry **entry = &list->entry;
    while ((*entry)->next && index > 0)
    {
        index--;
        entry = &(*entry)->next;
    }
    if (NULL != pdata)
        *pdata = (*entry)->data;
    (list->size)--;
    return ds_entry_remove(entry);
}

DS_STATUS ds_list_remove_first(DsList *list, void **pdata)
{
    if (NULL == list || NULL == list->entry)
        return DS_STATUS_NULL;

    DsListEntry **entry = &list->entry;
    if (NULL != pdata)
        *pdata = (*entry)->data;

    (list->size)--;
    return ds_entry_remove(entry);
}

DS_STATUS ds_list_remove_last(DsList *list, void **pdata)
{
    if (NULL == list || NULL == list->entry)
        return DS_STATUS_NULL;

    DsListEntry **entry = &list->entry;
    while ((*entry)->next)
        entry = &(*entry)->next;

    if (NULL != pdata)
        *pdata = (*entry)->data;
    (list->size)--;
    return ds_entry_remove(entry);
}

int ds_list_find_index(DsList *list, void *data)
{
    if (NULL == list || NULL == list->equal || NULL == list->entry)
        return -1;
    DsListEntry *entry = list->entry;
    int i = 0;
    while (entry)
    {
        if ((*(list->equal))(data, entry->data))
            return i;
        i++;
        entry = entry->next;
    }
    return -1;
}

DS_STATUS ds_list_get(DsList *list, int index, void **pdata)
{
    if (NULL == list || NULL == list->entry)
        return DS_STATUS_NULL;
    if (index < 0 || index >= list->size)
        return DS_STATUS_OUTMEM;

    DsListEntry *entry = list->entry;
    while (entry && entry->next && index > 0)
    {
        index--;
        entry = entry->next;
    }
    *pdata = entry->data;
    return DS_STATUS_OK;
}

void ds_list_destroy(DsList **plist)
{
    if (*plist)
    {
        DsList *list = *plist;
        DsListEntry *entry = list->entry;
        while (entry)
        {
            DsListEntry *temp = entry;
            entry = entry->next;
            free(temp);
        }
        free(list);
        *plist = NULL;
    }
    return;
}

DsListIter *ds_list_iter_create(DsList *list)
{
    if (NULL == list)
        return NULL;
    DsListIter *iter = (DsListIter *)malloc(sizeof(DsListIter));
    if (NULL == iter)
        exit(DS_STATUS_OUTMEM);
    iter->head = (DsListEntry *)malloc(sizeof(DsListEntry));
    if (NULL == iter->head)
        exit(DS_STATUS_OUTMEM);
    iter->head->data = NULL;
    iter->head->prev = NULL;
    iter->head->next = list->entry;
    iter->curr = iter->head;
    iter->size = list->size;
    iter->index = -1;
    return iter;
}

DS_BOOL ds_list_iter_hasNext(DsListIter *iter)
{
    if (NULL == iter)
        return DS_FALSE;
    return NULL != iter->curr->next;
}

DS_STATUS ds_list_iter_next(DsListIter *iter, void **pdata)
{
    if (NULL == iter || NULL == iter->curr)
        return DS_STATUS_NULL;
    iter->curr = iter->curr->next;
    iter->index++;
    if (NULL != pdata)
        *pdata = iter->curr->data;
    return DS_STATUS_OK;
}

DS_STATUS ds_list_iter_val(DsListIter *iter, void **pdata)
{
    if (NULL == iter || NULL == iter->curr)
        return DS_STATUS_NULL;
    if (NULL != pdata)
        *pdata = iter->curr->data;
    return DS_STATUS_OK;
}

void ds_list_iter_destroy(DsListIter **piter)
{
    if (*piter)
    {
        DsListIter *iter = *piter;
        free(iter->head);
        free(iter);
        *piter = NULL;
    }
    return;
}
