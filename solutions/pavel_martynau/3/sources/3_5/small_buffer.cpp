#include <boost/thread/mutex.hpp>
#include <boost/thread.hpp>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <boost/cstdint.hpp>
#include <market_message.h>
#include <map>

boost::mutex buffer_mutex;

struct message_str {
	boost::uint32_t type;
	boost::uint32_t time;
	boost::uint32_t length;
	char *message_ptr;
} msg_temp;

std::string get_file_name(std::string direct, int num){
	std::ostringstream file_name;
	file_name << "/"<<direct<<"_" << num << ".txt";
	return file_name.str();
}

void file_handling(int thread_num) {
	if( thread_num ){
		std::map<boost::uint32_t, std::map<boost::uint32_t, int>> msg_type_time_qty;

		int buffer_size = 2048;

		boost::uint32_t current_time = 0;

		std::string in_file_path = BINARY_DIR + get_file_name("input", thread_num);
		std::cout<< thread_num << std::endl;
		std::ifstream in(in_file_path, std::ios::binary);

		if(in) {
			while( in.read( (char*)&msg_temp.type, sizeof( msg_temp.type ) ) ) {
				boost::unique_lock<boost::mutex> scoped_lock(buffer_mutex);

				in.read( (char*)&msg_temp.time, sizeof( msg_temp.time ) );
				in.read( (char*)&msg_temp.length, sizeof( msg_temp.length ) );
				msg_temp.message_ptr = new char[msg_temp.length];

				if(buffer_size - ( sizeof( msg_temp.type ) + sizeof( msg_temp.time ) + sizeof( msg_temp.length ) + msg_temp.length) ){
				
					in.read(msg_temp.message_ptr, msg_temp.length);

					binary_reader::market_message mrkt_msg(msg_temp.type, msg_temp.time, msg_temp.length, msg_temp.message_ptr);

					if( mrkt_msg.type() != current_time ) 
						current_time = mrkt_msg.type();
					if( msg_type_time_qty.find(mrkt_msg.type()) != msg_type_time_qty.end() ) { //if message of presented type came for the fisrt time
						msg_type_time_qty[mrkt_msg.type()].insert( std::make_pair( mrkt_msg.time(), 1 ) );
					} else {
						if( msg_type_time_qty[ mrkt_msg.type() ].find( mrkt_msg.time() ) != msg_type_time_qty[mrkt_msg.type()].end() ) {//if message of presented type came for the fisrt time in this sec
							msg_type_time_qty[ mrkt_msg.type() ].insert(std::make_pair(mrkt_msg.time(), 1) );
						} else {
							msg_type_time_qty[ mrkt_msg.type() ][mrkt_msg.time()] += 1;
						}
					}
				}else{
					in.ignore(msg_temp.length);
				}
			
			}

			std::string out_file_path = BINARY_DIR + get_file_name("output", thread_num);
			std::ofstream out(out_file_path, std::ios::trunc|std::ios::binary);

			for (std::map<boost::uint32_t, std::map<boost::uint32_t, int>>::iterator i = msg_type_time_qty.begin(), iend = msg_type_time_qty.end(); i != iend; ++i)
			{
				boost::uint32_t sec = 0;
				boost::uint32_t qty = 0;
				for (std::map<boost::uint32_t, int>::iterator j = i->second.begin(), jend = i->second.end(); j != jend; ++j)
				{
					sec++;
					qty += j->second;
				}
				qty /= sec;
				out.write( (char*)&i->first, sizeof(i->first) );
				out.write( (char*)&qty, sizeof(qty) );
			}

	
			out.close();
		} else {
			std::cout<< "File " << get_file_name("input", thread_num) << " doesn't exist." << std::endl;
		}
		in.close();
	}
}

int main()
{
	for(size_t i = 1; i < 100; i++) {
		boost::thread t(&file_handling, i);
		t.join();
	}

	return 0;
}