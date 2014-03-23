#include <boost/thread.hpp>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <market_message.h>

class my_exception
	{
	};
	
std::string get_file_name(std::string direct, int num){
	std::ostringstream file_name;
	file_name << "/"<<direct<<"_" << num << ".txt";
	return file_name.str();
}

void file_handling(int thread_num) {
	if( thread_num ){
		std::string in_file_path = BINARY_DIR + get_file_name("input", thread_num);
		std::cout<< thread_num << std::endl;
		std::ifstream in(in_file_path, std::ios::binary);

		if(in) {
			std::string out_file_path = BINARY_DIR + get_file_name("output", thread_num);
			std::cout<< out_file_path << std::endl;
			std::ofstream out(out_file_path, std::ios::trunc|std::ios::binary);
			while( !in.eof() ) {
				binary_reader::market_message msg(in);
				if(msg.msg()[0] != EOF) {
					std::cout<< "MSG() " << msg.msg()<< " "<< msg.type() << std::endl;
					msg.write(out);
				} else {
					break;
				}
			}
			in.close();
			out.close();
		} else {
			std::cout<< "File " << get_file_name("input", thread_num) << " doesn't exist." << std::endl;
			//boost::this_thread::
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
}
