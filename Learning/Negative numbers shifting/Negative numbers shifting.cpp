#include <iostream>

bool nolog = false, nopause = false;
int main(int argc, char *args[])
{
    for (int x = 0; x != argc; ++x)
    {
        if (args[x] == "-nolog") nolog = true;
        else if (args[x] == "-nopause") nopause = true;
    }
    int i = -2;
    std::cin >> i;
    for (int n = 1; n != 32; ++n)
        std::cout << (i << n) << std::endl;

    if (!nolog) std::cout << "Now right-shifts\n";
    for (int n = 1; n != 32; ++n)
        std::cout << (i >> n) << std::endl;
    if (!nopause) system("pause");
    return 0;
}

