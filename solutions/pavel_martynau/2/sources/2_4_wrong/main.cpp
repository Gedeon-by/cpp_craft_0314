#include <iostream>
#include <fstream>
#include <stdint.h>


struct message_str {
	uint32_t type;
	uint32_t time;
	uint32_t length;
	char *message_ptr;
};

//Commented, as far as task doesn't need a sorting
//bool compareByTime( message_str &a, message_str &b){ 
//	return b.time > a.time;
//}

int main() {
	std::ifstream input_file ( BINARY_DIR "/2.4.in", std::ios::binary );
	std::ofstream output_file ( BINARY_DIR "/2.4.out", std::ofstream::trunc|std::ios::binary );
	if(input_file.is_open()){
		uint32_t current_time = 0;
		message_str msg;
		 while( input_file.read( (char*)&msg.type, sizeof( msg.type ) ) ) {	
			input_file.read( (char*)&msg.time, sizeof( msg.time ) );
			input_file.read( (char*)&msg.length, sizeof( msg.length ) );
			msg.message_ptr = new char[msg.length];
			input_file.read(msg.message_ptr, msg.length);

			if( msg.time > current_time )
				current_time = msg.time;

			if( msg.type == 1u || msg.type == 2u || msg.type == 3u || msg.type == 4u )
				if ( (current_time - msg.time) < 2u ) 
					if(output_file.is_open()) {
						output_file.write( (char*)&msg.type, sizeof(msg.type) );
						output_file.write( (char*)&msg.time, sizeof(msg.time) );
						output_file.write( (char*)&msg.length, sizeof(msg.length) );
						output_file.write( msg.message_ptr, msg.length );
					}

			delete [] msg.message_ptr;
		}
		input_file.close();
		output_file.close();
	}

	//std::sort(messages.begin(), messages.end(), compareByTime);

	return 0;
}