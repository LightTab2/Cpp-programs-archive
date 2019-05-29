#include <iostream>
#include <cmath>
#include <chrono>
#include <cstring>
using namespace std;

bool nolog = false, nopause = false, timer = false;
bool *primes;
unsigned long long z;

void EliminateDuplicates(unsigned long long x)
{
    x+=2;
    unsigned long long add, next[2];
    if (x & 1)
    {
        --x;
        add = x * 6ull + 2ull;
        next[0] = -x + add - 2ull;
        next[1] = x + add - 1ull;
    }
    else
    {
        add = x * 6 - 2;
        next[0] = -x + add - 1ull;
        next[1] = x + add - 2ull;
    }
    cout << (add >> 1) << ' ';

    for (;next[0] < z; next[0]+=add, next[1]+=add)
    {
        primes[next[0]] = false;
        if (next[1] < z) primes[next[1]] = false;
    }
}

int main(int argc, char *args[])
{
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);
    for (int x = 0; x != argc; ++x)
    {
        if (!strcmp(args[x],"-nolog")) nolog = true;
        else if (!strcmp(args[x], "-nopause")) nopause = true;
        else if (!strcmp(args[x], "-time")) timer = true;
    }
    if (!nolog) cout << "Tresc zadania, ktore ten program rozwiazuje to:\n"
        "Znajdz wszystkie liczby w przedziale <1;z>.\n"
        "Rozwiazanie:\n"
        "Tworze i wypisuje sito Eratostenesa, czyli strukture zawierajaca wylacznie liczby pierwsze w taki"
        "sposob:\n\n"
        "Wypisuje 1,2,3\n"
        "Liczbami pierwszymi moga byc tylko liczby"
        "niepodzielne przez 2 i 3, czyli musza byc w postaci 6n - 1 lub 6n + 1 dla dowolnej liczby"
        "naturalnej n.\n Struktura uwzglednia wszystkie takie elementy o wartosci mniejszych od podanego zakresu.\n"
        "Zapisuje ja jako tablice booleanów (liczba pierwsza lub nie)\n\n"
        "Pierwsza liczba jaka rozpatruje to 6n - 1, jezeli jest pierwsza (ma wartosc true w tablicy) to eliminuje "
        "jej wielokrotnosci, czyli elementy o indeksie 2(c*(6n-1) + n)-2 i 2(c*(6n-1) - n) - 1"
        "dla dowolnej naturalnej liczby c dowod"
        "jest prosty:\n"
        "(6c-1)*(6n-1) = 6c(6n-1) - (6n-1) = 6*(c * (6n-1) - n) + 1 = 6q + 1\n"
        "(6c+1)*(6n-1) = 6c(6n-1) + (6n-1) = 6*(c * (6n-1) + n) - 1 = 6p - 1\n"
        "Dlaczego jest to pomnozone przez 2 i w pierwszym odjete 2, a w druim 1? Poniewaz tablica booleanow "
        "posiada dla jednego n dwa elementy, reprezentujace 6n-1 i 6n+1 (p lub q) i indeksowanie zaczyna sie od 0\n"
        "Analogicznie dla 6n+1 mamy indeksy 2(c*(6n+1) + n)-1 i 2(c*(6n+1) - n)\n\n"; 

    if (!nolog) cout << "Podaj liczbe naturalna z:" << endl;
    cin >> z;
    if (!nolog) cout << endl;

    if (!nolog) cout << "Wszystkie liczby pierwsze mniejsze od lub rowne " << z << " to :" << endl;
    for (int x = 2; x != z && x != 4; ++x) cout << x << ' ';
    chrono::time_point<chrono::high_resolution_clock> start, stop;
    if (timer) start = chrono::high_resolution_clock::now();

    ++z;
    bool notsub = (z%6) > 1;
    z /= 6; z <<= 1;
    if (!notsub) --z;

    primes = new bool[z]; //mimo, ze bool normalnie zajmuje 1 bajt, to w tablicy jest to optymalizowane (1 bit)

    for (unsigned long long x = 0; x != z; ++x) primes[x] = true;

    for (unsigned long long x = 0; x != z; ++x)
    {
        if (primes[x])
            EliminateDuplicates(x);
        ++x;
        if (x == z) break;
        if (!primes[x]) continue;
        EliminateDuplicates(x);
    }

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
