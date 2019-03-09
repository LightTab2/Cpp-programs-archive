#include <iostream>

bool nolog = false;
int main(int argc, char *args[])
{
    for (int x = 0; x != argc; ++x)
    {
        if (args[x] == "-nolog") nolog = true;
    }
	int buffer = 0;
	while (std::cin >> buffer)
	{
		buffer <<= 2;
	    std::cout << buffer << std::endl;
	}
}
