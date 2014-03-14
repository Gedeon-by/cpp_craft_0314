#include <iostream>
#include <fstream>
#include <stdint.h>
#include "boost\date_time\gregorian\gregorian.hpp"

//stock_name – string (длинна строки не более 8 char), date_time: дата в формате YYYYMMDD, price: double, vwap: double, volume: uint32, (f1, t1, f2, f3, f4) данные о торгах за день типа double.

struct data {
	char stock_name[8];
	char date_time[8];
	double price;
	double vwap;
	uint32_t volume;
	double f1,t1,f2,f3,f4;
};

int main() {
	std::ifstream input_file ( BINARY_DIR "/2.6.in", std::ios::binary );
	std::ofstream output_file ( BINARY_DIR "/2.6.out", std::ios::binary );
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
			}
		}

		input_file.close();
		output_file.close();
	}

	return 0;
}