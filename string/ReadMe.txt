string ����

��ʵ��std::string�����Ҫ���ܡ����������Լ�д��ͷ�ļ��С�����ʵ��Ҳ���ˣ������ܲ���ȫ��ȷ��

��������ʵ������࣬�����価�����꾡�ĵ�Ԫ����������Խ��Խ�ã������߼�·������ԽȫԽ�á�

������Դ�����ϸ����ÿһ��ϸ�����⡣


replay:
1)û����Դй¶
2)ʱ�临�Ӷ�(N������string�ĳ���)���ռ临�ӶȺ�ʱ��һ����

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