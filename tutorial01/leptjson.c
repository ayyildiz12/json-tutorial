#include "leptjson.h"
#include <assert.h>  /* assert() 断言函数*/
#include <stdlib.h>  /* NULL */

//断言函数
#define EXPECT(c, ch)       do { assert(*c->json == (ch)); c->json++; } while(0)

//定义指向jason的指针，为了减少参数的传递，把所有参数传进去一个结构体
typedef struct {
    const char* json;
}lept_context;

//去除空字符函数，调用后会去除前面的空字符
//如果是空字符，就指针++，最后把指针的值赋值给json
static void lept_parse_whitespace(lept_context* c) {
    const char* p = c->json;
    while (*p == ' ' || *p == '\t' || *p == '\n' || *p == '\r')
        p++;
    c->json = p;
}

//解析null，带断言判断开头是不是n如果是，就判断后面的字符是不是ull，不是就返回无效是，是就返回null
static int lept_parse_null(lept_context* c, lept_value* v) {
    EXPECT(c, 'n');  //如果开头不是n直接退出程序
    if (c->json[0] != 'u' || c->json[1] != 'l' || c->json[2] != 'l')
        return LEPT_PARSE_INVALID_VALUE;   //返回判断失败标志
    c->json += 3;  // 指针跳转3格，指向后面的字符
    v->type = LEPT_NULL;    //设置判断结果类型
    return LEPT_PARSE_OK;    //返回测试通过标志
}

//解析开始函数
/* 提示：这里应该是 JSON-text = ws value wsjson这里传进来的是待解析的字符null等 */
//v是解析成功的预期返回值，json是待判断的字符null
/* 以下实现没处理最后的 ws 和 LEPT_PARSE_ROOT_NOT_SINGULAR */
int lept_parse(lept_value* v, const char* json) {
    lept_context c;     //定义一个指向jason的指针
    assert(v != NULL);  //如果预期值为空就终止程序
    c.json = json;   //赋值"null"给指针
    v->type = LEPT_NULL;  //默认v的值是LEPT_NULL
    lept_parse_whitespace(&c);  //先跳过前面的空格回车之类的空白符号，c指针最后指向第一个非空字符
    return lept_parse_value(&c, v);  //再判断json里面的值
}

//真正的解析函数，分情况开始解析json字符
//解析字符串，判断是否是null或者是字符串，不是就返回无效值
/* value = null / false / true */
//c=json v=LEPT_NULL
/* 提示：下面代码没处理 false / true，将会是练习之一 */
static int lept_parse_value(lept_context* c, lept_value* v) {
    switch (*c->json) {
    case 'n':  return lept_parse_null(c, v);
    case '\0': return LEPT_PARSE_EXPECT_VALUE;
    default:   return LEPT_PARSE_INVALID_VALUE;
    }
}


//返回结果类型
lept_type lept_get_type(const lept_value* v) {
    assert(v != NULL);   //如果返回的结果为空，中断程序
    return v->type;      //有返回的结果就返回该结果
}

