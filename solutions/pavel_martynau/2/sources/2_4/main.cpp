#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <stdint.h>


struct message_str {
	uint32_t type;
	uint32_t time;
	uint32_t length;
	char *message;
};

bool compareByTime( message_str &a, message_str &b){
	return b.time > a.time;
}

int main() {
	std::ifstream input_file ( BINARY_DIR "/2.4.in", std::ios::binary );
	std::ofstream output_file ( BINARY_DIR "/2.4.out", std::ios::binary );
	std::vector< message_str > messages;
	if(input_file.is_open()){
		uint32_t current_time = 0;
		message_str msg;
		 while( input_file.read( (char*)&msg.type, sizeof( msg.type ) ) ) {	
			input_file.read( (char*)&msg.time, sizeof( msg.time ) );
			input_file.read( (char*)&msg.length, sizeof( msg.length ) );
			msg.message = new char[msg.length];
			input_file.read(msg.message, msg.length);

			if( msg.time > current_time )
				current_time = msg.time;
			
			if( msg.type == 1u || msg.type == 2u || msg.type == 3u || msg.type == 4u )
				if ( (current_time - msg.time) < 2u )
					messages.push_back( msg );
		}
		input_file.close();
	}

	std::sort(messages.begin(), messages.end(), compareByTime);
	
	if(output_file.is_open()){
		for(size_t i = 0; i < messages.size(); i++){
			output_file.write( (char*)&messages[i].type, sizeof(messages[i].type) );
			output_file.write( (char*)&messages[i].time, sizeof(messages[i].time) );
			output_file.write( (char*)&messages[i].length, sizeof(messages[i].length) );
			output_file.write( messages[i].message, messages[i].length );
		}
		output_file.close();
	}

	return 0;
}