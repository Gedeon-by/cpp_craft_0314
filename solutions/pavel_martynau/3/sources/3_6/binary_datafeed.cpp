#include <iostream>
#include <fstream>
#include <boost/cstdint.hpp>
#include <string>
#include <map>
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
} tmp_msg;

int main()
{
	std::map<std::string, std::ofstream> fstreams;

	std::ifstream input( BINARY_DIR "/input.txt", std::ios::binary );

	if(input){
		while( input.read(tmp_msg.stock_name, 8) ) {
			std::cout << tmp_msg.stock_name << std::endl;;
			input.read(tmp_msg.date, 8);
			input.read( reinterpret_cast<char*>(&tmp_msg.price), sizeof( tmp_msg.price ) );
			input.read( reinterpret_cast<char*>(&tmp_msg.vwap), sizeof( tmp_msg.vwap ) );
			input.read( reinterpret_cast<char*>(&tmp_msg.volume), sizeof( tmp_msg.volume ) );
			input.read( reinterpret_cast<char*>(&tmp_msg.f1), sizeof( tmp_msg.f1 ) );
			input.read( reinterpret_cast<char*>(&tmp_msg.t1), sizeof( tmp_msg.t1 ) );
			input.read( reinterpret_cast<char*>(&tmp_msg.f2), sizeof( tmp_msg.f2 ) );
			input.read( reinterpret_cast<char*>(&tmp_msg.f3), sizeof( tmp_msg.f3 ) );
			input.read( reinterpret_cast<char*>(&tmp_msg.f4), sizeof( tmp_msg.f4 ) );

			binary_reader::stock_data stock_msg(tmp_msg.stock_name,
				tmp_msg.date, 
				tmp_msg.price, 
				tmp_msg.vwap, 
				tmp_msg.volume, 
				tmp_msg.f1,
				tmp_msg.t1, 
				tmp_msg.f2, 
				tmp_msg.f3, 
				tmp_msg.f4);

			std::map<std::string, std::ofstream>::iterator map_it = fstreams.find(std::string(tmp_msg.stock_name));
			if( map_it == fstreams.end() ) {
				fstreams.insert( std::pair<std::string, std::ofstream>(std::string(tmp_msg.stock_name), std::ofstream(BINARY_DIR "/output_" + std::string(tmp_msg.stock_name) + ".txt", std::ofstream::trunc|std::ios::binary)) );
				std::cout << BINARY_DIR "/output_" + std::string(tmp_msg.stock_name) + ".txt";
				stock_msg.write( fstreams.find(std::string(tmp_msg.stock_name))->second );
			} else {
				stock_msg.write(map_it->second);
			}
		}
	} else {
		std::cout<< "Probably file is missing" << std::endl;
		return 1;
	}

	input.close();

	for (std::map<std::string, std::ofstream>::iterator it=fstreams.begin(); it!=fstreams.end(); ++it)
		it->second.close();
	
	return 0;
}