#include <iostream>
#include <cmath>
#include <chrono>
#include <cstring>
#include <random>
using namespace std;

bool nolog = false, nopause = false, timer = false;

unsigned long long ModuloMulti(unsigned long long a, unsigned long long b, unsigned long long &mod) //upewnia sie, ze nie wyjdziemy poza zakres zmiennych
{
    unsigned long long res = 0;
    for (;;) //przechodzimy przez kazdy bit b i obliczamy (a^i % mod) * ... * (a^m % mod), gdzie i...m to indeksy jedynek w zapisie binarnym b
    {
        if (b & 1) 
        {
            res += a;
            res %= mod;
        };
        if (!(b >>= 1)) break;
        a <<= 1;
        a %= mod;
    }
    return res;
}

unsigned long long randomLCG(unsigned long long &&a, unsigned long long &&c, unsigned long long &&m, unsigned long long &seed)
{
    return (ModuloMulti(seed, a, m) + c) % m;
}

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
    unsigned long long n;
    if (!nolog) cout << "Wygeneruj n liczb pseudolosowych:\n"
        "Rozwiazanie:\n"
        "Ustanawiam zmienna [X1] zalezna od czasu uruchomienia.\n Tworze funkcje ktora zwraca [Xn] o wzorze "
        "[Xn] = (a * [X(n-1)]) mod m, gdzie wspolczynniki sa specjalnie dobrane, by okres powtarzania byl"
        "rowny m-1. Te wspolczynniki to a = 44485709377909 i m = 281474976710656\n\n";

    if (!nolog) cout << "Podaj liczbe naturalna n:" << endl;
    cin >> n;
    ++n;
    chrono::time_point<chrono::high_resolution_clock> start, stop;
    start = chrono::high_resolution_clock::now();
    unsigned long long seed = time(0);
    while (--n) cout << (seed = randomLCG(44485709377909, 0, 281474976710656, seed)) << ' ';

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
