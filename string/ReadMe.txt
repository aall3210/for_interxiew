string 工程

请实现std::string类的主要功能。函数声明以及写作头文件中。部分实现也做了，但可能不完全正确。

请面试者实现这个类，并补充尽可能详尽的单元测试用例，越多越好，代码逻辑路径覆盖越全越好。

请认真对待，仔细考虑每一个细节问题。


replay:
1)没有资源泄露
2)时间复杂度(N是输入string的长度)，空间复杂度和时间一样。

string(); 				O(1)
string(const char* s);			O(N)
string(const char* s, size_t len);	O(N)
string(const string& rhs);		O(N)
string& operator=(const string& rhs);	O(N)
~string();				O(1)
size_t size() const;			O(1)
const char* data() const;		O(1)
const char* c_str() const;		O(1)
char* operator[](size_t index); 	O(1)