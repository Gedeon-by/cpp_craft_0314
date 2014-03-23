#include <iostream>
#include <fstream>
#include <boost/cstdint.hpp>
#include <market_message.h>

struct message_str {
	boost::uint32_t type;
	boost::uint32_t time;
	boost::uint32_t length;
	char *message_ptr;
} msg_temp;

int main()
{
	std::ifstream in ( BINARY_DIR "/2.4_example.in", std::ios::binary );
	std::ofstream out ( BINARY_DIR "/2.4.out", std::ofstream::trunc|std::ios::binary );

	static boost::uint32_t current_time = 0;

	if(in) {
		while( in.read( (char*)&msg_temp.type, sizeof( msg_temp.type ) ) ) {	
			in.read( (char*)&msg_temp.time, sizeof( msg_temp.time ) );
			in.read( (char*)&msg_temp.length, sizeof( msg_temp.length ) );
			msg_temp.message_ptr = new char[msg_temp.length];
			in.read(msg_temp.message_ptr, msg_temp.length);

			binary_reader::market_message mrkt_msg(msg_temp.type, msg_temp.time, msg_temp.length, msg_temp.message_ptr);

			delete [] msg_temp.message_ptr;

			if( mrkt_msg.time() > current_time )
				current_time = mrkt_msg.time();

			if( mrkt_msg.type() == 1u || mrkt_msg.type() == 2u || mrkt_msg.type() == 3u || mrkt_msg.type() == 4u )
				if ( ( current_time - mrkt_msg.time() ) < 2u ) 
					mrkt_msg.write(out);
		}
	} else {
		std::cout<< "Probably file is missing" << std::endl;
		return 1;
	}
	
	in.close();
	out.close();

}

