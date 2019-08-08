#include <iostream>
#include <cmath>
#include <chrono>
#include <cstring>
#include <random>
using namespace std;

bool nolog = false, nopause = false, timer = false;

unsigned long long random (unsigned long long &&min, unsigned long long &&max)
{
    unsigned long long res;
    for (int i = 0; i != 8; ++i) //generuje co 8 bitow dla 64 bitowej liczby
    {
        res <<= 8;
        res |= rand() % 256;
    }
    return min + (res % (max - min));
}

unsigned long long ModuloMulti (unsigned long long a, unsigned long long b, unsigned long long mod) //upewnia sie, ze nie wyjdziemy poza zakres zmiennych
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

//base^exponent % mod
unsigned long long ModuloPow(unsigned long long base, unsigned long long exponent, unsigned long long mod)
{
    unsigned long long res = 1;
    for (;;)
    {
        if (exponent & 1) res = ModuloMulti(res, base, mod);
        if (!(exponent >>= 1)) break;
        base = ModuloMulti(base, base, mod);
    }
    return res;
}
int main(int argc, char *args[])
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    srand(time(0));
    for (int x = 0; x != argc; ++x)
    {
        if (!strcmp(args[x],"-nolog")) nolog = true;
        else if (!strcmp(args[x], "-nopause")) nopause = true;
        else if (!strcmp(args[x], "-time")) timer = true;
    }
    unsigned long long p;
    if (!nolog) cout << "Tresc zadania, ktore ten program rozwiazuje to:\n"
        "Sprawdz czy liczba naturalna p jest liczba pierwsza.\n"
        "Rozwiazanie:\n"
        "Z Malego Twierdzenia Fermata wiemy, ze a^(n-1) mod p = 1\n"
        "Czyli po przeksztalceniu a^(n-1) mod p - 1 = 0\n"
        "Jezeli n > 2, to n jest liczba nieparzysta, czyli n-1 jest liczba parzysta, czyli moge ja zapisac jako "
        "2^s * d, gdzie s to jakas liczba > 0, a d jest nieparzysta\n"
        "a^(2^s * d) - 1 moge z wzoru skrocnego mnozenia zapisac jako (a^(2^[s-1] * d) - 1)(a^(2^[s-1] * d) + 1)\n"
        "Moge dalej rekurencyjnie rozkladac to az do postaci (a^d - 1)*(a^(2d)+1)*(a^(4d)+1)*...*(a^(2^[s-2]*d)+1)*(a^(2^[s-2]*d)+1)\n"
        "Czyli, gdy a^d nie rowna sie 1 i a^(2^k * d) nie rowna sie -1 dla kadego k w przedziale <1;s-1>, to wiemy, ze n nie "
        "jest liczba pierwsza, w przeciwnym wypadku mamy w najgorszym wypadku 1/4 na pomylke, dlatego wykonam "
        "ten test, zwany testem Millera-Rabina 20 razy, minimalizujac te szanse do (1/4)^20, o ile a sie nie powtorzy.\n\n";

    if (!nolog) cout << "Podaj liczbe naturalna p:" << endl;
    cin >> p;
    unsigned long long psub = p - 1;
    bool prime = false;
    chrono::time_point<chrono::high_resolution_clock> start, stop;
    if (timer) start = chrono::high_resolution_clock::now();

    if (p < 4) prime = true;
    else
    {
        int s = 0;
        while (!(psub | 0))
        {
            psub >>= 1;
            ++s;
        }

        for (int i = 0; i != 20; ++i)
        {
            unsigned long long ran = random(2, p-2), res = ModuloPow(ran, psub, p);
            if (res == 1) 
                prime = true;
            for (int x = 0; x != s; ++x)
                if ((res = ModuloMulti(res, res, p)) == psub) prime = true; 
        }
    }
    if (prime) cout << "Liczba " << p << " raczej jest liczba pierwsza";
    else cout << "Liczba " << p << " nie jest liczba pierwsza";
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
