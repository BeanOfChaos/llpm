#include <cstring>
#include <iostream>
#include <iomanip>
#include <string>

#include "hasher.hpp"

int main(int argc, char **argv) {
	if (argc < 2){
		std::cout << "Usage: " << argv[0] << " <text to be hashed>" << std::endl;
		return 0;
	}
	
	SHA256_Hasher hasher;
	for (int i = 0; i < argc; ++i) {
		hasher.update(argv[i]);
	}
	std::cout << hasher.hash()->hex() << std::endl;
	for (int i = 0; i < 1000; ++i) hasher.rehash();

	std::cout << hasher.hash()->hex() << std::endl;
	
	return 0;
}
