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
    unsigned long long p;
    if (!nolog) cout << "Tresc zadania, ktore ten program rozwiazuje to:\n"
        "Sprawdz czy liczba naturalna p jest pierwsza.\n"
        "Rozwiazanie:\n"
        "Sprawdzam czy p dzieli sie bez reszty przez kadydatow na liczby pierwsze (6k - 1 i 6k + 1) az do "
        "pierwiastka z p, jezeli nie - liczba jest pierwsza\n\n";

    if (!nolog) cout << "Podaj liczbe naturalna p:" << endl;
    cin >> p;
    if (!nolog) cout << endl;

    bool switchb = true;
    chrono::time_point<chrono::high_resolution_clock> start, stop;
    if (timer) start = chrono::high_resolution_clock::now();

    if (p < 4) cout << p << " jest liczba pierwsza";
    else 
    {
        unsigned long long current = 5, end = ceil(sqrt(p));
        if (!(p % 2)) current = 2;
        if (!(p % 3)) current = 3;

        for (; current < end;) 
        {
            if (!(p % current)) break;

            if (switchb) current += 2;
            else current += 4; 
            switchb = !switchb;
        }

        if (current > end) cout << p << " jest liczba pierwsza";
        else cout << p << " nie jest liczba pierwsza";
    }
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
