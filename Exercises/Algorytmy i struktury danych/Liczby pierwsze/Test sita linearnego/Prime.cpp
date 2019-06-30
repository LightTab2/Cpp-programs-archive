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
    bool *primes;
    unsigned long long n;
    if (!nolog) cout << "Tresc zadania, ktore ten program rozwiazuje to:\n"
        "Znajdz wszystkie liczby w przedziale <1;n>.\n"
        "Rozwiazanie:\n"
        "Tworze i wypisuje sito liniowe, czyli strukture zawierajaca wylacznie liczby pierwsze w taki "
        "sposob:\n\n"
        "Algorytm zaczyna od 2 i oznaczmy te liczbe x\n"
        "Wykluczam ze zbioru wszystkich liczb naturalnych z przedzialu <1;n> wielokrotnosci x:\n"
        "Usuwam ze zbioru kazda liczbe w niej znajdujaca sie, mnozona przez x, az przekroczy n\n\n";

    if (!nolog) cout << "Podaj liczbe naturalna n:" << endl;
    cin >> n;
    ++n;
    if (!nolog) cout << endl;

    if (!nolog) cout << "Wszystkie liczby pierwsze mniejsze od lub rowne " << n-1 << " to :" << endl;
    chrono::time_point<chrono::high_resolution_clock> start, stop;
    if (timer) start = chrono::high_resolution_clock::now();
    primes = new bool[n];

    for (unsigned long long x = 0; x != n; ++x) primes[x] = true;

    if (timer) stop = chrono::high_resolution_clock::now();
    
    for (int i = 3; i != n; ++i) primes[i] = true;
    int a = 2, b, c;
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
    cout << 1 << ' ' << 2 << ' ';
    for (int i = 3; i != n; ++i) if(primes[i]) cout << i << " ";

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
