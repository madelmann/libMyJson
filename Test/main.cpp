
#ifdef _WIN32
#	include <stdlib.h>
#	include <windows.h>

	typedef unsigned int uint32_t;
#else
#	include <chrono>
#endif

#include <iostream>
#include <fstream>
#include <../Json/Json.h>

static const uint32_t ntimes = 10;

int main(int argc, char** argv)
{
	if ( argc < 2 ) {
		return -1;
	}

	std::ifstream inputfile(argv[1]);
	std::string to_parse;

	inputfile.seekg(0, std::ios::end);
	to_parse.reserve(inputfile.tellg());
	inputfile.seekg(0, std::ios::beg);

	to_parse.assign((std::istreambuf_iterator<char>(inputfile)),
					 std::istreambuf_iterator<char>());

#ifdef _WIN32
	long start = GetTickCount();
#else
	std::chrono::steady_clock::time_point start_time = std::chrono::steady_clock::now();
#endif

	for ( unsigned int i = 0; i < ntimes; ++i ) {
		//std::cout << "i/ntimes = " << i << "/" << ntimes << std::endl;

		Json::Value parsed_object;
		Json::Reader parser;
		/*bool result =*/ parser.parse(to_parse, parsed_object);

		//std::cout << parsed_object.toStyledString() << std::endl;
	}

#ifdef _WIN32
	long diff = GetTickCount() - start;

	std::cout << "[+] Finished successfully with an average of: " << diff / ntimes << " ms\n" << std::endl;

#else
	std::chrono::steady_clock::time_point end_time = std::chrono::steady_clock::now();
	std::chrono::microseconds us = chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);

	std::cout << "[+] Finished successfully with an average of: " << (us.count() / ntimes) / 1000 << " ms\n" << std::endl;
#endif
}

