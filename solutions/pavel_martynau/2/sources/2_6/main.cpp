#include <iostream>
#include <fstream>
#include <stdint.h>
#include "boost\date_time\gregorian\gregorian.hpp"

//stock_name – string (длинна строки не более 8 char), date_time: дата в формате YYYYMMDD, price: double, vwap: double, volume: uint32, (f1, t1, f2, f3, f4) данные о торгах за день типа double.

struct stock_data {
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
		stock_data msg;
		 while( input_file.read( msg.stock_name, sizeof( msg.stock_name ) ) ) {	
			
		}

		input_file.close();
		output_file.close();
	}

	return 0;
}