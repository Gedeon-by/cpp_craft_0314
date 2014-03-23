#include <boost/cstdint.hpp>
#include <fstream>
#include "stock_data.h"

binary_reader::stock_data::stock_data( std::ifstream& in )
{

}
binary_reader::stock_data::stock_data( const char* stock_name,
							const char* date_time,
							const double price,
							const double vwap,
							const boost::uint32_t volume,
							const double f1,
							const double t1,
							const double f2,
							const double f3,
							const double f4 ) : price_(price), vwap_(vwap), volume_(volume), f1_(f1), t1_(t1), f2_(f2), f3_(f3), f4_(f4)
{
	strncpy(stock_name_, stock_name, 8);
	stock_name_[8] = '\0';
	strncpy(date_time_, date_time, 8);
	date_time_[8] = '\0';
}
binary_reader::stock_data::~stock_data()
{
	// your code
}
void binary_reader::stock_data::write( std::ofstream& out )
{
	boost::uint32_t date = get_days();
	out.write(stock_name_, 9);
	out.write((char*)&date, sizeof(date));
	out.write((char*)&vwap_, sizeof(vwap_));
	out.write((char*)&volume_, sizeof(volume_));
	out.write((char*)&f1_, sizeof(f1_));
	out.write((char*)&f4_, sizeof(f4_));
	out.write((char*)&f3_, sizeof(f3_));
}
boost::uint32_t binary_reader::stock_data::get_days() const {
	int y=0;
	int m=0;
	int d=0;
	std::sscanf(date_time_, "%4d%2d%2d", &y, &m, &d);
	y -= 1;
	m -=1;

	return y*372 + m*31 + d;
}
void binary_reader::stock_data::write_raw( std::ofstream& out )
{	
	// your code. Can be emty
	// this method is used for testing. It writes data to the binary file without convertion.
}
