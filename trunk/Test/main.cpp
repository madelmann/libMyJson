
#include <chrono>
#include <iostream>
#include <fstream>
#include <Json.h>

using namespace std;

static const uint32_t ntimes = 10;

int main(int argc, char** argv)
{
	if ( argc < 2 ) {
		return -1;
	}

	ifstream inputfile(argv[1]);
	std::string to_parse;

	inputfile.seekg(0, std::ios::end);
	to_parse.reserve(inputfile.tellg());
	inputfile.seekg(0, std::ios::beg);

	to_parse.assign((std::istreambuf_iterator<char>(inputfile)),
					 std::istreambuf_iterator<char>());

	chrono::steady_clock::time_point start_time = chrono::steady_clock::now();

	for ( unsigned int i = 0; i < ntimes; ++i ) {
		//std::cout << "i/ntimes = " << i << "/" << ntimes << std::endl;

		Json::Value parsed_object;
		Json::Reader parser;
		/*bool result =*/ parser.parse(to_parse, parsed_object);

		//std::cout << parsed_object.toStyledString() << std::endl;
	}

	chrono::steady_clock::time_point end_time = chrono::steady_clock::now();
	chrono::microseconds us = chrono::duration_cast<chrono::microseconds>(end_time - start_time);

	cout << "[+] Finished successfully with an average of: " << (us.count() / ntimes) / 1000 << " ms\n";
}

