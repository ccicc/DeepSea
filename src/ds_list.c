// ds_list.c
// create by lq on 2018/11/25
//

#include <stdlib.h>
#include <malloc.h>
#include "../include/ds_list.c"

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
    DS_BOOL(*equal)
    (void *a, void *b);
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
    if (index < 0 || index > list->size + 1)
        return DS_STATUS_OUTMEM;

    DsListEntry *in = (DsListEntry *)malloc(sizeof(DsListEntry));
    if (NULL == in)
        return DS_STATUS_OUTMEM;
    in->data = data;
    in->next = NULL;
    in->prev = NULL;

    DsListEntry *entry = list->entry;
    while (entry && entry->next && index > 0)
    {
        index--;
        entry = entry->next;
    }
    if (DS_STATUS_OK != ds_entry_prepend(&entry, in))
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

    DsListEntry *entry = list->entry;
    if (DS_STATUS_OK != ds_entry_prepend(&entry, in))
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

    DsListEntry *entry = list->entry;
    if (DS_STATUS_OK != ds_entry_append(&entry, in))
    {
        free(in);
        return DS_STATUS_NULL;
    }

    (list->size)++;
    return DS_STATUS_OK;
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
        list->size = 0;
        free(list);
        *plist = NULL;
    }
    return;
}

