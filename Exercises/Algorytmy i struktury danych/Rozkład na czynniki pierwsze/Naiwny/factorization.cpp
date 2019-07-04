#include <iostream>
#include <cmath>
#include <chrono>
#include <cstring>
using namespace std;

bool nolog = false, nopause = false, timer = false;

int main(int argc, char *args[])
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    for (int x = 0; x != argc; ++x)
    {
        if (!strcmp(args[x],"-nolog")) nolog = true;
        else if (!strcmp(args[x], "-nopause")) nopause = true;
        else if (!strcmp(args[x], "-time")) timer = true;
    }
    unsigned long long p, n;
    bool *primes;
    if (!nolog) cout << "Tresc zadania, ktore ten program rozwiazuje to:\n"
        "Znajdz rozklad liczby p > 1 na iloczyn czynnikow pierwszych.\n"
        "Rozwiazanie:\n"
        "Jest to algorytm naiwny, wiec najpierw znajduje liczby pierwsze do pierwiastka z p, potem sprawdzam, "
        "czy dziela one rozpatrywana liczbe\n\n";
    if (!nolog) cout << "Podaj liczbe naturalna p:" << endl;
    cin >> p;
    if (!nolog) cout << endl;

    if (!nolog) cout << "Rozklad na czynniki pierwsze liczby " << p << ":" << endl;
    chrono::time_point<chrono::high_resolution_clock> start, stop;
    if (timer) start = chrono::high_resolution_clock::now();
    n = sqrt(p) + 1;
    primes = new bool[n];

    for (unsigned long long x = 0; x != n; ++x) primes[x] = true;
    
    for (unsigned long long i = 3; i != n; ++i) primes[i] = true;
    unsigned long long a = 2, b, c;
    while (a * a < n) //a * a to najmniejsza wielokrotność rozpatrywana (mniejsze zostały już wykluczone przy poprzednich wartościach a)
    {
        b = a;
        while ((c = a * b) < n)
        {
            while (c < n)
            {
                primes[c] = false;
                c *= a;
            }
            while (!primes[++b]); //znajdujemy następny element w zbiorze dla b
        }
        while (!primes[++a]); //up dla a
    }
    primes[2] = true;
    bool first = true;

    for (unsigned long long i = 2; i != n; ++i) 
        if (primes[i])
        {
            unsigned long long count = 0;
            while (!(p % i))
            {
                p /= i;
                ++count;
            }
            if (count > 1) cout << (first ? "" : " * ") << i << '^' << count;
            else if (count) cout << (first ? "" : " * ") << i;
            if (first && count) first = false;
        }

    if (p != 1) cout << (first ? "" : " * ") << p;
    cout << endl;

    if (timer)
    {
        stop = chrono::high_resolution_clock::now();
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
