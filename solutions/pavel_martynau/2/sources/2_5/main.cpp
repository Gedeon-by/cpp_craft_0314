#include <iostream>
#include <fstream>
#include <stdint.h>


struct message_str {
	uint32_t type;
	uint32_t time;
	uint32_t length;
	char *message;
};

int main() {
	std::ifstream input_file ( BINARY_DIR "/2.5.in", std::ios::binary );
	std::ofstream output_file ( BINARY_DIR "/2.5.out", std::ofstream::trunc|std::ios::binary );
	if(input_file.is_open()){
		uint32_t current_time = 0;
		message_str msg;
		 while( input_file.read( (char*)&msg.type, sizeof( msg.type ) ) ) {	
			input_file.read( (char*)&msg.time, sizeof( msg.time ) );
			input_file.read( (char*)&msg.length, sizeof( msg.length ) );
			if( msg.length < 2024 ) {
				msg.message = new char[msg.length];
				input_file.read(msg.message, msg.length);

				if(output_file.is_open()) {
					output_file.write( (char*)&msg.type, sizeof(msg.type) );
					output_file.write( (char*)&msg.time, sizeof(msg.time) );
					output_file.write( (char*)&msg.length, sizeof(msg.length) );
					output_file.write( msg.message, msg.length );
				}
			} else {
				input_file.ignore(msg.length);
			}
		}

		input_file.close();
		output_file.close();
	}

	return 0;
}