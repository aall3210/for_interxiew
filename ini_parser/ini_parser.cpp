#include "ini_parser.h"
#include <fstream>

namespace qh
{
	static const char left_tag     = '[';  
    static const char right_tag    = ']';  
    static const char* equal        = "=";  
    static const char* next_line    = "/n";  

	INIParser::INIParser()
	{
	}

	INIParser::~INIParser()
	{
	}

	// 从硬盘读取文件到内存，再进行ini解析
	// 处理好文件句柄打开而未关闭
	bool INIParser::Parse(const std::string& ini_file_path)
	{
		ifstream in_file(ini_file_path.c_str());
		if(NULL == in_file)
		{
			fprintf(stderr, "INIParser::Parse read_filepath_error=[%s] error!!", ini_file_path.c_str());
            in_file.close();
			return false;
		}

		in_file.seekg(0, ios::end);
		size_t len_of_file = in_file.tellg();
		if(len_of_file < 0)
		{
			fprintf(stderr, "INIParser::Parse read_filelen error!!");
            in_file.close();
			return false;
		}

		char* buffer = new char [len_of_file + 1];

		in_file.seekg(0, ios::beg);
		in_file.read(buffer, len_of_file);
		buffer[len_of_file] = '\0';

		in_file.close();
		return Parse(buffer, len_of_file);
	}

	// 通过状态机解析，共有三个状态，STATE_SECTION, STATE_KEY, STATE_VALUE
	// 该解析的没有考虑comments，同时默认当line_seperator不为空格时，字符串中没有空格
	bool INIParser::Parse(const char* ini_data, size_t ini_data_len, 
					 const std::string& line_seperator, 
					 const std::string& key_value_seperator )
	{
        string  section_str;  
        string  key_str; 
		int  	pos = 0; 
		int  	section_begin, section_end;
		int 	value_end;
		int 	key_end;
 
        string ini_data_str(ini_data, ini_data_len + 1);
		ini_data_str[ini_data_len] = '\0';
        enum STATE{ STATE_SECTION, STATE_KEY, STATE_VALUE }state = STATE_SECTION; 

        while(pos < ini_data_len)
        {
        	switch(state)
        	{
        	case STATE_SECTION:
        		{
        			pos = ini_data_str.find_first_not_of(line_seperator, pos);
        			if(ini_data_str[pos] != left_tag)
        			{
        				section_str = "";
						state = STATE_KEY;
        			}
        			else
        			{
        				section_begin = pos + 1;
        				section_end = ini_data_str.find_first_of( right_tag, pos );
        				state = STATE_KEY;  
	                    section_str = ini_data_str.substr(section_begin, section_end - section_begin);
	                    pos = section_end + 1; 
        			}
        			section_[section_str][""] = "";
        			break;
        		}
        	case STATE_KEY:
        		{
        			pos = ini_data_str.find_first_not_of(line_seperator, pos);
        			if(ini_data_str[pos] == left_tag)
        			{
        				section_[section_str][""] = "";
        				state = STATE_SECTION; 
        			}
        			else
        			{
        				key_end = ini_data_str.find_first_of( key_value_seperator, pos );
        				state = STATE_VALUE;  
						// pos = ini_data_str.find_first_not_of( line_seperator, pos );
						key_str = ini_data_str.substr(pos, key_end - pos);
						pos = key_end + key_value_seperator.size();  
        			}
        			break;
        		}
        	case STATE_VALUE:
        		{
        			value_end = ini_data_str.find_first_of( line_seperator, pos );
					if(value_end == string::npos)
					{
						section_[section_str][key_str] = ini_data_str.substr(pos, ini_data_len - pos);  
						pos = ini_data_len;
					}
					else
					{
						section_[section_str][key_str] = ini_data_str.substr(pos, value_end - pos); 
						pos = value_end + line_seperator.size();
						pos = ini_data_str.find_first_not_of(line_seperator, pos);
						if(ini_data_str[pos] == left_tag)
						{
							state = STATE_SECTION; 
						}
						else if(pos != string::npos)
						{
							state = STATE_KEY; 
						}
					}
					break;
        		}
        	default:
				    break;
        	}
        }
        return true;
	}

	// 默认section是空串
	const std::string& INIParser::Get(const std::string& key, bool* found)
	{
		return Get("", key, found);
	}

	// 当key不在对应查询的section中时，在map每个section中添加空串对
	// 以便查询失败返回引用空串。
	const std::string& INIParser::Get(const std::string& section, const std::string& key, bool* found)
	{
		section_map::iterator iter_section = section_.find(section);

		if(section_.end() != iter_section)
		{
			key_value_map::iterator iter_key = iter_section->second.find(key);
			if(iter_section->second.end() != iter_key)
			{
				return iter_key->second;
			}
		}
		return section_[""][""] ;
	}
}