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
        "Tworze i wypisuje sito Atkina-Bersteina, ktorego dzialanie nie rozumiem.\n"
        "https://cr.yp.to/papers/primesieves.pdf tutaj znalazlem dowod matematyczny, co mi wcale nie pomoglo "
        "jezeli jestes w stanie to rozczytac to nie wiem co tutaj robisz. Moze jak ogarne liczby zespolone "
        "i teorie pierscieni to wroce napisac dowod";

    if (!nolog) cout << "Podaj liczbe naturalna n:" << endl;
    cin >> n;
    ++n;
    if (!nolog) cout << endl;

    if (!nolog) cout << "Wszystkie liczby pierwsze mniejsze od lub rowne " << n-1 << " to :" << endl;
    chrono::time_point<chrono::high_resolution_clock> start, stop;
    if (timer) start = chrono::high_resolution_clock::now();
    primes = new bool[n];

    if (timer) stop = chrono::high_resolution_clock::now();
    
    for (unsigned long long i = 5; i != n; ++i) primes[false] = true;
    
    unsigned long long sq = sqrt(n-1) + 1;
    //na podstawie tego chorego dowodu
    for (unsigned long long x = 1; x != sq; ++x)
    {
        unsigned long long xx = x * x;
        for (unsigned long long y = 1; y != sq; ++y)
        {
            unsigned long long yy = y * y,
            z = (xx << 2) + yy,
            zmod = z % 12;
            if (z < n && (zmod == 1 || zmod == 5)) primes[z] = !primes[z];

            z -= xx;
            if (z < n && z % 12 == 7) primes[z] = !primes[z];

            if (x > y)
            {
                z -= yy << 1;
                if (z <= n && z % 12 == 11) primes[z] = !primes[z];
            } 
        }
    }
    //wykluczamy liczby, ktore nie sa bezkwadratowe
    for (unsigned long long i = 5; i != sq; ++i)
        if (primes[i])
        {
            unsigned long long xx = i * i,
            z = xx;
            while (z <= n)
            {
                primes[z] = false;
                z += xx;
            }
        }
    cout << 1 << ' ' << 2 << ' ' << 3 << ' ';
    for (unsigned long long i = 5; i != n; ++i) if(primes[i]) cout << i << ' ';
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
