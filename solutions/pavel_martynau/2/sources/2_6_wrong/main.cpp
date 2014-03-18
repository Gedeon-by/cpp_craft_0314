#include <iostream>
#include <fstream>
#include <stdint.h>
#include <string>

//stock_name – string (длинна строки не более 8 char), date_time: дата в формате YYYYMMDD, price: double, vwap: double, volume: uint32, (f1, t1, f2, f3, f4) данные о торгах за день типа double.

const char start_date[] = {'0','0','0','1','0','1','0','1'};

int days_count(const char date[] ) {
	//char year[4];
	//memcpy(year, &date[0], 2*sizeof(*a));

	return 0;
}

struct stock_data {
	char stock_name[8];
	char date[8];
	double price;
	double vwap;
	uint32_t volume;
	double f1;
	double t1;
	double f2;
	double f3;
	double f4;
};

int main() {
	std::ifstream input_file ( BINARY_DIR "/2.6.in", std::ios::binary );
	std::ofstream output_file ( BINARY_DIR "/2.6.out", std::ofstream::trunc|std::ios::binary );
	if(input_file.is_open()){
		stock_data msg;
		while( input_file.read( msg.stock_name, sizeof( msg.stock_name ) )  ) {	
			input_file.read( msg.date, sizeof( msg.date ) );
			input_file.read( reinterpret_cast<char*>( &msg.price ), sizeof( msg.price ) );
			input_file.read( reinterpret_cast<char*>( &msg.vwap ), sizeof( msg.vwap ) );
			input_file.read( reinterpret_cast<char*>( &msg.volume ), sizeof( msg.volume ) );
			input_file.read( reinterpret_cast<char*>( &msg.f1 ), sizeof( msg.f1 ) );
			input_file.read( reinterpret_cast<char*>( &msg.t1 ), sizeof( msg.t1 ) );
			input_file.read( reinterpret_cast<char*>( &msg.f2 ), sizeof( msg.f2 ) );
			input_file.read( reinterpret_cast<char*>( &msg.f3 ), sizeof( msg.f3 ) );
			input_file.read( reinterpret_cast<char*>( &msg.f4 ), sizeof( msg.f4 ) );

			//std::cout << msg.stock_name  << " " << msg.date[0]<< msg.date[1]<< msg.date[2]<< msg.date[3]<< msg.date[4]<< msg.date[5]<< msg.date[6]<< msg.date[7] << " "  << msg.price << " "  << msg.vwap << " "  << msg.volume << " "  << msg.f1 << " " << msg.t1 << " " << msg.f2 << " " << msg.f3 << " " << msg.f4 << " " << std::endl;
			//std::cout <<"date = "  " size of date = " << sizeof(msg.date) << std::endl;
		}

		input_file.close();
		output_file.close();
	}

	return 0;
}