#include <iostream>
#include <cmath>
#include <chrono>
#include <cstring>
using namespace std;

bool nolog = false, nopause = false, timer = false;
struct Interval
{
    long long min = ~(-1ull >> 1), max = -1ull >> 1;
};

bool coprime(unsigned long long a, unsigned long long b)
{
    int k = 0;
    if (!a) return false;
    if (!b) return false;

    for (; !((a | b) & 1); ++k)
    {
        a >>= 1;
        b >>= 1;
    }
    while (!(a & 1)) a >>= 1;
    while (!(b & 1)) b >>= 1;
    if (a < b) swap(a, b);
    while (b)
    {
        a -= b;
        a >>= 1;
        if (!a) { a = b; break; }
        while (!(a & 1)) a >>= 1;
        if (a < b) swap(a, b);
    }
    a <<= k;
    if (a == 1) return true;
    return false;
}

int main(int argc, char *args[])
{
    for (int x = 0; x != argc; ++x)
    {
        if (!strcmp(args[x],"-nolog")) nolog = true;
        else if (!strcmp(args[x], "-nopause")) nopause = true;
        else if (!strcmp(args[x], "-time")) timer = true;
    }
    Interval interval;
    unsigned long long p;
    if (!nolog) cout << "Tresc zadania, ktore ten program rozwiazuje to:\n"
        "W przedziale <a,b> liczb naturalnych wyszukaj wszystkie liczby wzglednie pierwsze z zadana liczba p.\n"
        "Rozwiazanie: wykorzystam algorytm z poprzedniego zadania i wypisze liczby z NWD rownym 1.\n\n";
        
    if (!nolog) cout << "Podaj liczbe naturalna p:\n";
    cin >> p;
    cout << endl;

    if (!nolog) cout << "Podaj przedzial <a;b>\nPodaj liczbe naturalna a:\n";
	cin >> interval.min;
    cout << endl;

    if (!nolog) cout << "Podaj liczbe naturalna b:\n";
	cin >> interval.max;
    while (interval.min > interval.max)
    {
        if (!nolog) cout << "\nPrzedzial nie moze sie konczyc mniejsza liczba niz sie zaczyna, sproboj ponownie:\n";
        cin >> interval.max;
    }

    //First writing to cout explains how respective algoritms work
    if (!nolog) cout << "Wszystkie liczby wzglednie pierwsze w przedziale <" << interval.min << ";" << interval.max << "> to: ";
    chrono::time_point<chrono::high_resolution_clock> start, stop;
    if (timer) start = chrono::high_resolution_clock::now();
        
    for (; interval.min != interval.max; ++interval.min) 
        if (coprime(interval.min, p)) cout << interval.min << " ";
    
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
