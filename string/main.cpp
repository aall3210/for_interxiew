
#include <stdio.h>
#include "qh_string.h"
#include <assert.h>

void test_string1()
{
	// test string()
	qh::string str;
	assert( '\0' == *str[0] );
	assert( 0 == str.size() );
	assert( '\0' == *str.c_str() );
	assert( '\0' == *str.data() );

	// test copy assign
	str = qh::string();
	assert( '\0' == *str[0] );
	assert( 0 == str.size() );
	assert( '\0' == *str.c_str() );
	assert( '\0' == *str.data() );

	// test string(cahr *) && copy assign
	str = qh::string( "jhsf" );
	assert( 'j' == *str[0] );
	assert( 4 == str.size() );
	assert( 'j' == *str.c_str() );
	assert( 'j' == *str.data() );

    printf( "%s() all test OK!\n", __FUNCTION__ );
}

void test_string2()
{
	// test string(string& s) s=""
	qh::string s;
	qh::string str_test( s );
	assert( '\0' == *str_test[0] );
	assert( 0 == str_test.size() );
	assert( '\0' == *str_test.c_str() );
	assert( '\0' == *str_test.data() );

	// test string(string&)
	const qh::string str_test2 = "abcdefgfgdgdfgfd";
	qh::string str(str_test2);
	assert( 16 == str.size() );
	assert( 'a' == *str.c_str() );
	assert( 'a' == *str.data() );
	assert( !strcmp(str.c_str(), str_test2.c_str()) );

	// test operator[]
	assert( 'd' == *str[3] );
	assert( 'f' == *str[7] );
	assert( NULL == str[29] );
	*str[7] = 'd';
	assert( 'd' == *str[7] );

	printf( "%s() all test OK!\n", __FUNCTION__ );
}


void test_string3()
{
	const char str_test[] = "";
	// test string(char* s) s=""
	qh::string str(str_test);
	assert( '\0' == *str[0] );
	assert( 0 == str.size() );
	assert( '\0' == *str.c_str() );
	assert( '\0' == *str.data() );

	// test string(char* s, size_t) s=""
	qh::string str2(str_test, 4);
	// test operator[]
	assert( '\0' == *str2[0] );
	assert( 0 == str2.size() );
	assert( '\0' == *str2.c_str() );
	assert( '\0' == *str2.data() );

	printf( "%s() all test OK!\n", __FUNCTION__ );
}

void test_string4()
{
	// test string(char*, size_t)
	char str_test[] = "^%$^%$**&%*(^^#%";
	qh::string str(str_test, 4);
	assert( '^' == *str.c_str() );
	assert( '^' == *str.data() );

	// test operator[]
	assert( '^' == *str[3] );
	assert( NULL == str[29] );
	assert( 4 == str.size() );
	*str[2] = '^';
	assert( '^' == *str[2] );

	// test self copy assign
	qh::string str2 = "1234645765";
	str2 = str2;
	assert(str2.c_str() != NULL);
	assert( '1' == *str2[0] );
	assert( 10 == str2.size() );
	assert( '1' == *str2.c_str() );
	assert( '1' == *str2.data() );

	printf("%s() all test OK!\n", __FUNCTION__);
}

int main(int argc, char* argv[])
{
    //TODO 在这里添加单元测试，越多越好，代码路径覆盖率越全越好
    //TODO 单元测试写法请参考INIParser那个项目，不要写一堆printf，要用assert进行断言判断
    test_string1();
    test_string2();
    test_string3();
    test_string4();

#ifdef WIN32
    system("pause");
#endif

	return 0;
}