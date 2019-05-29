#include <iostream>
#include <string.h>
#include <fstream>
#include <cmath>
#include <Windows.h>
using namespace std;

int main(int argc, char *args[])
{
    ifstream correct("primes.txt");
    for (unsigned n = 3; n != 10000000; ++n)
    {
        correct.seekg(0);
        ofstream arg("arg.txt");
        arg << n;
        arg.close();

        system("Prime.exe -nolog -nopause < arg.txt > opt.txt");
        Sleep(10 + sqrt(n)); //should be enough for the program to get the results, though I could accomplish this in a more civilized way by using my C# interface program or a winapi check whether the process had died already
        ifstream opt("opt.txt");
        int x = 0, correctx = 0;
        while (opt >> x)
        {
            correct >> correctx;
            if (x != correctx) 
            {
                cout << n << ' ';
                break;
            }
        }
    }
    system("pause");
    return 0;
}
