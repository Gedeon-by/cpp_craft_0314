#include "market_message.h"
#include <cstring>

binary_reader::market_message::market_message( std::ifstream& in )
{
	in.read( (char*)&type_, sizeof( type_ ) );
	in.read( (char*)&time_, sizeof( time_ ) );
	in.read( (char*)&len_, sizeof( len_ ) );
	msg_ = new char[len_];
	in.read(msg_, len_);
}
binary_reader::market_message::market_message( const boost::uint32_t type, const boost::uint32_t time, const boost::uint32_t len, const char* const msg ) : type_(type), time_(time), len_(len)
{
		msg_ = new char[len_];
		strncpy(msg_, msg, len_);
}
void binary_reader::market_message::write( std::ofstream& out )
{
	out.write( (char*)&type_, sizeof(type_) );
	out.write( (char*)&time_, sizeof(time_) );
	out.write( (char*)&len_, sizeof(len_) );
	out.write( msg_, len_ );

}

binary_reader::market_message::~market_message()
{
	delete[] msg_;
}
//
boost::uint32_t binary_reader::market_message::type() const
{
	return type_;
}
boost::uint32_t binary_reader::market_message::time() const
{
	return time_;
}
boost::uint32_t binary_reader::market_message::len() const
{
	return len_;
}
const char* const binary_reader::market_message::msg() const
{
	return msg_;
}
