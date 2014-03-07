#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

std::vector<std::string> readFile() {
	std::ifstream input_file( BINARY_DIR "/input.txt" );
	std::string line;
	std::vector<std::string> lines;
	while( !input_file.eof() )
	{
		std::getline( input_file, line );
		lines.push_back(line);
	}
	input_file.close();

	return lines;
}

void stringReverse(std::string& str){
	std::reverse(str.begin(), str.end());
}

void stringToLower(std::string& str){
	std::transform(str.begin(), str.end(), str.begin(), ::tolower);
}

void removeChars(std::string& str){
	char chars[] = " -/";

	for (unsigned int i = 0; i < strlen(chars); ++i){
		str.erase (std::remove(str.begin(), str.end(), chars[i]), str.end());
	}
}

int main(int argc, char* argv[]) {
	std::string str = "aSdfGhjKLLLL";
	std::vector<std::string> fileStrings = readFile();
	std::ofstream output_file( BINARY_DIR "/output.txt", std::ios::trunc );
	for(size_t i = 1; i < fileStrings.size(); i++){
		stringToLower(fileStrings[i]);
		removeChars(fileStrings[i]);
		stringReverse(fileStrings[i]);
		if ( std::string::npos != fileStrings[0].find(fileStrings[i]) ) output_file << "YES" << std::endl;
		else  output_file << "NO" << std::endl;
	}
	output_file.close();
	return 0;
}