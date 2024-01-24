#include <iostream>

#include "database.hpp"
#include "hmac.hpp"

int main(int argc, char **argv) {
	if (argc < 2)
	{
		std::cerr << "Usage: " << argv[0] << " <some string to sign>" << std::endl;
		exit(1);
	}

	std::string tbs(argv[1]);
	unsigned char pkey[64];
	for (int i = 0; i < 64; ++i)
		pkey[i] = i;
	Signature<SHA256_Hasher> s(tbs, pkey, 64);
	std::cout << s.hex() << std::endl;
	
	return 0;
}
