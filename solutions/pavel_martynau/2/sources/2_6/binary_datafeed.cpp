#include <iostream>
#include <fstream>
#include <boost/cstdint.hpp>
#include <stock_data.h>

struct stock_data {
	char stock_name[8];
	char date[8];
	double price;
	double vwap;
	boost::uint32_t volume;
	double f1;
	double t1;
	double f2;
	double f3;
	double f4;
} stock_msg;


int main()
{
	std::ifstream in ( BINARY_DIR "/2.6_example.in", std::ios::binary );
	std::ofstream out ( BINARY_DIR "/2.6.out", std::ofstream::trunc|std::ios::binary );

	if(in) {
		while( in.read(stock_msg.stock_name, 8) ) {
			in.read(stock_msg.date, 8);
			in.read( (char*)&stock_msg.price, sizeof( stock_msg.price ) );
			in.read( (char*)&stock_msg.vwap, sizeof( stock_msg.vwap ) );
			in.read( (char*)&stock_msg.volume, sizeof( stock_msg.volume ) );
			in.read( (char*)&stock_msg.f1, sizeof( stock_msg.f1 ) );
			in.read( (char*)&stock_msg.t1, sizeof( stock_msg.t1 ) );
			in.read( (char*)&stock_msg.f2, sizeof( stock_msg.f2 ) );
			in.read( (char*)&stock_msg.f3, sizeof( stock_msg.f3 ) );
			in.read( (char*)&stock_msg.f4, sizeof( stock_msg.f4 ) );

			binary_reader::stock_data stock_data_msg(stock_msg.stock_name, stock_msg.date, stock_msg.price, stock_msg.vwap, stock_msg.volume, stock_msg.f1,stock_msg.t1, stock_msg.f2, stock_msg.f3, stock_msg.f4);

			stock_data_msg.write(out);
		}
	} else {
		std::cout<< "Probably file is missing" << std::endl;
		return 1;
	}

	in.close();
	out.close();

	return 0;
}

