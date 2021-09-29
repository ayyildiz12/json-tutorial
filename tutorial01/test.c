#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "leptjson.h"

static int main_ret = 0;    //记录测试失败的次数
static int test_count = 0;  //记录测试的次数
static int test_pass = 0;   //记录测试通过的次数


//这是一个匿名函数，\代表该行未结束，串接下一行 do...while(0)代表只执行一次
// 两者的联系 printf("%s",stringVar) <===>fprintf(stdout,"%s",stringVar)
// format是输出格式，调用函数的时候会传进来，expct是期望值，actual是实际值第一个是条件
//作用：判断条件是否成立，如果不成立就输出第几行错误,正确就不输出
#define EXPECT_EQ_BASE(equality, expect, actual, format) \
    do {\
        test_count++;\
        if (equality)\
            test_pass++;\
        else {\
            fprintf(stderr, "%s:%d: expect: " format " actual: " format "\n", __FILE__, __LINE__, expect, actual);\
            printf("\r\n");\
             main_ret = 1;\
        }\
    } while(0)

//函数名替换，减少参数
//如果 expect != actual（预期值不等于实际值），程序就会输出错误信息
#define EXPECT_EQ_INT(expect, actual) EXPECT_EQ_BASE((expect) == (actual), expect, actual, "%d")

//测试null
static void test_parse_null() {
    lept_value v;   //定义一个临时的存放空间
    v.type = LEPT_FALSE;  //默认为解析错误
    EXPECT_EQ_INT(LEPT_PARSE_OK, lept_parse(&v, "null"));  //调用解析开始函数，判断返回值结果
    EXPECT_EQ_INT(LEPT_NULL, lept_get_type(&v));           //判断返回值结果
}

//测试空格换行
static void test_parse_expect_value() {
    lept_value v;

    v.type = LEPT_FALSE;
    EXPECT_EQ_INT(LEPT_PARSE_EXPECT_VALUE, lept_parse(&v, ""));
    EXPECT_EQ_INT(LEPT_NULL, lept_get_type(&v));

    v.type = LEPT_FALSE;
    EXPECT_EQ_INT(LEPT_PARSE_EXPECT_VALUE, lept_parse(&v, " "));
    EXPECT_EQ_INT(LEPT_NULL, lept_get_type(&v));
}

//测试无效值
static void test_parse_invalid_value() {
    lept_value v;
    v.type = LEPT_FALSE;
    EXPECT_EQ_INT(LEPT_PARSE_INVALID_VALUE, lept_parse(&v, "nul"));
    EXPECT_EQ_INT(LEPT_NULL, lept_get_type(&v));

    v.type = LEPT_FALSE;
    EXPECT_EQ_INT(LEPT_PARSE_INVALID_VALUE, lept_parse(&v, "?"));
    EXPECT_EQ_INT(LEPT_NULL, lept_get_type(&v));
}

//测试根节点不单一
static void test_parse_root_not_singular() {
    lept_value v;
    v.type = LEPT_FALSE;
    EXPECT_EQ_INT(LEPT_PARSE_ROOT_NOT_SINGULAR, lept_parse(&v, "null x"));
    EXPECT_EQ_INT(LEPT_NULL, lept_get_type(&v));
}

//总的调用函数，调用了四个测试函数
static void test_parse() {
    test_parse_null();
    test_parse_expect_value();
    test_parse_invalid_value();
    test_parse_root_not_singular();
}

int main() {
    test_parse();
    //输出测试通过的数量以及比例
    printf("%d/%d (%3.2f%%) passed\n", test_pass, test_count, test_pass * 100.0 / test_count);
    return main_ret;
}

