#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <stdint.h>

struct message_str {
	uint32_t type;
	uint32_t time;
	uint32_t length;
	char * message;
};

bool compareByTime(const message_str &a, const message_str &b) {
	return a.time < b.time;
}

int main() {
	std::ifstream input_file ( BINARY_DIR "/2.4.in", std::ios::binary );
	std::vector< message_str > messages;
	uint32_t cur_time = 0;
	if(input_file.is_open()){
		message_str msg;
		 while( input_file.read( (char*)&msg.type, sizeof( msg.type ) ) ) {
			input_file.read( (char*)&msg.time, sizeof( msg.time ) );
			input_file.read( (char*)&msg.length, sizeof( msg.length ) );
			msg.message = new char[msg.length];
			input_file.read(msg.message, msg.length);

			if(msg.time > cur_time) cur_time = msg.time;
			
			if(msg.type == 1u || msg.type == 2u || msg.type == 3u || msg.type == 4u )
				if(2 > ( cur_time - msg.time ) )
					messages.push_back( msg );
		}
		input_file.close();
	}

	std::sort(messages.begin(), messages.end(), compareByTime);
	
	for(size_t i = 0; i < messages.size(); i++) {
		std::cout << messages[i].type << " " << messages[i].time << " "<< messages[i].length << " ";
		for(size_t j = 0; j < messages[i].length; j++)
			std::cout << messages[i].message[j];
		std::cout << std::endl;
	}

	return 0;
}