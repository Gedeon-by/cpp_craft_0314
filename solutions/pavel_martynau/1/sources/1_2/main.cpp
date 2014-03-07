#include <iostream>
#include <fstream>
#include <vector>

void readFile(unsigned int& N, std::vector<float>& codes, std::vector<float>& passes) {
	std::ifstream input_file( BINARY_DIR "/input.txt" );
	//input_file.precision(4);
	input_file >> N;
	float tmp;
	for(size_t i = 0; i < N; i++){
		input_file >> tmp;
		codes.push_back(tmp);
	}
	while( !input_file.eof() )
	{
		input_file >> tmp;
		passes.push_back(tmp);
	}
	input_file.close();
}

int main(int argc, char* argv[]) {
	unsigned int N;
	std::vector<float> codes;
	std::vector<float> passes;
	readFile(N, codes, passes);
	std::ofstream output_file( BINARY_DIR "/output.txt", std::ios::trunc );
	bool haveEqual = false;
	for(size_t i = 0; i < passes.size(); i++){
		std::cout << "    " << passes[i] << std::endl;
		for(size_t j = 0; j < codes.size(); j++) {
			std::cout << "    " << codes[j] << std::endl;
			if( abs( passes[i] - codes[j] ) < 0.0001 ) haveEqual = true;
		}
		if ( haveEqual ) output_file << "YES" << std::endl;
		else  output_file << "NO" << std::endl;
		haveEqual = false;
	}
	output_file.close();
	return 0;
}