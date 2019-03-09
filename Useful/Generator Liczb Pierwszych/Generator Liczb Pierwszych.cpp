#include <fstream>
#include <iostream>
#include <cmath>
#include <sstream>
#include <algorithm>
using std::ofstream, std::stringstream;
ofstream primes("primes.h");
bool nolog = false, nopause = false;
int main(int argc, char *args[])
{
    for (int x = 0; x != argc; ++x)
    {
        if (args[x] == "-nolog") nolog = true;
        else if (args[x] == "-nopause") nopause = true;
    }
    //Brak synchronizacji z strumieniami z C
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);
    stringstream buffer;

    if (!nolog) std::cout << "Podaj gorna granice liczb pierwszych, ktore chcesz otrzymac:\n" << std::flush;

    unsigned lpierwszych = 2; //Najwieksza mozliwa liczba
    std::cin >> lpierwszych;
    
    if (!nolog) std::cout << "...\n" << std::flush;
    unsigned cpierwszych = 1; //Licznik elementów w powstałej tablicy

    primes << "const unsigned *const primes = new const unsigned[";
    buffer << 2;
    for (unsigned n = 3; n != lpierwszych; ++n)
    {
        unsigned x = 2, s = ceil(sqrt(n))+1;
        for (; x!=s; ++x)
        {
            if (!(n % x)) break; //Jeżeli dzieli się przez liczbę w przedziale <2;s> bez reszty to algorytm przerywa działanie
        }
        if (x == s) //Liczba jest pierwsza
        {
            buffer << ',' << n;
            ++cpierwszych;
        }
    }
    primes << cpierwszych << "] {" << buffer.str() << "};\n"; //Zapis tablicy
    primes << "const unsigned nprimes = " << cpierwszych << ';' << std::flush; //Zapis liczby elementów tej tablicy
    
    if (!nolog) std::cout << "Sukces!\n" << std::flush;
    if (!nopause) system("pause");
    return 0;
}
