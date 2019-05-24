#include <iostream>
#include <cmath>
#include <chrono>
#include <cstring>
using namespace std;

bool nolog = false, nopause = false, timer = false;
bool *primes;
unsigned long long z;
int endz;

void EliminateDuplicates(int x)
{
    bool add_one = x & 1;
    x+=2;
    x>>=1;
    int add = x * 6;
    if (add_one) ++add;
    else --add;

    cout << add << ' ';
    add <<= 1;

    int next[2] = {-2*x+add-1, 2*x+add-1};
    if (add_one) --next[0];
    else --next[1];

    for (;next[0] < endz; next[0]+=add, next[1]+=add)
    {
        //cout << next[0] << ' ' << next[1] << endl;
        primes[next[0]] = false;
        if (next[1] < endz) primes[next[1]] = false;
    }
}

int main(int argc, char *args[])
{
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

    if (!nolog) cout << "Podaj liczbe naturalna z:\n";
    cin >> z;
    cout << endl;

    if (!nolog) cout << "Wszystkie liczby pierwsze mniejsze od lub rowne " << z << " to :\n";
    for (int x = 0; x != z && x != 4;++x) cout << x << ' ';
    chrono::time_point<chrono::high_resolution_clock> start, stop;
    if (timer) start = chrono::high_resolution_clock::now();

    primes = new bool[z/3]; //mimo, ze bool normalnie zajmuje 1 bajt, to w tablicy jest to optymalizowane (1 bit)
    
    endz = (z+1)/3-1;
    if ((z%6)==1) ++endz;
    for (int x = 0; x != endz; ++x) primes[x] = true;

    for (int x = 0; x != endz; ++x)
    {
        if (primes[x])
            EliminateDuplicates(x);
        ++x;
        if (x == endz) break;
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
