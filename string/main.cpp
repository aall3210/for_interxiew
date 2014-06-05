
#include <stdio.h>
#include "qh_string.h"
#include <assert.h>

void test1()
{
	qh::string str;
	assert( '\0' == *str[0] );
	assert( 0 == str.size() );

	qh::string str_test = "1234567";
	str = str_test;
	assert( *(str.c_str() + str.size()) == '\0' );
	assert( !strcmp(str.c_str(), str_test.c_str()) );
}

void test2()
{
	const char str_test[] = "abcdefg";
	qh::string str(str_test);
	assert( !strcmp(str.c_str(), str_test) );
	assert( 7 == str.size() );
	assert( 'a' == *(str[0]) );
	assert( '\0' == *str[7] );
	assert( NULL == str[9] );

	qh::string str2;
	str = str2;
	assert( '\0' == *str[0] );
	assert( 0 == str.size() );
	assert( *(str.c_str() + str.size()) == '\0' );
}

void test3()
{
	char str_test[] = "abcdefg";
	qh::string str(str_test, 4);
	assert( 'd' == *str[3] );
	assert( 4 == str.size() );

	qh::string str2 = "1234645765";
	str = str2;
	assert( !strcmp(str.c_str(), str2.c_str()) );
}

void test4()
{
	const qh::string str_test = "abcdefgfgdgdfgfd";
	qh::string str(str_test);
	assert( !strcmp(str.c_str(), str_test.c_str()) );
	assert( 16 == str.size() );
	assert( 'd'== *str[3] );
	assert( 'f'== *str[7] );
	assert( NULL== str[29] );
	assert( NULL== str[-1] );
}


int main(int argc, char* argv[])
{
    //TODO 在这里添加单元测试，越多越好，代码路径覆盖率越全越好
    //TODO 单元测试写法请参考INIParser那个项目，不要写一堆printf，要用assert进行断言判断
    test1();
    test2();
    test3();
    test4();

#ifdef WIN32
    system("pause");
#endif

	return 0;
}