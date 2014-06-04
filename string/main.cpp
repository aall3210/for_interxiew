
#include <stdio.h>
#include "qh_string.h"

void test1()
{
	qh::string str;
	assert( '\0' == *str[0] && 0 == str.size() );

	qh::string str_test = "1234567";
	str = str_test;
	assert( *(str.c_str() + str.size()) == '\0' );
	assert( *(str.data() + str.size()) != '\0' );
	assert( !strcmp(str.c_str(), str_test.c_str()) );
}

void test2()
{
	const char str_test[] = "abcdefg";
	qh::string str(str_test);
	assert( !strcmp(str.c_str(), str_test) && 0 == str.size() );
	char s = *str[0];
	s = *str[7];
	s = *str[9];
	s = *str[-1];

	qh::string str2;
	str = str2;
	assert( '\0' == *str[0] && 0 == str.size() );

	assert( *(str.c_str() + str.size()) == '\0' );
}

void test3()
{
	const char str_test[] = "abcdefg";
	qh::string str(str_test, 4);
	assert( 'd' == *str[3] && 4 == str.size() );

	qh::string str2 = "1234";
	str = str2;
	int res = strcmp(str.c_str(), str2.c_str());
	assert( 0 == res );
}

void test4()
{
	const qh::string str_test = "abcdefg";
	qh::string str(str_test);
	assert( !strcmp(str.c_str(), str_test.c_str()) && 7 == str.size() );
	char s = *str[0];
	s = *str[4];
	s = *str[7];
	s = *str[-1];
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