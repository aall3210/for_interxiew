#include <iostream>
#include "ini_parser.h"
#include <assert.h>

void test1()
{
    const char* ini_text= "a=1\nb=2\n"; 
    qh::INIParser parser;
    if (!parser.Parse(ini_text, strlen(ini_text), "\n", "=")) {
        assert(false);
    }

    const std::string& a = parser.Get("a", NULL);
    assert(a == "1");

    std::string b = parser.Get("b", NULL);
    assert(b == "2");
	
    const std::string& c = parser.Get("c", NULL);
    assert(c == "");
    printf( "%s() all test OK!\n", __FUNCTION__ );
}

void test2()
{
    const char* ini_text= "a=1||b=2||c=3"; 
    qh::INIParser parser;
    if (!parser.Parse(ini_text, strlen(ini_text), "||", "=")) {
        assert(false);
    }

    const std::string& a = parser.Get("a", NULL);
    assert(a == "1");

    std::string b = parser.Get("b", NULL);
    assert(b == "2");

    const std::string& c = parser.Get("c", NULL);
    assert(c == "3");
    printf( "%s() all test OK!\n", __FUNCTION__ );
}

void test3()
{
    const char* ini_text= "||||a:1||b:2||||c:3||||||"; 
    qh::INIParser parser;
    if (!parser.Parse(ini_text, strlen(ini_text), "||", ":")) {
        assert(false);
    }

    const std::string& a = parser.Get("a", NULL);
    assert(a == "1");

    std::string b = parser.Get("b", NULL);
    assert(b == "2");

    const std::string& c = parser.Get("c", NULL);
    assert(c == "3");
    printf( "%s() all test OK!\n", __FUNCTION__ );
}

void test4()
{
    const char* ini_text = "[sec]***a:1***b:2**";
    qh::INIParser parser;
    if (!parser.Parse(ini_text, strlen(ini_text), "*", ":")) {
        assert(false);
    }

    const std::string& a = parser.Get("sec", "a", NULL);
    assert(a == "1");

    std::string b = parser.Get("sec", "b", NULL);
    assert(b == "2");

    const std::string& c = parser.Get("sec", "c", NULL);
    assert(c == "");
    printf( "%s() all test OK!\n", __FUNCTION__ );
}

void test5()
{
    const char* ini_text = "[sec]&&ab:1&&&bc:2&&&cd:3";
    qh::INIParser parser;
    if (!parser.Parse(ini_text, strlen(ini_text), "&", ":")) {
        assert(false);
    }

    const std::string& a = parser.Get("sec", "ab", NULL);
    assert(a == "1");

    std::string b = parser.Get("sec", "bc", NULL);
    assert(b == "2");

    const std::string& c = parser.Get("sec", "cd", NULL);
    assert(c == "3");
    printf( "%s() all test OK!\n", __FUNCTION__ );
}

void test6()
{
    const char* ini_text = "[sec][sec1]   a=1  bb=2    ccc=3    ";
    qh::INIParser parser;
    if (!parser.Parse(ini_text, strlen(ini_text), " ", "=")) {
        assert(false);
    }

    const std::string& a = parser.Get("sec1", "a", NULL);
    assert(a == "1");

    std::string b = parser.Get("sec1", "bb", NULL);
    assert(b == "2");

    const std::string& c = parser.Get("sec", "ccc", NULL);
    assert(c == "");

	const std::string& d = parser.Get("sec1", "dddd", NULL);
    assert(d == "");
    printf( "%s() all test OK!\n", __FUNCTION__ );
}

void test7()
{
    const char* ini_text = "[sec1]a=1***bb=2****ccc=3**[sec2]a=4***b=5****c=6**";
    qh::INIParser parser;
    if (!parser.Parse(ini_text, strlen(ini_text), "*", "=")) {
        assert(false);
    }

    const std::string& aa = parser.Get("sec1", "a", NULL);
    assert(aa == "1");

    std::string bb = parser.Get("sec1", "bb", NULL);
    assert(bb == "2");

    const std::string& ccc = parser.Get("sec1", "ccc", NULL);
    assert(ccc == "3");

	const std::string& dddd = parser.Get("sec1", "dddd", NULL);
    assert(dddd == "");

	const std::string& a = parser.Get("sec2", "a", NULL);
    assert(a == "4");

    std::string b = parser.Get("sec2", "b", NULL);
    assert(b == "5");

    const std::string& c = parser.Get("sec2", "c", NULL);
    assert(c == "6");

	const std::string& d = parser.Get("sec2", "dddd", NULL);
    assert(d == "");
    printf( "%s() all test OK!\n", __FUNCTION__ );
}

int main(int argc, char* argv[])
{
    //TODO 在这里添加单元测试，越多越好，代码路径覆盖率越全越好

    test1();
    test2();
    test3();
    test4();
	test5();
	test6();
	test7();

    return 0;
}
