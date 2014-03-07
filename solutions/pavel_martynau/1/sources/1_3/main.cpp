#include <iostream>
#include <fstream>
#include <string>
#include <vector>

void search(const size_t i, const size_t j, std::vector< std::vector<char> >& map){
	if ( map[i][j] == 'o' ) {
		map[i][j] = '~';
		if( i < map.size() - 1 ) search(i + 1, j, map);
		if( i != 0 ) search(i - 1, j, map);
		if( j < map[i].size() -1 ) search(i, j + 1, map);
		if( j != 0 ) search(i, j - 1, map);
	}
}

void readFile(std::vector< std::vector<char> >& lines) {
	std::ifstream input_file( BINARY_DIR "/input.txt" );
	std::string line;
	
	while( !input_file.eof() )
	{
		std::vector<char> newLine;
		std::getline( input_file, line );
		for (size_t i=0; i<line.length(); i++){
			newLine.push_back( line.at(i) );
		}
		lines.push_back(newLine);
	}
	input_file.close();
}

int main() {
	int res = 0;
	std::vector< std::vector<char> > map;
	readFile(map);
	for(size_t i = 0; i < map.size(); i++){
		for(size_t j = 0; j < map[i].size(); j++) {
			if ( map[i][j] == 'o' ) {
				res++;
				search(i, j, map);
			}
		}
	}
	std::ofstream output_file( BINARY_DIR "/output.txt", std::ios::trunc );
	output_file << res << std::endl;
	output_file.close();

	return 0;
}