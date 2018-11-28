// test_ds_list.c
// create by lq on 2018/11/27
//

#include <malloc.h>
#include <string.h>
#include "../include/ds_list.h"
#include "Unity/src/unity.h"

DsList *list = NULL;

typedef struct TestData
{
    char ch;
    int num;
} TestData;

DS_BOOL equalStr(void *a, void *b)
{
    char *str1 = (char *)a;
    char *str2 = (char *)b;
    return !strcmp(str1, str2);
}

DS_BOOL equalData(void *a, void *b)
{
    TestData *data1 = (TestData *)a;
    TestData *data2 = (TestData *)b;
    return (data1->num == data2->num && data1->ch == data2->ch);
}

void setUp(void)
{
    list = ds_list_create_equal(&equalStr);
    TEST_ASSERT_NOT_NULL_MESSAGE(list, "list initialize failed!");
}

void tearDown(void)
{
    ds_list_destroy(&list);
    TEST_ASSERT_NULL_MESSAGE(list, "list destroy failed!");
}

static void test_list_count(void)
{
    TEST_ASSERT_EQUAL(ds_list_size(list), 0);
    DS_STATUS status = ds_list_append(list, "a");
    TEST_ASSERT_EQUAL(ds_list_size(list), 1);
}

static void test_list_insert(void)
{
    TEST_ASSERT_EQUAL(ds_list_size(list), 0);

    DS_STATUS status;
    char *strs[3] = {"a", "b", "c"};
    char *str;

    for (int i = 0; i < 3; ++i)
    {
        status = ds_list_append(list, strs[i]);
        TEST_ASSERT_EQUAL(ds_list_size(list), i + 1);
        TEST_ASSERT_EQUAL(status, DS_STATUS_OK);
    }

    int index = ds_list_find_index(list, "c");
    TEST_ASSERT_EQUAL(index, 2);

    for (int i = 0; i < 3; ++i)
    {
        status = ds_list_get(list, i, (void **)&str);
        TEST_ASSERT_EQUAL(status, DS_STATUS_OK);
        TEST_ASSERT_EQUAL_STRING(str, strs[i]);
    }

    status = ds_list_prepend(list, "first");
    TEST_ASSERT_EQUAL(status, DS_STATUS_OK);

    status = ds_list_insert(list, 4, "last");
    TEST_ASSERT_EQUAL(status, DS_STATUS_OK);
    TEST_ASSERT_EQUAL(ds_list_size(list), 5);

    status = ds_list_insert(list, 100, "outmem");
    TEST_ASSERT_EQUAL(status, DS_STATUS_OUTMEM);
}

static void test_list_remove(void)
{
    TEST_ASSERT_EQUAL(ds_list_size(list), 0);

    ds_list_destroy(&list);
    list = ds_list_create_equal(&equalData);

    TestData *datas = (TestData *)malloc(sizeof(TestData) * 5);
    if (NULL == datas)
        TEST_IGNORE_MESSAGE("datas memory allocation failed!");
    for (int i = 0; i < 5; ++i)
    {
        datas[i].num = i;
        datas[i].ch = (char)('A' + i);
        DS_STATUS statu = ds_list_append(list, &datas[i]);
        TEST_ASSERT_EQUAL(statu, DS_STATUS_OK);
    }
    TEST_ASSERT_EQUAL(ds_list_size(list), 5);

    DS_STATUS status;
    TestData *data;

    status = ds_list_remove_first(list, (void **)&data);
    TEST_ASSERT_EQUAL(status, DS_STATUS_OK);
    TEST_ASSERT_TRUE(equalData(&datas[0], data));
    TEST_ASSERT_EQUAL(ds_list_size(list), 4);

    status = ds_list_remove_last(list, (void **)&data);
    TEST_ASSERT_EQUAL(status, DS_STATUS_OK);
    TEST_ASSERT_TRUE(equalData(&datas[4], data));
    TEST_ASSERT_EQUAL(ds_list_size(list), 3);

    status = ds_list_remove(list, 1, (void **)&data);
    TEST_ASSERT_EQUAL(status, DS_STATUS_OK);
    TEST_ASSERT_EQUAL(equalData(&datas[2], data), DS_TRUE);
    TEST_ASSERT_EQUAL(ds_list_size(list), 2);

    status = ds_list_remove(list, 100, (void **)&data);
    TEST_ASSERT_EQUAL(status, DS_STATUS_OUTMEM);

    free(datas);
}

static void test_list_iter(void)
{
    TEST_ASSERT_EQUAL(ds_list_size(list), 0);

    int nums[4] = {11, 22, 33, 44};
    for (int i = 0; i < 4; ++i)
        ds_list_append(list, &nums[i]);

    int *p = NULL;
    DS_STATUS status;
    DsListIter *iter = ds_list_iter_create(list);
    TEST_ASSERT_NOT_NULL_MESSAGE(iter, "list iterator initialize failed!");

    while (ds_list_iter_hasNext(iter))
    {
        int *val = NULL;
        status = ds_list_iter_next(iter, (void **)&p);
        TEST_ASSERT_EQUAL(status, DS_STATUS_OK);
        status = ds_list_iter_val(iter, (void **)&val);
        TEST_ASSERT_EQUAL(status, DS_STATUS_OK);
        TEST_ASSERT_EQUAL(*val, *p);
    }

    ds_list_iter_destroy(&iter);
    TEST_ASSERT_NULL_MESSAGE(iter, "list iterator destroy failed!");
}

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_list_count);
    RUN_TEST(test_list_insert);
    RUN_TEST(test_list_remove);
    RUN_TEST(test_list_iter);

    return UNITY_END();
}
