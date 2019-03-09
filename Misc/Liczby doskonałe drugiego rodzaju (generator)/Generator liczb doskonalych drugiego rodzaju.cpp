#include <fstream>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
#include "primes.h"

using std::ofstream, std::stringstream;
bool nolog = false, nopause = false;
ofstream dosk("LIC.cpp");
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
    std::vector<unsigned> buffer;
    
    unsigned doskmax = 5000000;
    if (!nolog) std::cout << "Podaj gorna granice liczb doskonalych drugiego rodzaju (powinna byc wieksza od 8):\n" << std::flush;
    std::cin >> doskmax;

    if (!nolog) std::cout << "...\n" << std::flush;
    unsigned cdosk = 0; //Licznik elementów w powstałej tablicy

    dosk << "const unsigned *const dosk = new const unsigned[";
    unsigned mbuffer; //MultiplicationBuffer

    for (unsigned n = 0; n != nprimes-1; ++n)
    {
        if ((mbuffer=primes[n]*primes[n]*primes[n]) <= doskmax) 
        {
            buffer.push_back(mbuffer); //p[n]^3
            ++cdosk;
        }
        for (unsigned x = n+1; x != nprimes; ++x) //p[n] * p[x]
        {
            if ((mbuffer=primes[n] * primes[x]) > doskmax) break;
            buffer.push_back(mbuffer);
            ++cdosk;
        }
    }
    std::sort(buffer.begin(), buffer.end());

    //Pierwsza instancja, żeby nie trzeba było potem spradzać warunku (mimo, że i tak byłoby to zoptymalizowane później...)
    dosk << cdosk << "] {";

    dosk << buffer[0];
    for (auto it = buffer.cbegin()+1; it != buffer.cend(); ++it)
    {
        dosk << ',' << *it;
    }
    
    dosk << "};\n"; //Zapis tablicy
    dosk << "const unsigned ndosk = " << cdosk << ';' << std::flush; //Zapis liczby elementów tej tablicy
    
    if (!nolog) std::cout << "Sukces!\n" << std::flush;
    if (!nopause) system("pause");
    delete[] primes;
    return 0;
}
