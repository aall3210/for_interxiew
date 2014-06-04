#include "ini_parser.h"
#include <fstream>

namespace qh
{
	INIParser::INIParser()
	{
	}

	~INIParser::INIParser()
	{
	}

	bool INIParser::Parse(const std::string& ini_file_path)
	{
		
	}

	bool INIParser::Parse(const char* ini_data, size_t ini_data_len, 
					 const std::string& line_seperator = "\n", 
					 const std::string& key_value_seperator = "=")
	{

	}

	const std::string& INIParser::Get(const std::string& key, bool* found)
	{

	}

	const std::string& INIParser::Get(const std::string& section, const std::string& key, bool* found)
	{

	}
}