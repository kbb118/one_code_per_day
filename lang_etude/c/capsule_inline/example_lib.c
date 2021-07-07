#include "example_lib.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>

struct Test_ {
    int n;
    char* name;
};

Test*
test_new (int n,
          char* name)
{
    Test* ret = malloc(sizeof(Test));
    if ( !ret )
        assert(0 && "memory error");
    ret->n = n;
    ret->name = strdup(name);
    if ( !ret->name )
        assert(0 && "memory error");
    return ret;
}

/* この程度の関数は inline 化したいが
 * inline 化するとなるとヘッダに書かないと
 * いけないのでメンバーを隠蔽できなくなる。*/
char*
test_name (Test* test)
{
    return test->name;
}

int
mul_100 (Test* test)
{
    return test->n*100;
}

