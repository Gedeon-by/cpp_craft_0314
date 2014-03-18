#include <iostream>
#include <fstream>
#include <boost/cstdint.hpp>
#include <market_message.h>

int main()
{
	std::ifstream in ( BINARY_DIR "/2.4_example.in", std::ios::binary );
	std::ofstream out ( BINARY_DIR "/2.4.out", std::ofstream::trunc|std::ios::binary );

	boost::uint32_t current_time = 0;

	while( in ){
		binary_reader::market_message msg(in);

		if( msg.time() > current_time )
			current_time = msg.time();
		
		std::cout << msg.type() << " " << msg.time() << " " << msg.len() << " " << msg.msg()<< " " << sizeof(msg.msg()) << std::endl;

		if( msg.type() == 1u || msg.type() == 2u || msg.type() == 3u || msg.type() == 4u )
				if ( (current_time - msg.time()) < 2u ) 
					if(out.is_open())
						msg.write(out);

	}
	in.close();
	out.close();

}

