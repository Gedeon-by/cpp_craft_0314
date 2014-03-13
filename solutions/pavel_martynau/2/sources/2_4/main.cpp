#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdint.h>

union uint_char {
	char c[4];
	uint32_t i;
};

struct message_str {
	uint32_t type;
	uint32_t time;
	uint32_t length;
	char * message;
};

class Message_class {
	public:
		uint32_t type;
		uint32_t time;
		uint32_t length;
		char * message;
};

int main() {
	std::ifstream input_file ( BINARY_DIR "/2.4.in", std::ios::in|std::ios::binary );
	std::vector< message_str > messages;
	if(input_file.is_open()){
		message_str msg;
		uint_char ui;
		 while(input_file.read( ui.c, 4 )) {
			std::cout << input_file.eof() << std::endl;
			msg.type = ui.i;
			std::cout << msg.type << std::endl;
			input_file.read( ui.c, 4 );
			msg.time = ui.i;
			std::cout << msg.time << std::endl;
			input_file.read( ui.c, 4 );
			msg.length = ui.i;
			std::cout << msg.length << "--------------" << std::endl;
			msg.message = new char[msg.length];
			input_file.read(msg.message, msg.length);
			for(size_t j = 0; j < msg.length; j++) {
				std::cout << msg.message[j];
			}
					
			std::cout << std::endl;
			std::cout << input_file.eof() << std::endl;
			messages.push_back( msg );

		}
		input_file.close();
	}
	std::cout << "size" << messages.size() << std::endl;
	for(size_t i = 0; i < messages.size(); i++){
		std::cout << messages[i].type << " " << messages[i].time << " " << messages[i].length << " ";
		for(size_t j = 0; j < messages[i].length; j++) {
			std::cout << messages[i].message[j];
		}
		std::cout << std::endl;
	}

	return 0;
}