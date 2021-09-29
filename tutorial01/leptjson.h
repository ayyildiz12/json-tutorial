#pragma once
#ifndef LEPTJSON_H__
#define LEPTJSON_H__


//先枚举lept_type六种数据类型
typedef enum { LEPT_NULL, LEPT_FALSE, LEPT_TRUE, LEPT_NUMBER, LEPT_STRING, LEPT_ARRAY, LEPT_OBJECT } lept_type;

//声明jason数据结构，一个jason节点
typedef struct {
    lept_type type;
}lept_value;

//枚举返回值类型
enum {
    LEPT_PARSE_OK = 0,
    LEPT_PARSE_EXPECT_VALUE,
    LEPT_PARSE_INVALID_VALUE,
    LEPT_PARSE_ROOT_NOT_SINGULAR
};

//声明两个函数
//解析jason函数
int lept_parse(lept_value* v, const char* json);

//访问结果函数，获取他的类型
lept_type lept_get_type(const lept_value* v);

#endif /* LEPTJSON_H__ */
