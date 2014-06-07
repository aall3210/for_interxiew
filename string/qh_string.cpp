#include "qh_string.h"

namespace qh
{
    // ctor
    string::string() : len_(0)
    {
        data_ = new char [1];
        data_[0] = '\0';
    }

    string::string( const char* s )
    {
        if(NULL == s)
        {
            len_ = 0;
            data_ = new char [1];
            data_[0] = '\0';
        }
        else
        {
            len_ = strlen(s);
            data_ = new char [len_ + 1];
            strcpy( data_, s );
        }
    }

    string::string( const char* s, size_t len )
    {
		if( NULL == s )
        {
            len_ = 0;
            data_ = new char [1];
            data_[0] = '\0';
        }
        else
		{
			len_ = (strlen(s) < len) ? strlen(s) : len;
			data_ = new char [len_ + 1];
			strncpy( data_, s, len_ );
			data_[len_] = '\0';
		}
    }

	// copy ctor
    string::string( const string& rhs )
    {
        len_ = rhs.size();
        data_ = new char [len_ + 1];
        strcpy( data_, rhs.c_str() );        
    }

    // copy assign
    // 改进，同时考虑到“自我赋值”和“异常”的安全性
    string& string::operator=( const string& rhs )
    {

        char *pOrig = data_;
        char *copy = new char [rhs.size() + 1];
        strcpy( copy, rhs.c_str() ); 
        data_ = copy;
        len_ = rhs.size();
        delete [] pOrig;
        return *this;
        /*
        if( this != &rhs )
        {
            delete [] data_;
            len_ = rhs.len_;
            data_ = new char [len_ + 1];
            strcpy( data_, rhs.data_ );        
        }
        return *this;
        */
    }

    // dtor
    string::~string()
    {
        delete [] data_;
    }

    size_t string::size() const
    {
        return len_;
    }

    // from C++11, the data() is same with c_str()
    const char* string::data() const
    {
        return c_str();
    }

    const char* string::c_str() const
    {
        return data_;
    }

    char* string::operator[]( size_t index )
    {
        return ( index > len_ ) ? NULL : data_ + index;
    }

}