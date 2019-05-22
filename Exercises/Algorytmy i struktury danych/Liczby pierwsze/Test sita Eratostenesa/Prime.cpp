#include <iostream>
#include <cmath>
#include <chrono>
#include <cstring>
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
    if (!nolog) cout << "Tresc zadania, ktore ten program rozwiazuje to:\n"
        "Znajdz wszystkie liczby w przedziale <1;n>.\n"
        "Rozwiazanie:\n"
        "Tworze i wypisuje sito Eratostenesa, czyli strukture zawierajaca wylacznie liczby pierwsze w taki sposob:\n\n"
        "Sito na pocztku ma 3 elementy: 1, 2,3. Liczbami pierwszymi moga byc tylko liczby"
        "niepodzielne przez 2 i 3, czyli musza byc w postaci 3(2n) - 1 lub 3(2n + 1) + 1 dla dowolnej liczby"
        "naturalnej n.\n Struktura posiada wszystkie takie elementy o wartosci mniejszych od podanego zakresu.\n"
        "Nastepnie wyznacze nastepna liczbe w sicie (zaczynam od 5) i usune z sita wszystkie jej wielokrotnosci\n\n"; 

    if (!nolog) cout << "Podaj liczbe naturalna n:\n";
    cin >> n;
    bool *primes = new bool[n];
    cout << endl;
    
    if (!nolog) cout << "Wszystkie liczby pierwsza mniejsze od " << n << " to :\n";
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
