����������C++ʵ�����INI������

���INI����������ֱ�ӽ����ڴ����ݺʹ����ļ���
�ٸ������ӣ�

const char* ini_text= "a=1\nb=2\n"; 
qh::INIParser parser;
if (!parser.Parse(ini_text, strlen(ini_text), "\n", "=")) {
    //TODO error process
}

const std::string& a = parser.Get("a", NULL);
assert(a == "1");

std::string b = parser.Get("a", NULL);
assert(b == "2");

const std::string& c = parser.Get("c", NULL);
assert(c == "");

	���ini_text�����ڴ����ݡ����ô������ϡ�
	Ӳ�����ݿ���ͨ�����ļ���api�����ڴ����Ϊ�ڴ����ݡ�

����㣺
-          INI���Ľ������ܵ��걸��
-          �������������ʾ�����
-          �����̷��Ƚ��Ѻ�(�ο�google��C++��̹淶)
-          ������Ķ��ԡ���ά���ԱȽϺ�
-          Linux�¿����Ͳ���
�뽫Դ�롢�����������롢Makefile��һ�����(ע����ļ����ϴ����Լ�������)�������ǡ�


û���ڴ�й¶��

ʱ�临�Ӷȷ�����
INIParser();	O(1)	
~INIParser();	O(1)	


ʱ�临�Ӷ�O(N)��N���ڴ��л���Ӳ�̶����string�ĳ��ȡ�
bool Parse(const std::string& ini_file_path);	
bool Parse(const char* ini_data, 
size_t ini_data_len, const std::string& line_seperator = "\n", 
const std::string& key_value_seperator = "=");


ʱ�临�Ӷ�O(1)��ֱ�Ӵ�map��ȡ����
const std::string& Get(const std::string& key, bool* found);
const std::string& Get(const std::string& section, const std::string& key, bool* found);


�����������ĵĿռ�ͽ����������йأ���Ҳ��O(N)��