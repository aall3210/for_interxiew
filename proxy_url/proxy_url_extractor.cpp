#include "proxy_url_extractor.h"
#include <vector>
#include "tokener.h"

namespace qh
{

    namespace {

        template< class _StringVector, 
        class StringType,
        class _DelimType> 
            inline void StringSplit(  
            const StringType& str, 
            const _DelimType& delims, 
            unsigned int maxSplits, 
            _StringVector& ret)
        {
            unsigned int numSplits = 0;

            // Use STL methods
            size_t start, pos;
            start = 0;

            do
            {
                pos = str.find_first_of( delims, start );

                if ( pos == start )
                {
                    ret.push_back(StringType());
                    start = pos + 1;
                }
                else if ( pos == StringType::npos || ( maxSplits && numSplits + 1== maxSplits ) )
                {
                    // Copy the rest of the string
                    ret.push_back(StringType());
                    *(ret.rbegin()) = StringType(str.data() + start, str.size() - start);
                    break;
                }
                else
                {
                    // Copy up to delimiter
                    //ret.push_back( str.substr( start, pos - start ) );
                    ret.push_back(StringType());
                    *(ret.rbegin()) = StringType(str.data() + start, pos - start);
                    start = pos + 1;
                }

                ++numSplits;

            }
            while ( pos != StringType::npos );
        }
    }

    ProxyURLExtractor::ProxyURLExtractor()
    {
    }

    bool ProxyURLExtractor::Initialize( const std::string& param_keys_path )
    {
        std::ifstream ifs;
        ifs.open(param_keys_path.data(), std::fstream::in);
        typedef std::vector<std::string> stringvector;
        stringvector keysvect;
        
        while (!ifs.eof()) {
            std::string line;
            getline(ifs, line);
            if (ifs.fail() && !ifs.eof()) {
                fprintf(stderr, "SubUrlExtractor::LoadParamKeysFile readfile_error=[%s] error!!", param_keys_path.data());
                ifs.close();
                return false;
            }
            if (line.empty()) continue;

            keysvect.clear();
            StringSplit(line, ",", static_cast<unsigned int>(-1), keysvect);
            assert(keysvect.size() >= 1);
            keys_set_.insert(keysvect.begin(), keysvect.end());
            keys_set_.erase("");
        }

        ifs.close();

        return true;
    }

    std::string ProxyURLExtractor::Extract( const std::string& raw_url )
    {
        std::string sub_url;
        ProxyURLExtractor::Extract(keys_set_, raw_url, sub_url);
        return sub_url;
    }

    // 直接在原始方法上修改，处理异常分支。直接用string做我想会更好。
    void ProxyURLExtractor::Extract( const KeyItems& keys, const std::string& raw_url, std::string& sub_url )
    {
#if 1
        //TODO 请面试者在这里添加自己的代码实现以完成所需功能
        int pos = raw_url.find_first_of("?");
		assert(pos != std::string::npos);
        // skip of '?', maybe have some
		while('?' == raw_url[pos])
		{
			++pos;
		}
		int value_end; 
		int key_begin;
		int equal;
		std::string key;
		while(pos < raw_url.size())
		{
			equal = raw_url.find_first_of("=", pos);
            // 都需要处理异常情况
			if(std::string::npos == equal)
				break;
			key_begin = raw_url.find_last_of("&", equal);
			key_begin = (std::string::npos == key_begin) ? pos : key_begin + 1;
			key = raw_url.substr(key_begin, equal - key_begin);
			value_end = raw_url.find_first_of("&", equal);
			value_end = (std::string::npos == value_end) ? raw_url.size() : value_end;
			++equal;
			if (keys.find(key) != keys.end()) 
			{
				sub_url = raw_url.substr(equal, value_end - equal);
			}
			pos = value_end + 1;
		}
        /*
		Tokener token(raw_url);
        token.skipTo('?');
		while('?' == token.current())
		{
			token.next();
		}
        std::string key;
		int pos;
        while (!token.isEnd()) {
            key = token.nextString('=');
			if( ( pos = key.find_last_of('&') ) != -1)
				key = key.erase(0, pos+1);
            if (keys.find(key) != keys.end()) {
                const char* curpos = token.getCurReadPos();
                int nreadable = token.getReadableSize();
                sub_url = token.nextString('&');
                if (sub_url.empty() && nreadable > 0 && *curpos != '&')
				{
                    assert(curpos);
                    sub_url.assign(curpos, nreadable);
                }
            }
            if( token.skipTo('&') == '&')
            	token.next();    //skip one char : '&'
            else
				break;
        }
        */
#else
        //这是一份参考实现，但在特殊情况下工作不能符合预期
        Tokener token(raw_url);
        token.skipTo('?');
        token.next(); //skip one char : '?' 
        std::string key;
        while (!token.isEnd()) {
            key = token.nextString('=');
            if (keys.find(key) != keys.end()) {
                const char* curpos = token.getCurReadPos();
                int nreadable = token.getReadableSize();

                /**
                * case 1: 
                *  raw_url="http://www.microsofttranslator.com/bv.aspx?from=&to=zh-chs&a=http://hnujug.com/&xx=yy"
                *  sub_url="http://hnujug.com/"
                */
                sub_url = token.nextString('&');

                if (sub_url.empty() && nreadable > 0) {
                    /**
                    * case 2: 
                    * raw_url="http://www.microsofttranslator.com/bv.aspx?from=&to=zh-chs&a=http://hnujug.com/"
                    * sub_url="http://hnujug.com/"
                    */
                    assert(curpos);
                    sub_url.assign(curpos, nreadable);
                }
            }
            token.skipTo('&');
            token.next();//skip one char : '&'
        }
#endif
    }

    std::string ProxyURLExtractor::Extract( const KeyItems& keys, const std::string& raw_url )
    {
        std::string sub_url;
        ProxyURLExtractor::Extract(keys, raw_url, sub_url);
        return sub_url;
    }
}
