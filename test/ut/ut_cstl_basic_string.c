#include <stddef.h>
#include <stdarg.h>
#include <setjmp.h>
#include <google/cmockery.h>

#include "cstl/cstl_def.h"
#include "cstl/cstl_iterator.h"
#include "cstl/clist.h"
#include "cstl/cvector.h"
#include "cstl/cstl_basic_string_iterator.h"
#include "cstl/cstl_basic_string_private.h"
#include "cstl/cstl_basic_string.h"
#include "cstl_basic_string_aux.h"

#include "ut_def.h"
#include "ut_cstl_basic_string.h"

UT_SUIT_DEFINATION(cstl_basic_string, basic_string_init)

/*
 * test basic_string_init
 */
UT_CASE_DEFINATION(basic_string_init)
void test_basic_string_init__null_basic_string_container(void** state)
{
    expect_assert_failure(basic_string_init(NULL));
}

void test_basic_string_init__non_created(void** state)
{
    basic_string_t bstr;
    bstr._t_vector._pby_start = (_byte_t*)0x887;
    expect_assert_failure(basic_string_init(&bstr));
}

void test_basic_string_init__successfully_c_builtin(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(int);
    basic_string_init(pt_basic_string);

    assert_true(basic_string_size(pt_basic_string) == 0);
    assert_true(basic_string_capacity(pt_basic_string) == 0);

    basic_string_destroy(pt_basic_string);
}

void test_basic_string_init__successfully_cstl_builtin(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(list_t<int>);
    basic_string_init(pt_basic_string);

    assert_true(basic_string_size(pt_basic_string) == 0);
    assert_true(basic_string_capacity(pt_basic_string) == 0);

    basic_string_destroy(pt_basic_string);
}

void test_basic_string_init__successfully_cstr(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(char*);
    basic_string_init(pt_basic_string);

    assert_true(basic_string_size(pt_basic_string) == 0);
    assert_true(basic_string_capacity(pt_basic_string) == 0);

    basic_string_destroy(pt_basic_string);
}

void test_basic_string_init__successfully_user_defined(void** state)
{
    typedef struct _tagtest_basic_string_init__successfully_user_defined
    {
        int n_elem;
    }_test_basic_string_init__successfully_user_defined_t;
    basic_string_t* pt_basic_string = NULL;

    type_register(_test_basic_string_init__successfully_user_defined_t, NULL, NULL, NULL, NULL);

    pt_basic_string = create_basic_string(_test_basic_string_init__successfully_user_defined_t);
    basic_string_init(pt_basic_string);

    assert_true(basic_string_size(pt_basic_string) == 0);
    assert_true(basic_string_capacity(pt_basic_string) == 0);

    basic_string_destroy(pt_basic_string);
}

/*
 * test basic_string_init_cstr
 */
UT_CASE_DEFINATION(basic_string_init_cstr)
void test_basic_string_init_cstr__null_container(void** state)
{
    expect_assert_failure(basic_string_init_cstr(NULL, "abcdef"));
}

void test_basic_string_init_cstr__non_created_container(void** state)
{
    basic_string_t bstr;
    bstr._t_vector._t_typeinfo._t_style = 24455656;
    expect_assert_failure(basic_string_init_cstr(&bstr, "abcdefg"));
}

void test_basic_string_init_cstr__null_valuestring(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(int);

    expect_assert_failure(basic_string_init_cstr(pt_basic_string, NULL));

    basic_string_destroy(pt_basic_string);
}

void test_basic_string_init_cstr__c_builtin_init_empty(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(int);
    int elem = 0;

    basic_string_init_cstr(pt_basic_string, &elem);
    assert_true(basic_string_size(pt_basic_string) == 0);

    basic_string_destroy(pt_basic_string);
}

void test_basic_string_init_cstr__c_builtin_init_non_empty(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(int);
    int elems[] = {9, 5, 2, 0, 13, 5455};

    basic_string_init_cstr(pt_basic_string, elems);
    assert_true(basic_string_size(pt_basic_string) == 3);
    assert_true(*(int*)basic_string_at(pt_basic_string, 0) == 9);
    assert_true(*(int*)basic_string_at(pt_basic_string, 1) == 5);
    assert_true(*(int*)basic_string_at(pt_basic_string, 2) == 2);

    basic_string_destroy(pt_basic_string);
}

void test_basic_string_init_cstr__char_init_empty(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(char);

    basic_string_init_cstr(pt_basic_string, "");
    assert_true(basic_string_size(pt_basic_string) == 0);

    basic_string_destroy(pt_basic_string);
}

void test_basic_string_init_cstr__char_init_non_empty(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(char);

    basic_string_init_cstr(pt_basic_string, "abc");
    assert_true(basic_string_size(pt_basic_string) == 3);
    assert_true(*(char*)basic_string_at(pt_basic_string, 0) == 'a');
    assert_true(*(char*)basic_string_at(pt_basic_string, 1) == 'b');
    assert_true(*(char*)basic_string_at(pt_basic_string, 2) == 'c');

    basic_string_destroy(pt_basic_string);
}

void test_basic_string_init_cstr__cstr_init_empty(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(char*);
    const char* elems[] = {NULL};

    basic_string_init_cstr(pt_basic_string, elems);
    assert_true(basic_string_size(pt_basic_string) == 0);

    basic_string_destroy(pt_basic_string);
}

void test_basic_string_init_cstr__cstr_init_non_empty(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(char*);
    const char* elems[] = {"abc", "def", "hij", NULL};

    basic_string_init_cstr(pt_basic_string, elems);
    assert_true(basic_string_size(pt_basic_string) == 3);
    assert_true(strcmp((char*)basic_string_at(pt_basic_string, 0), "abc") == 0);
    assert_true(strcmp((char*)basic_string_at(pt_basic_string, 1), "def") == 0);
    assert_true(strcmp((char*)basic_string_at(pt_basic_string, 2), "hij") == 0);

    basic_string_destroy(pt_basic_string);
}

void test_basic_string_init_cstr__libcstl_builtin_empty(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(list_t<int>);
    list_t* elems[] = {NULL};

    basic_string_init_cstr(pt_basic_string, elems);
    assert_true(basic_string_size(pt_basic_string) == 0);

    basic_string_destroy(pt_basic_string);
}

void test_basic_string_init_cstr__libcstl_builtin_non_empty(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(list_t<int>);
    list_t* plist = create_list(int);
    list_t* elems[5];

    list_init(plist);
    elems[0] = plist;
    elems[1] = plist;
    elems[2] = plist;
    elems[3] = NULL;
    elems[4] = plist;
    basic_string_init_cstr(pt_basic_string, elems);
    assert_true(basic_string_size(pt_basic_string) == 3);

    basic_string_destroy(pt_basic_string);
    list_destroy(plist);
}

typedef struct _tag_test_basic_string_init_cstr__user_define
{
    int n_elem;
    double d_elem;
}_test_basic_string_init_cstr__user_define_t;
void test_basic_string_init_cstr__user_define_empty(void** state)
{
    basic_string_t* pt_basic_string = NULL;
    _test_basic_string_init_cstr__user_define_t* elems[] = {NULL};

    type_register(_test_basic_string_init_cstr__user_define_t, NULL, NULL, NULL, NULL);
    pt_basic_string = create_basic_string(_test_basic_string_init_cstr__user_define_t);

    basic_string_init_cstr(pt_basic_string, elems);
    assert_true(basic_string_size(pt_basic_string) == 0);

    basic_string_destroy(pt_basic_string);
}

void test_basic_string_init_cstr__user_define_non_empty(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(_test_basic_string_init_cstr__user_define_t);
    _test_basic_string_init_cstr__user_define_t t_user1;
    _test_basic_string_init_cstr__user_define_t t_user2;
    _test_basic_string_init_cstr__user_define_t* elems[5] = {&t_user1, &t_user2, &t_user2, NULL, &t_user1};

    t_user1.n_elem = 4;
    t_user1.d_elem = 9.4;
    t_user2.n_elem = 0;
    t_user2.d_elem = 0.0;
    basic_string_init_cstr(pt_basic_string, elems);
    assert_true(basic_string_size(pt_basic_string) == 3);
    assert_true(((_test_basic_string_init_cstr__user_define_t*)basic_string_at(pt_basic_string, 0))->n_elem == 4);
    assert_true(((_test_basic_string_init_cstr__user_define_t*)basic_string_at(pt_basic_string, 0))->d_elem == 9.4);
    assert_true(((_test_basic_string_init_cstr__user_define_t*)basic_string_at(pt_basic_string, 1))->n_elem == 0);
    assert_true(((_test_basic_string_init_cstr__user_define_t*)basic_string_at(pt_basic_string, 1))->d_elem == 0.0);
    assert_true(((_test_basic_string_init_cstr__user_define_t*)basic_string_at(pt_basic_string, 2))->n_elem == 0);
    assert_true(((_test_basic_string_init_cstr__user_define_t*)basic_string_at(pt_basic_string, 2))->d_elem == 0.0);

    basic_string_destroy(pt_basic_string);
}

/*
 * test basic_string_init_subcstr
 */
UT_CASE_DEFINATION(basic_string_init_subcstr)
void test_basic_string_init_subcstr__null_container(void** state)
{
    expect_assert_failure(basic_string_init_subcstr(NULL, "abcdef", 0));
}

void test_basic_string_init_subcstr__non_created_container(void** state)
{
    basic_string_t bstr;
    bstr._t_vector._t_typeinfo._t_style = 24455656;
    expect_assert_failure(basic_string_init_subcstr(&bstr, "abcdefg", NPOS));
}

void test_basic_string_init_subcstr__null_valuestring(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(int);

    expect_assert_failure(basic_string_init_subcstr(pt_basic_string, NULL, NPOS));

    basic_string_destroy(pt_basic_string);
}

void test_basic_string_init_subcstr__c_builtin_init_empty(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(int);
    int elems[] = {9, 5, 2, 0, 13, 5455};

    basic_string_init_subcstr(pt_basic_string, elems, 0);
    assert_true(basic_string_size(pt_basic_string) == 0);

    basic_string_destroy(pt_basic_string);
}

void test_basic_string_init_subcstr__c_builtin_init_non_empty(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(int);
    int elems[] = {9, 5, 2, 0, 13, 5455};

    basic_string_init_subcstr(pt_basic_string, elems, 2);
    assert_true(basic_string_size(pt_basic_string) == 2);
    assert_true(*(int*)basic_string_at(pt_basic_string, 0) == 9);
    assert_true(*(int*)basic_string_at(pt_basic_string, 1) == 5);

    basic_string_destroy(pt_basic_string);
}

void test_basic_string_init_subcstr__c_builtin_init_total(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(int);
    int elems[] = {9, 5, 2, 0, 13, 5455};

    basic_string_init_subcstr(pt_basic_string, elems, 3);
    assert_true(basic_string_size(pt_basic_string) == 3);
    assert_true(*(int*)basic_string_at(pt_basic_string, 0) == 9);
    assert_true(*(int*)basic_string_at(pt_basic_string, 1) == 5);
    assert_true(*(int*)basic_string_at(pt_basic_string, 2) == 2);

    basic_string_destroy(pt_basic_string);
}

void test_basic_string_init_subcstr__char_init_empty(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(char);

    basic_string_init_subcstr(pt_basic_string, "abc", 0);
    assert_true(basic_string_size(pt_basic_string) == 0);

    basic_string_destroy(pt_basic_string);
}

void test_basic_string_init_subcstr__char_init_non_empty(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(char);

    basic_string_init_subcstr(pt_basic_string, "abc", 1);
    assert_true(basic_string_size(pt_basic_string) == 1);
    assert_true(*(char*)basic_string_at(pt_basic_string, 0) == 'a');

    basic_string_destroy(pt_basic_string);
}

void test_basic_string_init_subcstr__char_init_total(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(char);

    basic_string_init_subcstr(pt_basic_string, "abc", 100);
    assert_true(basic_string_size(pt_basic_string) == 3);
    assert_true(*(char*)basic_string_at(pt_basic_string, 0) == 'a');
    assert_true(*(char*)basic_string_at(pt_basic_string, 1) == 'b');
    assert_true(*(char*)basic_string_at(pt_basic_string, 2) == 'c');

    basic_string_destroy(pt_basic_string);
}

void test_basic_string_init_subcstr__cstr_init_empty(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(char*);
    const char* elems[] = {"abc", "def", "hij", NULL};

    basic_string_init_subcstr(pt_basic_string, elems, 0);
    assert_true(basic_string_size(pt_basic_string) == 0);

    basic_string_destroy(pt_basic_string);
}

void test_basic_string_init_subcstr__cstr_init_non_empty(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(char*);
    const char* elems[] = {"abc", "def", "hij", NULL};

    basic_string_init_subcstr(pt_basic_string, elems, 2);
    assert_true(basic_string_size(pt_basic_string) == 2);
    assert_true(strcmp((char*)basic_string_at(pt_basic_string, 0), "abc") == 0);
    assert_true(strcmp((char*)basic_string_at(pt_basic_string, 1), "def") == 0);

    basic_string_destroy(pt_basic_string);
}

void test_basic_string_init_subcstr__cstr_init_total(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(char*);
    const char* elems[] = {"abc", "def", "hij", NULL};

    basic_string_init_subcstr(pt_basic_string, elems, NPOS);
    assert_true(basic_string_size(pt_basic_string) == 3);
    assert_true(strcmp((char*)basic_string_at(pt_basic_string, 0), "abc") == 0);
    assert_true(strcmp((char*)basic_string_at(pt_basic_string, 1), "def") == 0);
    assert_true(strcmp((char*)basic_string_at(pt_basic_string, 2), "hij") == 0);

    basic_string_destroy(pt_basic_string);
}

void test_basic_string_init_subcstr__libcstl_builtin_empty(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(list_t<int>);
    list_t* plist = create_list(int);
    list_t* elems[5];

    list_init(plist);
    elems[0] = plist;
    elems[1] = plist;
    elems[2] = plist;
    elems[3] = NULL;
    elems[4] = plist;
    basic_string_init_subcstr(pt_basic_string, elems, 0);
    assert_true(basic_string_size(pt_basic_string) == 0);

    basic_string_destroy(pt_basic_string);
    list_destroy(plist);
}

void test_basic_string_init_subcstr__libcstl_builtin_non_empty(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(list_t<int>);
    list_t* plist = create_list(int);
    list_t* elems[5];

    list_init(plist);
    elems[0] = plist;
    elems[1] = plist;
    elems[2] = plist;
    elems[3] = NULL;
    elems[4] = plist;
    basic_string_init_subcstr(pt_basic_string, elems, 1);
    assert_true(basic_string_size(pt_basic_string) == 1);

    basic_string_destroy(pt_basic_string);
    list_destroy(plist);
}

void test_basic_string_init_subcstr__libcstl_builtin_total(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(list_t<int>);
    list_t* plist = create_list(int);
    list_t* elems[5];

    list_init(plist);
    elems[0] = plist;
    elems[1] = plist;
    elems[2] = plist;
    elems[3] = NULL;
    elems[4] = plist;
    basic_string_init_subcstr(pt_basic_string, elems, NPOS);
    assert_true(basic_string_size(pt_basic_string) == 3);

    basic_string_destroy(pt_basic_string);
    list_destroy(plist);
}

typedef struct _tag_test_basic_string_init_subcstr__user_define
{
    int n_elem;
    double d_elem;
}_test_basic_string_init_subcstr__user_define_t;
void test_basic_string_init_subcstr__user_define_empty(void** state)
{
    basic_string_t* pt_basic_string = NULL;
    _test_basic_string_init_subcstr__user_define_t t_user;
    _test_basic_string_init_subcstr__user_define_t* elems[5] = {&t_user, &t_user, &t_user, NULL, &t_user};

    type_register(_test_basic_string_init_subcstr__user_define_t, NULL, NULL, NULL, NULL);
    pt_basic_string = create_basic_string(_test_basic_string_init_subcstr__user_define_t);

    basic_string_init_subcstr(pt_basic_string, elems, 0);
    assert_true(basic_string_size(pt_basic_string) == 0);

    basic_string_destroy(pt_basic_string);
}

void test_basic_string_init_subcstr__user_define_non_empty(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(_test_basic_string_init_subcstr__user_define_t);
    _test_basic_string_init_subcstr__user_define_t t_user;
    _test_basic_string_init_subcstr__user_define_t* elems[5] = {&t_user, &t_user, &t_user, NULL, &t_user};

    t_user.n_elem = 4;
    t_user.d_elem = 0.0;
    basic_string_init_subcstr(pt_basic_string, elems, 1);
    assert_true(basic_string_size(pt_basic_string) == 1);
    assert_true(((_test_basic_string_init_subcstr__user_define_t*)basic_string_at(pt_basic_string, 0))->n_elem == 4);
    assert_true(((_test_basic_string_init_subcstr__user_define_t*)basic_string_at(pt_basic_string, 0))->d_elem == 0.0);

    basic_string_destroy(pt_basic_string);
}

void test_basic_string_init_subcstr__user_define_total(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(_test_basic_string_init_subcstr__user_define_t);
    _test_basic_string_init_subcstr__user_define_t t_user1;
    _test_basic_string_init_subcstr__user_define_t t_user2;
    _test_basic_string_init_subcstr__user_define_t t_user3;
    _test_basic_string_init_subcstr__user_define_t* elems[5] = {&t_user1, &t_user2, &t_user3, NULL, &t_user1};

    t_user1.n_elem = 4; t_user1.d_elem = 0.0;
    t_user2.n_elem = 0; t_user2.d_elem = 9.24;
    t_user3.n_elem = 0; t_user3.d_elem = 0.0;
    basic_string_init_subcstr(pt_basic_string, elems, NPOS);
    assert_true(basic_string_size(pt_basic_string) == 3);
    assert_true(((_test_basic_string_init_subcstr__user_define_t*)basic_string_at(pt_basic_string, 0))->n_elem == 4);
    assert_true(((_test_basic_string_init_subcstr__user_define_t*)basic_string_at(pt_basic_string, 0))->d_elem == 0.0);
    assert_true(((_test_basic_string_init_subcstr__user_define_t*)basic_string_at(pt_basic_string, 1))->n_elem == 0);
    assert_true(((_test_basic_string_init_subcstr__user_define_t*)basic_string_at(pt_basic_string, 1))->d_elem == 9.24);
    assert_true(((_test_basic_string_init_subcstr__user_define_t*)basic_string_at(pt_basic_string, 2))->n_elem == 0);
    assert_true(((_test_basic_string_init_subcstr__user_define_t*)basic_string_at(pt_basic_string, 2))->d_elem == 0.0);

    basic_string_destroy(pt_basic_string);
}

/*
 * test basic_string_init_copy
 */
UT_CASE_DEFINATION(basic_string_init_copy)
void test_basic_string_init_copy__null_dest(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(int);
    basic_string_init(pt_basic_string);

    expect_assert_failure(basic_string_init_copy(NULL, pt_basic_string));

    basic_string_destroy(pt_basic_string);
}

void test_basic_string_init_copy__null_src(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(int);

    expect_assert_failure(basic_string_init_copy(pt_basic_string, NULL));

    basic_string_destroy(pt_basic_string);
}

void test_basic_string_init_copy__non_create_dest(void** state)
{
    basic_string_t bstr;
    basic_string_t* pt_basic_string = create_basic_string(int);
    basic_string_init(pt_basic_string);

    bstr._t_vector._t_typeinfo._pt_type = NULL;
    expect_assert_failure(basic_string_init_copy(&bstr, pt_basic_string));

    basic_string_destroy(pt_basic_string);
}

void test_basic_string_init_copy__non_inited_src(void** state)
{
    basic_string_t* pt_dest = create_basic_string(int);
    basic_string_t* pt_src = create_basic_string(int);

    pt_src->_t_vector._pby_finish = (_byte_t*)0x732;
    expect_assert_failure(basic_string_init_copy(pt_dest, pt_src));

    pt_src->_t_vector._pby_finish = NULL;
    basic_string_destroy(pt_dest);
    basic_string_destroy(pt_src);
}

void test_basic_string_init_copy__not_same_type(void** state)
{
    basic_string_t* pt_dest = create_basic_string(int);
    basic_string_t* pt_src = create_basic_string(double);
    basic_string_init(pt_src);

    expect_assert_failure(basic_string_init_copy(pt_dest, pt_src));

    basic_string_destroy(pt_dest);
    basic_string_destroy(pt_src);
}

void test_basic_string_init_copy__successfully_c_builtin_empty(void** state)
{
    basic_string_t* pt_dest = create_basic_string(int);
    basic_string_t* pt_src = create_basic_string(int);
    basic_string_init(pt_src);

    basic_string_init_copy(pt_dest, pt_src);
    assert_true(basic_string_size(pt_dest) == basic_string_size(pt_src));
    assert_true(basic_string_capacity(pt_dest) == 0);

    basic_string_destroy(pt_dest);
    basic_string_destroy(pt_src);
}

void test_basic_string_init_copy__successfully_c_builtin_little(void** state)
{
    size_t i = 0;
    basic_string_t* pt_dest = create_basic_string(int);
    basic_string_t* pt_src = create_basic_string(int);
    basic_string_init_elem(pt_src, 10, 2010);

    basic_string_init_copy(pt_dest, pt_src);
    assert_true(basic_string_size(pt_dest) == basic_string_size(pt_src));
    assert_true(basic_string_capacity(pt_dest) == 26);
    for(i = 0; i < basic_string_size(pt_dest); ++i)
    {
        assert_true(*(int*)basic_string_at(pt_dest, i) == 2010);
    }

    basic_string_destroy(pt_dest);
    basic_string_destroy(pt_src);
}

void test_basic_string_init_copy__successfully_c_builtin_huge(void** state)
{
    size_t i = 0;
    basic_string_t* pt_dest = create_basic_string(int);
    basic_string_t* pt_src = create_basic_string(int);
    basic_string_init_elem(pt_src, 1000, 2010);

    basic_string_init_copy(pt_dest, pt_src);
    assert_true(basic_string_size(pt_dest) == basic_string_size(pt_src));
    assert_true(basic_string_capacity(pt_dest) == 1500);
    for(i = 0; i < basic_string_size(pt_dest); ++i)
    {
        assert_true(*(int*)basic_string_at(pt_dest, i) == 2010);
    }

    basic_string_destroy(pt_dest);
    basic_string_destroy(pt_src);
}

void test_basic_string_init_copy__successfully_cstr_empty(void** state)
{
    basic_string_t* pt_dest = create_basic_string(char*);
    basic_string_t* pt_src = create_basic_string(char*);
    basic_string_init(pt_src);

    basic_string_init_copy(pt_dest, pt_src);
    assert_true(basic_string_size(pt_dest) == basic_string_size(pt_src));
    assert_true(basic_string_capacity(pt_dest) == 0);

    basic_string_destroy(pt_dest);
    basic_string_destroy(pt_src);
}

void test_basic_string_init_copy__successfully_cstr_little(void** state)
{
    size_t i = 0;
    basic_string_t* pt_dest = create_basic_string(char*);
    basic_string_t* pt_src = create_basic_string(char*);
    basic_string_init_elem(pt_src, 19, "c-string");

    basic_string_init_copy(pt_dest, pt_src);
    assert_true(basic_string_size(pt_dest) == basic_string_size(pt_src));
    assert_true(basic_string_capacity(pt_dest) == 35);
    for(i = 0; i < basic_string_size(pt_dest); ++i)
    {
        assert_true(strcmp((char*)basic_string_at(pt_dest, i), "c-string") == 0);
    }

    basic_string_destroy(pt_dest);
    basic_string_destroy(pt_src);
}

void test_basic_string_init_copy__successfully_cstr_huge(void** state)
{
    size_t i = 0;
    basic_string_t* pt_dest = create_basic_string(char*);
    basic_string_t* pt_src = create_basic_string(char*);
    basic_string_init_elem(pt_src, 19000, "c-string");

    basic_string_init_copy(pt_dest, pt_src);
    assert_true(basic_string_size(pt_dest) == basic_string_size(pt_src));
    assert_true(basic_string_capacity(pt_dest) == 28500);
    for(i = 0; i < basic_string_size(pt_dest); ++i)
    {
        assert_true(strcmp((char*)basic_string_at(pt_dest, i), "c-string") == 0);
    }

    basic_string_destroy(pt_dest);
    basic_string_destroy(pt_src);
}

void test_basic_string_init_copy__successfully_cstl_builtin_empty(void** state)
{
    basic_string_t* pt_dest = create_basic_string(list_t<int>);
    basic_string_t* pt_src = create_basic_string(list_t<int>);
    list_t* pt_elem = create_list(int);
    list_init_elem(pt_elem, 23, 21234);
    basic_string_init(pt_src);

    basic_string_init_copy(pt_dest, pt_src);
    assert_true(basic_string_size(pt_dest) == basic_string_size(pt_src));
    assert_true(basic_string_capacity(pt_dest) == 0);

    basic_string_destroy(pt_dest);
    basic_string_destroy(pt_src);
    list_destroy(pt_elem);
}

void test_basic_string_init_copy__successfully_cstl_builtin_little(void** state)
{
    size_t i = 0;
    basic_string_t* pt_dest = create_basic_string(list_t<int>);
    basic_string_t* pt_src = create_basic_string(list_t<int>);
    list_t* pt_elem = create_list(int);
    list_init_elem(pt_elem, 23, 21234);
    basic_string_init_elem(pt_src, 32, pt_elem);

    basic_string_init_copy(pt_dest, pt_src);
    assert_true(basic_string_size(pt_dest) == basic_string_size(pt_src));
    assert_true(basic_string_capacity(pt_dest) == 48);
    for(i = 0; i < basic_string_size(pt_dest); ++i)
    {
        assert_true(list_equal((list_t*)basic_string_at(pt_dest, i), pt_elem));
    }

    basic_string_destroy(pt_dest);
    basic_string_destroy(pt_src);
    list_destroy(pt_elem);
}

void test_basic_string_init_copy__successfully_cstl_builtin_huge(void** state)
{
    size_t i = 0;
    basic_string_t* pt_dest = create_basic_string(list_t<int>);
    basic_string_t* pt_src = create_basic_string(list_t<int>);
    list_t* pt_elem = create_list(int);
    list_init_elem(pt_elem, 23, 21234);
    basic_string_init_elem(pt_src, 3702, pt_elem);

    basic_string_init_copy(pt_dest, pt_src);
    assert_true(basic_string_size(pt_dest) == basic_string_size(pt_src));
    assert_true(basic_string_capacity(pt_dest) == 5553);
    for(i = 0; i < basic_string_size(pt_dest); ++i)
    {
        assert_true(list_equal((list_t*)basic_string_at(pt_dest, i), pt_elem));
    }

    basic_string_destroy(pt_dest);
    basic_string_destroy(pt_src);
    list_destroy(pt_elem);
}

typedef struct _tag_test_basic_string_init_copy__successfully_user_define
{
    int n_elem;
}_test_basic_string_init_copy__successfully_user_define_t;
void test_basic_string_init_copy__successfully_user_define_empty(void** state)
{
    basic_string_t* pt_dest = NULL;
    basic_string_t* pt_src = NULL;
    type_register(_test_basic_string_init_copy__successfully_user_define_t, NULL, NULL, NULL, NULL);
    pt_dest = create_basic_string(_test_basic_string_init_copy__successfully_user_define_t);
    pt_src = create_basic_string(_test_basic_string_init_copy__successfully_user_define_t);
    basic_string_init(pt_src);

    basic_string_init_copy(pt_dest, pt_src);
    assert_true(basic_string_size(pt_dest) == basic_string_size(pt_src));
    assert_true(basic_string_capacity(pt_dest) == 0);

    basic_string_destroy(pt_dest);
    basic_string_destroy(pt_src);
}

void test_basic_string_init_copy__successfully_user_define_little(void** state)
{
    size_t i = 0;
    _test_basic_string_init_copy__successfully_user_define_t t_user;
    basic_string_t* pt_dest = create_basic_string(_test_basic_string_init_copy__successfully_user_define_t);
    basic_string_t* pt_src = create_basic_string(_test_basic_string_init_copy__successfully_user_define_t);
    t_user.n_elem = 100;
    basic_string_init_elem(pt_src, 17, &t_user);

    basic_string_init_copy(pt_dest, pt_src);
    assert_true(basic_string_size(pt_dest) == basic_string_size(pt_src));
    assert_true(basic_string_capacity(pt_dest) == 33);
    for(i = 0; i < basic_string_size(pt_dest); ++i)
    {
        assert_true(memcmp(
            (_test_basic_string_init_copy__successfully_user_define_t*)basic_string_at(pt_dest, i), &t_user, sizeof(t_user)) == 0);
    }

    basic_string_destroy(pt_dest);
    basic_string_destroy(pt_src);
}

void test_basic_string_init_copy__successfully_user_define_huge(void** state)
{
    size_t i = 0;
    _test_basic_string_init_copy__successfully_user_define_t t_user;
    basic_string_t* pt_dest = create_basic_string(_test_basic_string_init_copy__successfully_user_define_t);
    basic_string_t* pt_src = create_basic_string(_test_basic_string_init_copy__successfully_user_define_t);
    t_user.n_elem = 100;
    basic_string_init_elem(pt_src, 11117, &t_user);

    basic_string_init_copy(pt_dest, pt_src);
    assert_true(basic_string_size(pt_dest) == basic_string_size(pt_src));
    assert_true(basic_string_capacity(pt_dest) == 16675);
    for(i = 0; i < basic_string_size(pt_dest); ++i)
    {
        assert_true(memcmp(
            (_test_basic_string_init_copy__successfully_user_define_t*)basic_string_at(pt_dest, i), &t_user, sizeof(t_user)) == 0);
    }

    basic_string_destroy(pt_dest);
    basic_string_destroy(pt_src);
}

/*
 * test basic_string_init_copy_substring
 */
UT_CASE_DEFINATION(basic_string_init_copy_substring)
void test_basic_string_init_copy_substring__null_dest(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(int);
    basic_string_init(pt_basic_string);

    expect_assert_failure(basic_string_init_copy_substring(NULL, pt_basic_string, 0, NPOS));

    basic_string_destroy(pt_basic_string);
}

void test_basic_string_init_copy_substring__null_src(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(int);

    expect_assert_failure(basic_string_init_copy_substring(pt_basic_string, NULL, 0, NPOS));

    basic_string_destroy(pt_basic_string);
}

void test_basic_string_init_copy_substring__non_create_dest(void** state)
{
    basic_string_t bstr;
    basic_string_t* pt_basic_string = create_basic_string(int);
    basic_string_init(pt_basic_string);

    bstr._t_vector._t_typeinfo._pt_type = NULL;
    expect_assert_failure(basic_string_init_copy_substring(&bstr, pt_basic_string, 0, NPOS));

    basic_string_destroy(pt_basic_string);
}

void test_basic_string_init_copy_substring__non_inited_src(void** state)
{
    basic_string_t* pt_dest = create_basic_string(int);
    basic_string_t* pt_src = create_basic_string(int);

    pt_src->_t_vector._pby_finish = (_byte_t*)0x732;
    expect_assert_failure(basic_string_init_copy_substring(pt_dest, pt_src, 0, NPOS));

    pt_src->_t_vector._pby_finish = NULL;
    basic_string_destroy(pt_dest);
    basic_string_destroy(pt_src);
}

void test_basic_string_init_copy_substring__not_same_type(void** state)
{
    basic_string_t* pt_dest = create_basic_string(int);
    basic_string_t* pt_src = create_basic_string(double);
    basic_string_init(pt_src);

    expect_assert_failure(basic_string_init_copy_substring(pt_dest, pt_src, 0, NPOS));

    basic_string_destroy(pt_dest);
    basic_string_destroy(pt_src);
}

void test_basic_string_init_copy_substring__successfully_c_builtin_src_non_empty_begin_empty(void** state)
{
    basic_string_t* pt_dest = create_basic_string(int);
    basic_string_t* pt_src = create_basic_string(int);
    basic_string_init_elem(pt_src, 10, 100);

    basic_string_init_copy_substring(pt_dest, pt_src, 0, 0);
    assert_true(basic_string_size(pt_dest) == 0);
    assert_true(basic_string_capacity(pt_dest) == 0);

    basic_string_destroy(pt_dest);
    basic_string_destroy(pt_src);
}

void test_basic_string_init_copy_substring__successfully_c_builtin_src_non_empty_begin_non_empty(void** state)
{
    int i = 0;
    basic_string_t* pt_dest = create_basic_string(int);
    basic_string_t* pt_src = create_basic_string(int);
    basic_string_init(pt_src);
    for(i = 0; i < 10; ++i)
    {
        basic_string_push_back(pt_src, i);
    }

    basic_string_init_copy_substring(pt_dest, pt_src, 0, 3);
    assert_true(basic_string_size(pt_dest) == 3);
    for(i = 0; i < basic_string_size(pt_dest); ++i)
    {
        assert_true(*(int*)basic_string_at(pt_dest, i) == i);
    }

    basic_string_destroy(pt_dest);
    basic_string_destroy(pt_src);
}

void test_basic_string_init_copy_substring__successfully_c_builtin_src_non_empty_begin_length(void** state)
{
    int i = 0;
    basic_string_t* pt_dest = create_basic_string(int);
    basic_string_t* pt_src = create_basic_string(int);
    basic_string_init(pt_src);
    for(i = 0; i < 10; ++i)
    {
        basic_string_push_back(pt_src, i);
    }

    basic_string_init_copy_substring(pt_dest, pt_src, 0, basic_string_length(pt_src));
    assert_true(basic_string_size(pt_dest) == basic_string_length(pt_src));
    for(i = 0; i < basic_string_size(pt_dest); ++i)
    {
        assert_true(*(int*)basic_string_at(pt_dest, i) == i);
    }

    basic_string_destroy(pt_dest);
    basic_string_destroy(pt_src);
}

void test_basic_string_init_copy_substring__successfully_c_builtin_src_non_empty_begin_npos(void** state)
{
    int i = 0;
    basic_string_t* pt_dest = create_basic_string(int);
    basic_string_t* pt_src = create_basic_string(int);
    basic_string_init(pt_src);
    for(i = 0; i < 10; ++i)
    {
        basic_string_push_back(pt_src, i);
    }

    basic_string_init_copy_substring(pt_dest, pt_src, 0, NPOS);
    assert_true(basic_string_size(pt_dest) == basic_string_length(pt_src));
    for(i = 0; i < basic_string_size(pt_dest); ++i)
    {
        assert_true(*(int*)basic_string_at(pt_dest, i) == i);
    }

    basic_string_destroy(pt_dest);
    basic_string_destroy(pt_src);
}

void test_basic_string_init_copy_substring__successfully_c_builtin_src_non_empty_middle_empty(void** state)
{
    int i = 0;
    basic_string_t* pt_dest = create_basic_string(int);
    basic_string_t* pt_src = create_basic_string(int);
    basic_string_init(pt_src);
    for(i = 0; i < 10; ++i)
    {
        basic_string_push_back(pt_src, i);
    }

    basic_string_init_copy_substring(pt_dest, pt_src, 3, 0);
    assert_true(basic_string_size(pt_dest) == 0);
    for(i = 0; i < basic_string_size(pt_dest); ++i)
    {
        assert_true(*(int*)basic_string_at(pt_dest, i) == i);
    }

    basic_string_destroy(pt_dest);
    basic_string_destroy(pt_src);
}

void test_basic_string_init_copy_substring__successfully_c_builtin_src_non_empty_middle_non_empty(void** state)
{
    int i = 0;
    basic_string_t* pt_dest = create_basic_string(int);
    basic_string_t* pt_src = create_basic_string(int);
    basic_string_init(pt_src);
    for(i = 0; i < 10; ++i)
    {
        basic_string_push_back(pt_src, i);
    }

    basic_string_init_copy_substring(pt_dest, pt_src, 3, 4);
    assert_true(basic_string_size(pt_dest) == 4);
    for(i = 0; i < basic_string_size(pt_dest); ++i)
    {
        assert_true(*(int*)basic_string_at(pt_dest, i) == i + 3);
    }

    basic_string_destroy(pt_dest);
    basic_string_destroy(pt_src);
}

void test_basic_string_init_copy_substring__successfully_c_builtin_src_non_empty_middle_length(void** state)
{
    int i = 0;
    basic_string_t* pt_dest = create_basic_string(int);
    basic_string_t* pt_src = create_basic_string(int);
    basic_string_init(pt_src);
    for(i = 0; i < 10; ++i)
    {
        basic_string_push_back(pt_src, i);
    }

    basic_string_init_copy_substring(pt_dest, pt_src, 3, basic_string_length(pt_src)-3);
    assert_true(basic_string_size(pt_dest) == 7);
    for(i = 0; i < basic_string_size(pt_dest); ++i)
    {
        assert_true(*(int*)basic_string_at(pt_dest, i) == i + 3);
    }

    basic_string_destroy(pt_dest);
    basic_string_destroy(pt_src);
}

void test_basic_string_init_copy_substring__successfully_c_builtin_src_non_empty_middle_npos(void** state)
{
    int i = 0;
    basic_string_t* pt_dest = create_basic_string(int);
    basic_string_t* pt_src = create_basic_string(int);
    basic_string_init(pt_src);
    for(i = 0; i < 10; ++i)
    {
        basic_string_push_back(pt_src, i);
    }

    basic_string_init_copy_substring(pt_dest, pt_src, 3, NPOS);
    assert_true(basic_string_size(pt_dest) == 7);
    for(i = 0; i < basic_string_size(pt_dest); ++i)
    {
        assert_true(*(int*)basic_string_at(pt_dest, i) == i + 3);
    }

    basic_string_destroy(pt_dest);
    basic_string_destroy(pt_src);
}

void test_basic_string_init_copy_substring__successfully_c_builtin_src_non_empty_end(void** state)
{
    int i = 0;
    basic_string_t* pt_dest = create_basic_string(int);
    basic_string_t* pt_src = create_basic_string(int);
    basic_string_init(pt_src);
    for(i = 0; i < 10; ++i)
    {
        basic_string_push_back(pt_src, i);
    }

    expect_assert_failure(basic_string_init_copy_substring(pt_dest, pt_src, basic_string_length(pt_src), NPOS));

    basic_string_destroy(pt_dest);
    basic_string_destroy(pt_src);
}

void test_basic_string_init_copy_substring__successfully_c_builtin_src_non_empty_npos(void** state)
{
    int i = 0;
    basic_string_t* pt_dest = create_basic_string(int);
    basic_string_t* pt_src = create_basic_string(int);
    basic_string_init(pt_src);
    for(i = 0; i < 10; ++i)
    {
        basic_string_push_back(pt_src, i);
    }

    expect_assert_failure(basic_string_init_copy_substring(pt_dest, pt_src, NPOS, NPOS));

    basic_string_destroy(pt_dest);
    basic_string_destroy(pt_src);
}

void test_basic_string_init_copy_substring__successfully_cstr_src_non_empty_begin_empty(void** state)
{
    basic_string_t* pt_dest = create_basic_string(char*);
    basic_string_t* pt_src = create_basic_string(char*);
    basic_string_init_elem(pt_src, 10, "abcdefg");

    basic_string_init_copy_substring(pt_dest, pt_src, 0, 0);
    assert_true(basic_string_size(pt_dest) == 0);
    assert_true(basic_string_capacity(pt_dest) == 0);

    basic_string_destroy(pt_dest);
    basic_string_destroy(pt_src);
}

void test_basic_string_init_copy_substring__successfully_cstr_src_non_empty_begin_non_empty(void** state)
{
    basic_string_t* pt_dest = create_basic_string(char*);
    basic_string_t* pt_src = create_basic_string(char*);
    basic_string_init(pt_src);
    basic_string_push_back(pt_src, "abc");
    basic_string_push_back(pt_src, "def");
    basic_string_push_back(pt_src, "hij");
    basic_string_push_back(pt_src, "klm");
    basic_string_push_back(pt_src, "nop");

    basic_string_init_copy_substring(pt_dest, pt_src, 0, 3);
    assert_true(basic_string_size(pt_dest) == 3);
    assert_true(strcmp((char*)basic_string_at(pt_dest, 0), "abc") == 0);
    assert_true(strcmp((char*)basic_string_at(pt_dest, 1), "def") == 0);
    assert_true(strcmp((char*)basic_string_at(pt_dest, 2), "hij") == 0);

    basic_string_destroy(pt_dest);
    basic_string_destroy(pt_src);
}

void test_basic_string_init_copy_substring__successfully_cstr_src_non_empty_begin_length(void** state)
{
    basic_string_t* pt_dest = create_basic_string(char*);
    basic_string_t* pt_src = create_basic_string(char*);
    basic_string_init(pt_src);
    basic_string_push_back(pt_src, "abc");
    basic_string_push_back(pt_src, "def");
    basic_string_push_back(pt_src, "hij");
    basic_string_push_back(pt_src, "klm");
    basic_string_push_back(pt_src, "nop");

    basic_string_init_copy_substring(pt_dest, pt_src, 0, basic_string_length(pt_src));
    assert_true(basic_string_size(pt_dest) == 5);
    assert_true(strcmp((char*)basic_string_at(pt_dest, 0), "abc") == 0);
    assert_true(strcmp((char*)basic_string_at(pt_dest, 1), "def") == 0);
    assert_true(strcmp((char*)basic_string_at(pt_dest, 2), "hij") == 0);
    assert_true(strcmp((char*)basic_string_at(pt_dest, 3), "klm") == 0);
    assert_true(strcmp((char*)basic_string_at(pt_dest, 4), "nop") == 0);

    basic_string_destroy(pt_dest);
    basic_string_destroy(pt_src);
}

void test_basic_string_init_copy_substring__successfully_cstr_src_non_empty_begin_npos(void** state)
{
    basic_string_t* pt_dest = create_basic_string(char*);
    basic_string_t* pt_src = create_basic_string(char*);
    basic_string_init(pt_src);
    basic_string_push_back(pt_src, "abc");
    basic_string_push_back(pt_src, "def");
    basic_string_push_back(pt_src, "hij");
    basic_string_push_back(pt_src, "klm");
    basic_string_push_back(pt_src, "nop");

    basic_string_init_copy_substring(pt_dest, pt_src, 0, NPOS);
    assert_true(basic_string_size(pt_dest) == 5);
    assert_true(strcmp((char*)basic_string_at(pt_dest, 0), "abc") == 0);
    assert_true(strcmp((char*)basic_string_at(pt_dest, 1), "def") == 0);
    assert_true(strcmp((char*)basic_string_at(pt_dest, 2), "hij") == 0);
    assert_true(strcmp((char*)basic_string_at(pt_dest, 3), "klm") == 0);
    assert_true(strcmp((char*)basic_string_at(pt_dest, 4), "nop") == 0);

    basic_string_destroy(pt_dest);
    basic_string_destroy(pt_src);
}

void test_basic_string_init_copy_substring__successfully_cstr_src_non_empty_middle_empty(void** state)
{
    basic_string_t* pt_dest = create_basic_string(char*);
    basic_string_t* pt_src = create_basic_string(char*);
    basic_string_init(pt_src);
    basic_string_push_back(pt_src, "abc");
    basic_string_push_back(pt_src, "def");
    basic_string_push_back(pt_src, "hij");
    basic_string_push_back(pt_src, "klm");
    basic_string_push_back(pt_src, "nop");

    basic_string_init_copy_substring(pt_dest, pt_src, 2, 0);
    assert_true(basic_string_size(pt_dest) == 0);

    basic_string_destroy(pt_dest);
    basic_string_destroy(pt_src);
}

void test_basic_string_init_copy_substring__successfully_cstr_src_non_empty_middle_non_empty(void** state)
{
    basic_string_t* pt_dest = create_basic_string(char*);
    basic_string_t* pt_src = create_basic_string(char*);
    basic_string_init(pt_src);
    basic_string_push_back(pt_src, "abc");
    basic_string_push_back(pt_src, "def");
    basic_string_push_back(pt_src, "hij");
    basic_string_push_back(pt_src, "klm");
    basic_string_push_back(pt_src, "nop");

    basic_string_init_copy_substring(pt_dest, pt_src, 2, 2);
    assert_true(basic_string_size(pt_dest) == 2);
    assert_true(strcmp((char*)basic_string_at(pt_dest, 0), "hij") == 0);
    assert_true(strcmp((char*)basic_string_at(pt_dest, 1), "klm") == 0);

    basic_string_destroy(pt_dest);
    basic_string_destroy(pt_src);
}

void test_basic_string_init_copy_substring__successfully_cstr_src_non_empty_middle_length(void** state)
{
    basic_string_t* pt_dest = create_basic_string(char*);
    basic_string_t* pt_src = create_basic_string(char*);
    basic_string_init(pt_src);
    basic_string_push_back(pt_src, "abc");
    basic_string_push_back(pt_src, "def");
    basic_string_push_back(pt_src, "hij");
    basic_string_push_back(pt_src, "klm");
    basic_string_push_back(pt_src, "nop");

    basic_string_init_copy_substring(pt_dest, pt_src, 2, 3);
    assert_true(basic_string_size(pt_dest) == 3);
    assert_true(strcmp((char*)basic_string_at(pt_dest, 0), "hij") == 0);
    assert_true(strcmp((char*)basic_string_at(pt_dest, 1), "klm") == 0);
    assert_true(strcmp((char*)basic_string_at(pt_dest, 2), "nop") == 0);

    basic_string_destroy(pt_dest);
    basic_string_destroy(pt_src);
}

void test_basic_string_init_copy_substring__successfully_cstr_src_non_empty_middle_npos(void** state)
{
    basic_string_t* pt_dest = create_basic_string(char*);
    basic_string_t* pt_src = create_basic_string(char*);
    basic_string_init(pt_src);
    basic_string_push_back(pt_src, "abc");
    basic_string_push_back(pt_src, "def");
    basic_string_push_back(pt_src, "hij");
    basic_string_push_back(pt_src, "klm");
    basic_string_push_back(pt_src, "nop");

    basic_string_init_copy_substring(pt_dest, pt_src, 2, NPOS);
    assert_true(basic_string_size(pt_dest) == 3);
    assert_true(strcmp((char*)basic_string_at(pt_dest, 0), "hij") == 0);
    assert_true(strcmp((char*)basic_string_at(pt_dest, 1), "klm") == 0);
    assert_true(strcmp((char*)basic_string_at(pt_dest, 2), "nop") == 0);

    basic_string_destroy(pt_dest);
    basic_string_destroy(pt_src);
}

void test_basic_string_init_copy_substring__successfully_cstr_src_non_empty_end(void** state)
{
    basic_string_t* pt_dest = create_basic_string(char*);
    basic_string_t* pt_src = create_basic_string(char*);
    basic_string_init(pt_src);
    basic_string_push_back(pt_src, "abc");
    basic_string_push_back(pt_src, "def");
    basic_string_push_back(pt_src, "hij");
    basic_string_push_back(pt_src, "klm");
    basic_string_push_back(pt_src, "nop");

    expect_assert_failure(basic_string_init_copy_substring(pt_dest, pt_src, basic_string_length(pt_src), 0));

    basic_string_destroy(pt_dest);
    basic_string_destroy(pt_src);
}

void test_basic_string_init_copy_substring__successfully_cstr_src_non_empty_npos(void** state)
{
    basic_string_t* pt_dest = create_basic_string(char*);
    basic_string_t* pt_src = create_basic_string(char*);
    basic_string_init(pt_src);
    basic_string_push_back(pt_src, "abc");
    basic_string_push_back(pt_src, "def");
    basic_string_push_back(pt_src, "hij");
    basic_string_push_back(pt_src, "klm");
    basic_string_push_back(pt_src, "nop");

    expect_assert_failure(basic_string_init_copy_substring(pt_dest, pt_src, NPOS, 0));

    basic_string_destroy(pt_dest);
    basic_string_destroy(pt_src);
}

void test_basic_string_init_copy_substring__successfully_cstl_builtin_src_non_empty_begin_empty(void** state)
{
    int i = 0;
    basic_string_t* pt_dest = create_basic_string(list_t<int>);
    basic_string_t* pt_src = create_basic_string(list_t<int>);
    list_t* pt_elem = create_list(int);
    list_init(pt_elem);
    basic_string_init(pt_src);

    for(i = 0; i < 10; ++i)
    {
        list_clear(pt_elem);
        list_push_back(pt_elem, i);
        basic_string_push_back(pt_src, pt_elem);
    }

    basic_string_init_copy_substring(pt_dest, pt_src, 0, 0);
    assert_true(basic_string_size(pt_dest) == 0);

    basic_string_destroy(pt_dest);
    basic_string_destroy(pt_src);
    list_destroy(pt_elem);
}

void test_basic_string_init_copy_substring__successfully_cstl_builtin_non_empty_begin_non_empty(void** state)
{
    size_t i = 0;
    basic_string_t* pt_dest = create_basic_string(list_t<int>);
    basic_string_t* pt_src = create_basic_string(list_t<int>);
    list_t* pt_elem = create_list(int);
    list_init(pt_elem);
    basic_string_init(pt_src);

    for(i = 0; i < 10; ++i)
    {
        list_clear(pt_elem);
        list_push_back(pt_elem, i);
        basic_string_push_back(pt_src, pt_elem);
    }

    basic_string_init_copy_substring(pt_dest, pt_src, 0, 2);
    assert_true(basic_string_size(pt_dest) == 2);
    for(i = 0; i < basic_string_size(pt_dest); ++i)
    {
        assert_true(*(int*)list_front((list_t*)basic_string_at(pt_dest, i)) == i);
    }

    basic_string_destroy(pt_dest);
    basic_string_destroy(pt_src);
    list_destroy(pt_elem);
}

void test_basic_string_init_copy_substring__successfully_cstl_builtin_non_empty_begin_length(void** state)
{
    size_t i = 0;
    basic_string_t* pt_dest = create_basic_string(list_t<int>);
    basic_string_t* pt_src = create_basic_string(list_t<int>);
    list_t* pt_elem = create_list(int);
    list_init(pt_elem);
    basic_string_init(pt_src);

    for(i = 0; i < 10; ++i)
    {
        list_clear(pt_elem);
        list_push_back(pt_elem, i);
        basic_string_push_back(pt_src, pt_elem);
    }

    basic_string_init_copy_substring(pt_dest, pt_src, 0, basic_string_length(pt_src));
    assert_true(basic_string_size(pt_dest) == 10);
    for(i = 0; i < basic_string_size(pt_dest); ++i)
    {
        assert_true(*(int*)list_front((list_t*)basic_string_at(pt_dest, i)) == i);
    }

    basic_string_destroy(pt_dest);
    basic_string_destroy(pt_src);
    list_destroy(pt_elem);
}

void test_basic_string_init_copy_substring__successfully_cstl_builtin_non_empty_begin_npos(void** state)
{
    size_t i = 0;
    basic_string_t* pt_dest = create_basic_string(list_t<int>);
    basic_string_t* pt_src = create_basic_string(list_t<int>);
    list_t* pt_elem = create_list(int);
    list_init(pt_elem);
    basic_string_init(pt_src);

    for(i = 0; i < 10; ++i)
    {
        list_clear(pt_elem);
        list_push_back(pt_elem, i);
        basic_string_push_back(pt_src, pt_elem);
    }

    basic_string_init_copy_substring(pt_dest, pt_src, 0, NPOS);
    assert_true(basic_string_size(pt_dest) == 10);
    for(i = 0; i < basic_string_size(pt_dest); ++i)
    {
        assert_true(*(int*)list_front((list_t*)basic_string_at(pt_dest, i)) == i);
    }

    basic_string_destroy(pt_dest);
    basic_string_destroy(pt_src);
    list_destroy(pt_elem);
}

void test_basic_string_init_copy_substring__successfully_cstl_builtin_non_empty_middle_empty(void** state)
{
    size_t i = 0;
    basic_string_t* pt_dest = create_basic_string(list_t<int>);
    basic_string_t* pt_src = create_basic_string(list_t<int>);
    list_t* pt_elem = create_list(int);
    list_init(pt_elem);
    basic_string_init(pt_src);

    for(i = 0; i < 10; ++i)
    {
        list_clear(pt_elem);
        list_push_back(pt_elem, i);
        basic_string_push_back(pt_src, pt_elem);
    }

    basic_string_init_copy_substring(pt_dest, pt_src, 3, 0);
    assert_true(basic_string_size(pt_dest) == 0);

    basic_string_destroy(pt_dest);
    basic_string_destroy(pt_src);
    list_destroy(pt_elem);
}

void test_basic_string_init_copy_substring__successfully_cstl_builtin_non_empty_middle_non_empty(void** state)
{
    size_t i = 0;
    basic_string_t* pt_dest = create_basic_string(list_t<int>);
    basic_string_t* pt_src = create_basic_string(list_t<int>);
    list_t* pt_elem = create_list(int);
    list_init(pt_elem);
    basic_string_init(pt_src);

    for(i = 0; i < 10; ++i)
    {
        list_clear(pt_elem);
        list_push_back(pt_elem, i);
        basic_string_push_back(pt_src, pt_elem);
    }

    basic_string_init_copy_substring(pt_dest, pt_src, 3, 3);
    assert_true(basic_string_size(pt_dest) == 3);
    for(i = 0; i < basic_string_size(pt_dest); ++i)
    {
        assert_true(*(int*)list_front((list_t*)basic_string_at(pt_dest, i)) == i + 3);
    }

    basic_string_destroy(pt_dest);
    basic_string_destroy(pt_src);
    list_destroy(pt_elem);
}

void test_basic_string_init_copy_substring__successfully_cstl_builtin_non_empty_middle_length(void** state)
{
    size_t i = 0;
    basic_string_t* pt_dest = create_basic_string(list_t<int>);
    basic_string_t* pt_src = create_basic_string(list_t<int>);
    list_t* pt_elem = create_list(int);
    list_init(pt_elem);
    basic_string_init(pt_src);

    for(i = 0; i < 10; ++i)
    {
        list_clear(pt_elem);
        list_push_back(pt_elem, i);
        basic_string_push_back(pt_src, pt_elem);
    }

    basic_string_init_copy_substring(pt_dest, pt_src, 3, basic_string_length(pt_src));
    assert_true(basic_string_size(pt_dest) == 7);
    for(i = 0; i < basic_string_size(pt_dest); ++i)
    {
        assert_true(*(int*)list_front((list_t*)basic_string_at(pt_dest, i)) == i + 3);
    }

    basic_string_destroy(pt_dest);
    basic_string_destroy(pt_src);
    list_destroy(pt_elem);
}

void test_basic_string_init_copy_substring__successfully_cstl_builtin_non_empty_middle_npos(void** state)
{
    size_t i = 0;
    basic_string_t* pt_dest = create_basic_string(list_t<int>);
    basic_string_t* pt_src = create_basic_string(list_t<int>);
    list_t* pt_elem = create_list(int);
    list_init(pt_elem);
    basic_string_init(pt_src);

    for(i = 0; i < 10; ++i)
    {
        list_clear(pt_elem);
        list_push_back(pt_elem, i);
        basic_string_push_back(pt_src, pt_elem);
    }

    basic_string_init_copy_substring(pt_dest, pt_src, 3, NPOS);
    assert_true(basic_string_size(pt_dest) == 7);
    for(i = 0; i < basic_string_size(pt_dest); ++i)
    {
        assert_true(*(int*)list_front((list_t*)basic_string_at(pt_dest, i)) == i + 3);
    }

    basic_string_destroy(pt_dest);
    basic_string_destroy(pt_src);
    list_destroy(pt_elem);
}

void test_basic_string_init_copy_substring__successfully_cstl_builtin_length(void** state)
{
    size_t i = 0;
    basic_string_t* pt_dest = create_basic_string(list_t<int>);
    basic_string_t* pt_src = create_basic_string(list_t<int>);
    list_t* pt_elem = create_list(int);
    list_init(pt_elem);
    basic_string_init(pt_src);

    for(i = 0; i < 10; ++i)
    {
        list_clear(pt_elem);
        list_push_back(pt_elem, i);
        basic_string_push_back(pt_src, pt_elem);
    }

    expect_assert_failure(basic_string_init_copy_substring(pt_dest, pt_src, basic_string_length(pt_src), NPOS));

    basic_string_destroy(pt_dest);
    basic_string_destroy(pt_src);
    list_destroy(pt_elem);
}

void test_basic_string_init_copy_substring__successfully_cstl_builtin_npos(void** state)
{
    size_t i = 0;
    basic_string_t* pt_dest = create_basic_string(list_t<int>);
    basic_string_t* pt_src = create_basic_string(list_t<int>);
    list_t* pt_elem = create_list(int);
    list_init(pt_elem);
    basic_string_init(pt_src);

    for(i = 0; i < 10; ++i)
    {
        list_clear(pt_elem);
        list_push_back(pt_elem, i);
        basic_string_push_back(pt_src, pt_elem);
    }

    expect_assert_failure(basic_string_init_copy_substring(pt_dest, pt_src, NPOS, NPOS));

    basic_string_destroy(pt_dest);
    basic_string_destroy(pt_src);
    list_destroy(pt_elem);
}

typedef struct _tag_test_basic_string_init_copy_substring__successfully_user_define
{
    int n_elem;
}_test_basic_string_init_copy_substring__successfully_user_define_t;
void test_basic_string_init_copy_substring__successfully_user_define_non_empty_begin_empty(void** state)
{
    size_t i = 0;
    _test_basic_string_init_copy_substring__successfully_user_define_t t_user;
    basic_string_t* pt_dest = NULL;
    basic_string_t* pt_src = NULL;
    type_register(_test_basic_string_init_copy_substring__successfully_user_define_t, NULL, NULL, NULL, NULL);
    pt_dest = create_basic_string(_test_basic_string_init_copy_substring__successfully_user_define_t);
    pt_src = create_basic_string(_test_basic_string_init_copy_substring__successfully_user_define_t);
    basic_string_init(pt_src);
    for(i = 0; i < 10; ++i)
    {
        t_user.n_elem = i;
        basic_string_push_back(pt_src, &t_user);
    }

    basic_string_init_copy_substring(pt_dest, pt_src, 0, 0);
    assert_true(basic_string_size(pt_dest) == 0);

    basic_string_destroy(pt_dest);
    basic_string_destroy(pt_src);
}

void test_basic_string_init_copy_substring__successfully_user_define_non_empty_begin_non_empty(void** state)
{
    size_t i = 0;
    _test_basic_string_init_copy_substring__successfully_user_define_t t_user;
    basic_string_t* pt_dest = create_basic_string(_test_basic_string_init_copy_substring__successfully_user_define_t);
    basic_string_t* pt_src = create_basic_string(_test_basic_string_init_copy_substring__successfully_user_define_t);
    basic_string_init(pt_src);
    for(i = 0; i < 10; ++i)
    {
        t_user.n_elem = i;
        basic_string_push_back(pt_src, &t_user);
    }

    basic_string_init_copy_substring(pt_dest, pt_src, 0, 3);
    assert_true(basic_string_size(pt_dest) == 3);
    for(i = 0; i < basic_string_size(pt_dest); ++i)
    {
        assert_true(((_test_basic_string_init_copy_substring__successfully_user_define_t*)
            basic_string_at(pt_dest, i))->n_elem == i);
    }

    basic_string_destroy(pt_dest);
    basic_string_destroy(pt_src);
}

void test_basic_string_init_copy_substring__successfully_user_define_non_empty_begin_length(void** state)
{
    size_t i = 0;
    _test_basic_string_init_copy_substring__successfully_user_define_t t_user;
    basic_string_t* pt_dest = create_basic_string(_test_basic_string_init_copy_substring__successfully_user_define_t);
    basic_string_t* pt_src = create_basic_string(_test_basic_string_init_copy_substring__successfully_user_define_t);
    basic_string_init(pt_src);
    for(i = 0; i < 10; ++i)
    {
        t_user.n_elem = i;
        basic_string_push_back(pt_src, &t_user);
    }

    basic_string_init_copy_substring(pt_dest, pt_src, 0, basic_string_length(pt_src));
    assert_true(basic_string_size(pt_dest) == 10);
    for(i = 0; i < basic_string_size(pt_dest); ++i)
    {
        assert_true(((_test_basic_string_init_copy_substring__successfully_user_define_t*)
            basic_string_at(pt_dest, i))->n_elem == i);
    }

    basic_string_destroy(pt_dest);
    basic_string_destroy(pt_src);
}

void test_basic_string_init_copy_substring__successfully_user_define_non_empty_begin_npos(void** state)
{
    size_t i = 0;
    _test_basic_string_init_copy_substring__successfully_user_define_t t_user;
    basic_string_t* pt_dest = create_basic_string(_test_basic_string_init_copy_substring__successfully_user_define_t);
    basic_string_t* pt_src = create_basic_string(_test_basic_string_init_copy_substring__successfully_user_define_t);
    basic_string_init(pt_src);
    for(i = 0; i < 10; ++i)
    {
        t_user.n_elem = i;
        basic_string_push_back(pt_src, &t_user);
    }

    basic_string_init_copy_substring(pt_dest, pt_src, 0, NPOS);
    assert_true(basic_string_size(pt_dest) == 10);
    for(i = 0; i < basic_string_size(pt_dest); ++i)
    {
        assert_true(((_test_basic_string_init_copy_substring__successfully_user_define_t*)
            basic_string_at(pt_dest, i))->n_elem == i);
    }

    basic_string_destroy(pt_dest);
    basic_string_destroy(pt_src);
}

void test_basic_string_init_copy_substring__successfully_user_define_non_empty_middle_empty(void** state)
{
    size_t i = 0;
    _test_basic_string_init_copy_substring__successfully_user_define_t t_user;
    basic_string_t* pt_dest = create_basic_string(_test_basic_string_init_copy_substring__successfully_user_define_t);
    basic_string_t* pt_src = create_basic_string(_test_basic_string_init_copy_substring__successfully_user_define_t);
    basic_string_init(pt_src);
    for(i = 0; i < 10; ++i)
    {
        t_user.n_elem = i;
        basic_string_push_back(pt_src, &t_user);
    }

    basic_string_init_copy_substring(pt_dest, pt_src, 3, 0);
    assert_true(basic_string_size(pt_dest) == 0);

    basic_string_destroy(pt_dest);
    basic_string_destroy(pt_src);
}

void test_basic_string_init_copy_substring__successfully_user_define_non_empty_middle_non_empty(void** state)
{
    size_t i = 0;
    _test_basic_string_init_copy_substring__successfully_user_define_t t_user;
    basic_string_t* pt_dest = create_basic_string(_test_basic_string_init_copy_substring__successfully_user_define_t);
    basic_string_t* pt_src = create_basic_string(_test_basic_string_init_copy_substring__successfully_user_define_t);
    basic_string_init(pt_src);
    for(i = 0; i < 10; ++i)
    {
        t_user.n_elem = i;
        basic_string_push_back(pt_src, &t_user);
    }

    basic_string_init_copy_substring(pt_dest, pt_src, 3, 3);
    assert_true(basic_string_size(pt_dest) == 3);
    for(i = 0; i < basic_string_size(pt_dest); ++i)
    {
        assert_true(((_test_basic_string_init_copy_substring__successfully_user_define_t*)
            basic_string_at(pt_dest, i))->n_elem == i + 3);
    }

    basic_string_destroy(pt_dest);
    basic_string_destroy(pt_src);
}

void test_basic_string_init_copy_substring__successfully_user_define_non_empty_middle_length(void** state)
{
    size_t i = 0;
    _test_basic_string_init_copy_substring__successfully_user_define_t t_user;
    basic_string_t* pt_dest = create_basic_string(_test_basic_string_init_copy_substring__successfully_user_define_t);
    basic_string_t* pt_src = create_basic_string(_test_basic_string_init_copy_substring__successfully_user_define_t);
    basic_string_init(pt_src);
    for(i = 0; i < 10; ++i)
    {
        t_user.n_elem = i;
        basic_string_push_back(pt_src, &t_user);
    }

    basic_string_init_copy_substring(pt_dest, pt_src, 3, basic_string_length(pt_src));
    assert_true(basic_string_size(pt_dest) == 7);
    for(i = 0; i < basic_string_size(pt_dest); ++i)
    {
        assert_true(((_test_basic_string_init_copy_substring__successfully_user_define_t*)
            basic_string_at(pt_dest, i))->n_elem == i + 3);
    }

    basic_string_destroy(pt_dest);
    basic_string_destroy(pt_src);
}

void test_basic_string_init_copy_substring__successfully_user_define_non_empty_middle_npos(void** state)
{
    size_t i = 0;
    _test_basic_string_init_copy_substring__successfully_user_define_t t_user;
    basic_string_t* pt_dest = create_basic_string(_test_basic_string_init_copy_substring__successfully_user_define_t);
    basic_string_t* pt_src = create_basic_string(_test_basic_string_init_copy_substring__successfully_user_define_t);
    basic_string_init(pt_src);
    for(i = 0; i < 10; ++i)
    {
        t_user.n_elem = i;
        basic_string_push_back(pt_src, &t_user);
    }

    basic_string_init_copy_substring(pt_dest, pt_src, 3, NPOS);
    assert_true(basic_string_size(pt_dest) == 7);
    for(i = 0; i < basic_string_size(pt_dest); ++i)
    {
        assert_true(((_test_basic_string_init_copy_substring__successfully_user_define_t*)
            basic_string_at(pt_dest, i))->n_elem == i + 3);
    }

    basic_string_destroy(pt_dest);
    basic_string_destroy(pt_src);
}

void test_basic_string_init_copy_substring__successfully_user_define_non_empty_end(void** state)
{
    size_t i = 0;
    _test_basic_string_init_copy_substring__successfully_user_define_t t_user;
    basic_string_t* pt_dest = create_basic_string(_test_basic_string_init_copy_substring__successfully_user_define_t);
    basic_string_t* pt_src = create_basic_string(_test_basic_string_init_copy_substring__successfully_user_define_t);
    basic_string_init(pt_src);
    for(i = 0; i < 10; ++i)
    {
        t_user.n_elem = i;
        basic_string_push_back(pt_src, &t_user);
    }

    expect_assert_failure(basic_string_init_copy_substring(pt_dest, pt_src, basic_string_length(pt_src), NPOS));

    basic_string_destroy(pt_dest);
    basic_string_destroy(pt_src);
}

void test_basic_string_init_copy_substring__successfully_user_define_non_empty_npos(void** state)
{
    size_t i = 0;
    _test_basic_string_init_copy_substring__successfully_user_define_t t_user;
    basic_string_t* pt_dest = create_basic_string(_test_basic_string_init_copy_substring__successfully_user_define_t);
    basic_string_t* pt_src = create_basic_string(_test_basic_string_init_copy_substring__successfully_user_define_t);
    basic_string_init(pt_src);
    for(i = 0; i < 10; ++i)
    {
        t_user.n_elem = i;
        basic_string_push_back(pt_src, &t_user);
    }

    expect_assert_failure(basic_string_init_copy_substring(pt_dest, pt_src, NPOS, NPOS));

    basic_string_destroy(pt_dest);
    basic_string_destroy(pt_src);
}

/*
 * test basic_string_init_copy_range
 */
UT_CASE_DEFINATION(basic_string_init_copy_range)
void test_basic_string_init_copy_range__null_dest(void** state)
{
    basic_string_t* pt = create_basic_string(int);
    basic_string_iterator_t it_begin;
    basic_string_iterator_t it_end;

    basic_string_init(pt);
    it_begin = basic_string_begin(pt);
    it_end = basic_string_end(pt);

    expect_assert_failure(basic_string_init_copy_range(NULL, it_begin, it_end));

    basic_string_destroy(pt);
}

void test_basic_string_init_copy_range__invalid_begin_iterator(void** state)
{
    basic_string_t* pt_dest = create_basic_string(int);
    basic_string_t* pt_src = create_basic_string(int);
    basic_string_iterator_t it_begin;
    basic_string_iterator_t it_end;

    basic_string_init(pt_src);
    it_begin = basic_string_begin(pt_src);
    it_end = basic_string_end(pt_src);

    it_begin._t_iteratortype = 23445;
    expect_assert_failure(basic_string_init_copy_range(pt_dest, it_begin, it_end));

    basic_string_destroy(pt_dest);
    basic_string_destroy(pt_src);
}

void test_basic_string_init_copy_range__invalid_end_iterator(void** state)
{
    basic_string_t* pt_dest = create_basic_string(int);
    basic_string_t* pt_src = create_basic_string(int);
    basic_string_iterator_t it_begin;
    basic_string_iterator_t it_end;

    basic_string_init(pt_src);
    it_begin = basic_string_begin(pt_src);
    it_end = basic_string_end(pt_src);

    it_end._t_containertype = 9999;
    expect_assert_failure(basic_string_init_copy_range(pt_dest, it_begin, it_end));

    basic_string_destroy(pt_dest);
    basic_string_destroy(pt_src);
}

void test_basic_string_init_copy_range__invalid_range(void** state)
{
    basic_string_t* pt_dest = create_basic_string(int);
    basic_string_t* pt_src = create_basic_string(int);
    basic_string_iterator_t it_begin;
    basic_string_iterator_t it_end;

    basic_string_init_elem(pt_src, 19, 323);
    it_begin = basic_string_begin(pt_src);
    it_end = basic_string_end(pt_src);

    expect_assert_failure(basic_string_init_copy_range(pt_dest, it_end, it_begin));

    basic_string_destroy(pt_dest);
    basic_string_destroy(pt_src);
}

void test_basic_string_init_copy_range__not_same_type(void** state)
{
    basic_string_t* pt_dest = create_basic_string(int);
    basic_string_t* pt_src = create_basic_string(double);
    basic_string_iterator_t it_begin;
    basic_string_iterator_t it_end;

    basic_string_init_elem(pt_src, 19, 323);
    it_begin = basic_string_begin(pt_src);
    it_end = basic_string_end(pt_src);

    expect_assert_failure(basic_string_init_copy_range(pt_dest, it_begin, it_end));

    basic_string_destroy(pt_dest);
    basic_string_destroy(pt_src);
}

void test_basic_string_init_copy_range__successfully_empty_range(void** state)
{
    basic_string_t* pt_dest = create_basic_string(int);
    basic_string_t* pt_src = create_basic_string(int);
    basic_string_iterator_t it_begin;
    basic_string_iterator_t it_end;

    basic_string_init_elem(pt_src, 19, 323);
    it_begin = basic_string_begin(pt_src);
    it_end = basic_string_end(pt_src);

    basic_string_init_copy_range(pt_dest, it_begin, it_begin);
    assert_true(basic_string_size(pt_dest) == 0);
    assert_true(basic_string_capacity(pt_dest) == 0);

    basic_string_destroy(pt_dest);
    basic_string_destroy(pt_src);
}

void test_basic_string_init_copy_range__successfully_c_builtin(void** state)
{
    size_t i = 0;
    basic_string_t* pt_dest = create_basic_string(int);
    basic_string_t* pt_src = create_basic_string(int);
    basic_string_iterator_t it_begin;
    basic_string_iterator_t it_end;

    basic_string_init(pt_src);
    for(i = 0; i < 10; ++i)
    {
        basic_string_push_back(pt_src, i);
    }
    it_begin = iterator_next_n(basic_string_begin(pt_src), 3);
    it_end = iterator_next_n(it_begin, 5);

    basic_string_init_copy_range(pt_dest, it_begin, it_end);
    assert_true(basic_string_size(pt_dest) == iterator_distance(it_begin, it_end));
    assert_true(basic_string_capacity(pt_dest) == 21);
    for(i = 0; i < basic_string_size(pt_dest); ++i)
    {
        assert_true(*(int*)basic_string_at(pt_dest, i) == i + 3);
    }

    basic_string_destroy(pt_dest);
    basic_string_destroy(pt_src);
}

void test_basic_string_init_copy_range__successfully_cstr(void** state)
{
    size_t i = 0;
    basic_string_t* pt_dest = create_basic_string(char*);
    basic_string_t* pt_src = create_basic_string(char*);
    basic_string_iterator_t it_begin;
    basic_string_iterator_t it_end;

    basic_string_init_elem(pt_src, 100, "abcdefg");
    it_begin = basic_string_begin(pt_src);
    it_end = iterator_next_n(it_begin, 10);

    basic_string_init_copy_range(pt_dest, it_begin, it_end);
    assert_true(basic_string_size(pt_dest) == iterator_distance(it_begin, it_end));
    assert_true(basic_string_capacity(pt_dest) == 26);
    for(i = 0; i < basic_string_size(pt_dest); ++i)
    {
        assert_true(strcmp((char*)basic_string_at(pt_dest, i), "abcdefg") == 0);
    }

    basic_string_destroy(pt_dest);
    basic_string_destroy(pt_src);
}

void test_basic_string_init_copy_range__successfully_cstl_builtin(void** state)
{
    size_t i = 0;
    basic_string_t* pt_dest = create_basic_string(list_t<int>);
    basic_string_t* pt_src = create_basic_string(list_t<int>);
    list_t* pt_elem = create_list(int);
    basic_string_iterator_t it_begin;
    basic_string_iterator_t it_end;

    list_init_elem(pt_elem, 18, 23);
    basic_string_init_elem(pt_src, 1004, pt_elem);
    it_begin = iterator_next_n(basic_string_begin(pt_src), 100);
    it_end = basic_string_end(pt_src);

    basic_string_init_copy_range(pt_dest, it_begin, it_end);
    assert_true(basic_string_size(pt_dest) == iterator_distance(it_begin, it_end));
    assert_true(basic_string_capacity(pt_dest) == 1356);
    for(i = 0; i < basic_string_size(pt_dest); ++i)
    {
        assert_true(list_equal((list_t*)basic_string_at(pt_dest, i), pt_elem));
    }

    basic_string_destroy(pt_dest);
    basic_string_destroy(pt_src);
    list_destroy(pt_elem);
}

void test_basic_string_init_copy_range__successfully_user_define(void** state)
{
    typedef struct _tag_test_basic_string_init_copy_range__successfully_user_define
    {
        int n_elem;
    }_test_basic_string_init_copy_range__successfully_user_define_t;

    size_t i = 0;
    basic_string_t* pt_dest = NULL;
    basic_string_t* pt_src = NULL;
    basic_string_iterator_t it_begin;
    basic_string_iterator_t it_end;
    _test_basic_string_init_copy_range__successfully_user_define_t t_user;

    type_register(_test_basic_string_init_copy_range__successfully_user_define_t, NULL, NULL, NULL, NULL);

    pt_dest = create_basic_string(_test_basic_string_init_copy_range__successfully_user_define_t);
    pt_src = create_basic_string(_test_basic_string_init_copy_range__successfully_user_define_t);

    t_user.n_elem = 28743;
    basic_string_init_elem(pt_src, 10000, &t_user);
    it_begin = basic_string_begin(pt_src);
    it_end = basic_string_end(pt_src);

    basic_string_init_copy_range(pt_dest, it_begin, it_end);
    assert_true(basic_string_size(pt_dest) == iterator_distance(it_begin, it_end));
    assert_true(basic_string_capacity(pt_dest) == 15000);
    for(i = 0; i < basic_string_size(pt_dest); ++i)
    {
        assert_true(memcmp((_test_basic_string_init_copy_range__successfully_user_define_t*)basic_string_at(pt_dest, i),
            &t_user, sizeof(t_user)) == 0);
    }

    basic_string_destroy(pt_dest);
    basic_string_destroy(pt_src);
}

/*
 * test basic_string_destroy
 */
UT_CASE_DEFINATION(basic_string_destroy)
void test_basic_string_destroy__null_basic_string_container(void** state)
{
    expect_assert_failure(basic_string_destroy(NULL));
}

void test_basic_string_destroy__non_created(void** state)
{
    basic_string_t bstr;
    bstr._t_vector._pby_start = (_byte_t*)0x37;

    expect_assert_failure(basic_string_destroy(&bstr));
}

void test_basic_string_destroy__created_non_inited(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(int);

    basic_string_destroy(pt_basic_string);
}

void test_basic_string_destroy__inited_empty(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(int);
    basic_string_init(pt_basic_string);

    basic_string_destroy(pt_basic_string);
}

void test_basic_string_destroy__inited_non_empty(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(int);
    basic_string_init_elem(pt_basic_string, 199, 100);

    basic_string_destroy(pt_basic_string);
}

/*
 * test basic_string_c_str
 */
UT_CASE_DEFINATION(basic_string_c_str)
void test_basic_string_c_string__null_container(void** state)
{
    expect_assert_failure(basic_string_c_str(NULL));
}

void test_basic_string_c_string__non_inited_container(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(int);

    pt_basic_string->_t_vector._t_typeinfo._t_style = 4566;
    expect_assert_failure(basic_string_c_str(pt_basic_string));

    pt_basic_string->_t_vector._t_typeinfo._t_style = _TYPE_C_BUILTIN;
    basic_string_destroy(pt_basic_string);
}

void test_basic_string_c_string__empty(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(int);

    basic_string_init(pt_basic_string);
    assert_true(basic_string_c_str(pt_basic_string) == NULL);

    basic_string_destroy(pt_basic_string);
}

void test_basic_string_c_string__non_empty(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(int);
    int* pn = NULL;

    basic_string_init(pt_basic_string);
    basic_string_push_back(pt_basic_string, 0);
    basic_string_push_back(pt_basic_string, 2);
    basic_string_push_back(pt_basic_string, 199);
    basic_string_push_back(pt_basic_string, 5);
    pn = (int*)basic_string_c_str(pt_basic_string);
    assert_true(pn != NULL);
    assert_true(pn[0] == 0);
    assert_true(pn[1] == 2);
    assert_true(pn[2] == 199);
    assert_true(pn[3] == 5);

    basic_string_destroy(pt_basic_string);
}

