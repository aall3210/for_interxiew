#include "qh_string.h"

namespace qh
{
    // TODO
    string::string() 
    {
        len_ = 0;
        data_ = new char [1];
        data_[0] = '\0';
    }

    string::string( const char* s )
    {
        len_ = strlen(s);
        data_ = new char [len_ + 1];
        strcpy( data_, s );
    }

    string::string( const char* s, size_t len )
    {
		if(len > 0)
		{
			len_ = (strlen(s) < len) ? strlen(s) : len;
			data_ = new char [len_ + 1];
			strncpy( data_, s, len_ );
			data_[len_] = '\0';
		}
    }

    string::string( const string& rhs )
    {
        len_ = rhs.len_;
        data_ = new char [len_ + 1];
        strcpy( data_, rhs.data_ );        
    }

    // need to improve
    string& string::operator=( const string& rhs )
    {
        if( this != &rhs )
        {
            delete [] data_;
            len_ = rhs.len_;
            data_ = new char [len_ + 1];
            strcpy( data_, rhs.data_ );        
        }
        return *this;
    }

    string::~string()
    {
        delete [] data_;
        data_ = NULL;
    }

    size_t string::size() const
    {
        return len_;
    }

    // need to improve
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
        if( index>=0 && index<=len_ )
            return data_ + index;
        return NULL;
    }

}