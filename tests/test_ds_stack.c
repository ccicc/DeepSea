// test_ds_stack.c
// create by lq on 2018/11/18
//

#include <string.h>
#include "../include/ds_stack.h"
#include "Unity/src/unity.h"

DS_STACK *stack = NULL;

void setUp(void)
{
    stack = ds_stack_create(3);
    TEST_ASSERT_NOT_NULL_MESSAGE(stack, "stack initialize failed!");
}

void tearDown(void)
{
    ds_stack_destroy(&stack);
    TEST_ASSERT_NULL_MESSAGE(stack, "stack destroy failed!");
}

static void test_dsStack_counts()
{
    TEST_ASSERT_EQUAL_MESSAGE(ds_stack_counts(stack), 0, "unexpected counts!");
    ds_stack_push(stack, "aa");
    TEST_ASSERT_EQUAL_MESSAGE(ds_stack_counts(stack), 1, "unexpected counts!");
    ds_stack_push(stack, "bb");
    TEST_ASSERT_EQUAL_MESSAGE(ds_stack_counts(stack), 2, "unexpected counts!");
    ds_stack_push(stack, "cc");
    TEST_ASSERT_EQUAL_MESSAGE(ds_stack_counts(stack), 3, "unexpected counts!");
}

static void test_dsStack_overflow()
{
    TEST_ASSERT_EQUAL_MESSAGE(ds_stack_counts(stack), 0, "unexpected counts!");
    DS_STATUS res;
    char* strs[3] = {"aa", "bb", "cc"};
    for(int i = 0; i < 3; ++i)
    {
        ds_stack_push(stack, strs[i]);
        TEST_ASSERT_EQUAL_MESSAGE(ds_stack_counts(stack), i+1, "unexpected counts!");
    }
    res = ds_stack_push(stack, "dd");
    TEST_ASSERT_EQUAL_MESSAGE(res, DS_STATUS_FULL, "overflow");
}

static void test_dsStack_empty()
{
    TEST_ASSERT_EQUAL_MESSAGE(ds_stack_counts(stack), 0, "unexpected counts!");
    DS_STATUS res;
    void* data;
    res = ds_stack_pop(stack, &data);
    TEST_ASSERT_EQUAL_MESSAGE(res, DS_STATUS_EMPTY, "empty");
}

static void test_dsStack_store()
{
    TEST_ASSERT_EQUAL_MESSAGE(ds_stack_counts(stack), 0, "unexpected counts!");
    char* strs[3] = {"one", "two", "three"};
    for(int i = 0; i < 3; ++i)
        ds_stack_push(stack, strs[i]);
    void* data;
    DS_STATUS res = ds_stack_pop(stack, &data);
    TEST_ASSERT_EQUAL(res, DS_STATUS_OK);
    TEST_ASSERT_TRUE(!strcmp((char*)data, "three"));
    res = ds_stack_clear(stack);
    TEST_ASSERT_EQUAL(res, DS_STATUS_OK);
    TEST_ASSERT_EQUAL_MESSAGE(ds_stack_counts(stack), 0, "unexpected counts!");
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_dsStack_counts);
    RUN_TEST(test_dsStack_overflow);
    RUN_TEST(test_dsStack_empty);
    RUN_TEST(test_dsStack_store);
    return UNITY_END();
}
