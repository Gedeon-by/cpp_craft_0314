#include "a_message.h"

#include <stdexcept>

task4_4::a_message::a_message( std::istream& inp )
{
	inp.read( content_, content_size );
	if ( inp.eof() ){
		throw std::logic_error("bad input stream, a_message cannot be readed");
	}
	content_[content_size] = '\0';
}

task4_4::message_ptr task4_4::a_message::create_message( std::istream& inp )
{
	return message_ptr( new a_message( inp ) );
}

task4_4::a_message::~a_message()
{

}

//
const char task4_4::a_message::type() const
{
	return 'A';
}

const std::string task4_4::a_message::str() const
{
	const std::string myString = "a_message(" + static_cast<std::string>(content_) + ")";
	return myString;
}
