#include <iostream>
#include <cmath>
#include <chrono>
#include <cstring>
#include <list>
using namespace std;

bool nolog = false, nopause = false, timer = false;

int main(int argc, char *args[])
{
    for (int x = 0; x != argc; ++x)
    {
        if (!strcmp(args[x],"-nolog")) nolog = true;
        else if (!strcmp(args[x], "-nopause")) nopause = true;
        else if (!strcmp(args[x], "-time")) timer = true;
    }
    unsigned long long n;
    list<unsigned long long> primes;
    if (!nolog) cout << "Tresc zadania, ktore ten program rozwiazuje to:\n"
        "Znajdz n kolejnych liczb pierwszych.\n"
        "Rozwiazanie:\n"
        "Tworze sito Eratostenesa, czyli: ...\n\n"; //todo: explain the alogrithm, implement it

    if (!nolog) cout << "Podaj liczbe naturalna n:\n";
    cin >> n;
    cout << endl;
    
    if (!nolog) cout << n << " kolejnych liczb pierwszych to:\n";
    chrono::time_point<chrono::high_resolution_clock> start, stop;
    if (timer) start = chrono::high_resolution_clock::now();

    if (timer) stop = chrono::high_resolution_clock::now();
    cout << endl;
    if (timer)
    {
        if (!nolog) cout << "Wykonanie algorytmu trwalo: ";
        auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
        cout << fixed << duration.count();
        if (!nolog) cout << " mikrosekund";
        cout << endl;
    }
    //Press any key to exit the program
    if (!nopause) system("pause");
    return 0;
}
