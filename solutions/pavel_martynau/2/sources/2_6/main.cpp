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

const boost::gregorian::date begin_date(boost::gregorian::from_simple_string("00010101"));

boost::gregorian::days days;

int main() {
	std::ifstream input_file ( BINARY_DIR "/2.6.in", std::ios::binary );
	std::ofstream output_file ( BINARY_DIR "/2.6.out", std::ofstream::trunc|std::ios::binary );
	if(input_file.is_open()){
		stock_data msg;
		 while( input_file.read( msg.stock_name, sizeof( msg.stock_name ) ) ) {	
			input_file.read( msg.date_time, sizeof( msg.date_time ) );

			days = boost::gregorian::date (boost::gregorian::from_simple_string(msg.date_time)) - begin_date;
			std::cout << days <<std::endl;

			input_file.read( (char*)&msg.price, sizeof( msg.price ) );
			input_file.read( (char*)&msg.vwap, sizeof( msg.vwap ) );
			input_file.read( (char*)&msg.volume, sizeof( msg.volume ) );
			input_file.read( (char*)&msg.f1, sizeof( msg.f1 ) );
			input_file.read( (char*)&msg.t1, sizeof( msg.t1 ) );
			input_file.read( (char*)&msg.f2, sizeof( msg.f2 ) );
			input_file.read( (char*)&msg.f3, sizeof( msg.f3 ) );
			input_file.read( (char*)&msg.f4, sizeof( msg.f4 ) );
		}

		input_file.close();
		output_file.close();
	}

	return 0;
}