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
        "Znajdz n kolejnych liczb pierwszych.\n"
        "Rozwiazanie: Pierw wyelminuje wszystkie liczby podzielne przez 2 i 3 (nieliczac ich), czyli:\n"
        "6, 8, 9, 10, 12, 14...\n"
        "Na ogol: 6k - 3, 6k - 2, 6k, 6k + 2, 6k + 3\n"
        "W takim razie zostaja do rozpatrzenia tylko: 6k - 1, 6k + 1\n"
        "Bede przechowywal w zbiorniku 'primes' sprawdzone liczby pierwsze w celu sprawdzania podzielnosci "
        "kolejnych liczb w nastepujacy sposob:\n"
        "Jezeli sprawdzana liczba p jest podzielna przez jakakolwiek z liczb z przedzialu <2;sqrt(p)>, znajdujaca "
        "sie w zbiorniku 'primes', to liczba nie jest pierwsza. W przeciwnym wypadku sprawdzna liczba jest liczba "
        "pierwsza\n\n";

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