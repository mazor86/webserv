
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fcntl.h>
#include <vector>

int main()
{
	const int nContentLength = atoi(getenv("Content-Length"));
	std::cout << "RRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRR\n";
		// "\n" << 
		// "Content-Length = " << nContentLength << "\n" <<
		// "VARIABLE2 = " << getenv("VARIABLE2") << "\n" <<
		// "VARIABLE3 = " << getenv("VARIABLE3") << "\n" <<
		// "\n\n";


	return 0;
}