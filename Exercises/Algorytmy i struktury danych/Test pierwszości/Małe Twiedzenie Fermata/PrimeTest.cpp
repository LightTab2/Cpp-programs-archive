#include <iostream>
#include <cmath>
#include <chrono>
#include <cstring>
#include <random>
using namespace std;

bool nolog = false, nopause = false, timer = false;

unsigned long long random (unsigned long long &&min, unsigned long long &max)
{
    unsigned long long res;
    for (int i = 0; i != 8; ++i) //generuje co 8 bitow dla 64 bitowej liczby
    {
        res <<= 8;
        res |= rand() % 256;
    }
    return min + (res % (max - min));
}

unsigned long long NWD (unsigned long long a, unsigned long long b)
{
    while (b)
    {
        a %= b;
        swap(a, b);
    }
    return a;
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
        "Sprawdz czy liczba naturalna p jest pierwsza.\n"
        "Rozwiazanie (bedzie troche matematyki - udowadniam Male Twierdzenie Fermata):\n"
        "Wybierzmy dwie liczby a i b, ktore w zalozeniu sa wzglednie pierwsze (w algorytmie b jest liczba badana) "
        "Rozpatrzmy ciag liczb:\n a, 2a, 3a, ..., (b-2)a, (b-1)a \noraz zastosujmy na nim arytmetyke modularna, "
        "mianowicie z kazdego elementu obliczymy jego modulo b i dla ulatwienia oznaczne jeszcze nowa zmienna:\n"
        "x = a mod b \n"
        "Na tym etapie mozna juz zauwazyc, ze x zawiera sie w przedziale <0;b). Teraz mozemy zapisac ciag wynikow "
        "modulo:\n"
        "x, 2x mod b, 3x mod b, ..., (b-2)x mod b, (b-1)x mod b\n"
        "Udowodnie, ze zadna z liczb w tym zbiorze nie jest rowna innej ze tego ciagu dla b bedacego liczba pierwsza:\n"
        "wyrazenie qx mod b, gdzie q to dowolna liczba naturalna w przedziale <0;b), mozemy przedstawic w postaci\n"
        "cx - db, gdzie c i d to pewne, nieznane liczby naturalne\n"
        "Tak samo (p jest rozne od q) px mod b = ex - fb, w takim razie rownanie\n"
        "qx mod b = px mod b (dwie dowolne liczby z ciagu wynikow) mozemy zapisac jako:\n"
        "cx - db = ex - fb      inaczej      (c-e)x = (d-f)b\n"
        "Zauwazmy, ze c jest rozne od d lub/i e jest rozne od f, inaczej p nie bylbo rozne od q; nie spelnialo "
        "zalozenia. Wyklucza to przypadek, gdy (c-e) i (d-f) sa oba rowne zero\n"
        "Wiemy, ze c, e, d, f zawieraja sie w przedziale <0;b), zatem (c - e) < b i (d - f) < b\n"
        "Skoro NWD(x, b) = 1, NWW(x, b) = x * b\n"
        "Zatem (c-e)x jest rowna liczbie (d-f)b tylko wtedy, gdy (d-f) jest rowne kx, co moze "
        "sie zdarzyc, i (c-e) jest rowne kb, co nie moze sie zdarzyc (k to dowolna liczba calkowita rozna od zero "
        "W takim razie skoro elementow ciagu wynikow (po obliczeniu modulo) jest b-1 i kazdy jest rozny (jezeli "
        "b to liczba pierwsza), zawierajacy sie w przedziale <0;b-1>, to ten ciag mozemy posortowac i zapisac"
        "w postaci 1,2,3,...b-3,b-2,b-1, stworzmy rownianie, ktore doprowadzi nas do Malego Twierdzenia Fermata:\n"
        "[a * 2a * 3a * ...* (b-2)a * (b-1)a] mod b = [1 * 2 * 3 * ... (b-2) * (b-1)] mod b <=>\n"
        "{[1 * 2 * 3 * ...* (b-2) * (b-1)]*a^(b-1)} mod b = [1 * 2 * 3 * ... (b-2) * (b-1)] mod b <=>\n"
        "a^(b-1) mod b = 1\n"
        "Zauwazmy, co sie stanie, gdy wyliczymy modulo z ciagu wynikow, gdy b nie jest liczba pierwsza."
        "Na przykladzie:\n"
        "Zalozmy, ze b = 6o i b > 8, w takim razie ciag wynikow wynosi: a mod 6o, a mod 3o, a mod 2o, 2a mod 3o,"
        "5a mod 6o, a mod o, 7a mod 6o, ..., (b-2)a mod 6o, (b-1)a mod 6o\n"
        "W takim ciagu jest duza szansa, ze elementy sie powtorza, szczegolnie latwo to sobie wyborazic, gdy o jest znacznie "
        "wieksze od a\n"
        "Gdy elementy powtarzaja sie, a^(b-1) mod b = 1 nie zachodzi w wiekszosc przypadkow, czyli negatywny wynik wyklucza "
        "pierwszenstwo liczby, ale pozytywny wynik nie daje gwarancji, ze liczba jest pierwsza (jedynie duzo prawdopodobienstwo)\n"
        "Czyli, jezeli znajdziemy b > a i NWD(a, b) = 1 i spelniony jest warunek powyzej, to b moze byc liczba pierwsza\n\n"
        "Implementacja:\n"
        "Bede sprawdzal czy dana liczba p spelnia Male Twierdzenie Fermata dla 10 losowych podstaw (liczb a w dowodzie) "
        "i potem wyklucze okolo 95% przypadkow, ze p jest liczba pseudopierwsza Carmicheala, sprawdzajac podzielnosc "
        "tej liczby przez wszystkie liczby pierwsze z przedzialu <2;1009>.\n\n";

    const unsigned long long lowprimes[] = {
      2,  3,  5,  7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67,
     71, 73, 79, 83, 89, 97,101,103,107,109,113,127,131,137,139,149,151,157,163,
    167,173,179,181,191,193,197,199,211,223,227,229,233,239,241,251,257,263,269,
    271,277,281,283,293,307,311,313,317,331,337,347,349,353,359,367,373,379,383,
    389,397,401,409,419,421,431,433,439,443,449,457,461,463,467,479,487,491,499,
    503,509,521,523,541,547,557,563,569,571,577,587,593,599,601,607,613,617,619,
    631,641,643,647,653,659,661,673,677,683,691,701,709,719,727,733,739,743,751,
    757,761,769,773,787,797,809,811,821,823,827,829,839,853,857,859,863,877,881,
    883,887,907,911,919,929,937,941,947,953,967,971,977,983,991,997,1009,1010}; //1010 jest pivotem
    if (!nolog) cout << "Podaj liczbe naturalna p:" << endl;
    cin >> p;
    unsigned long long psub = p - 1;
    bool prime = true;
    chrono::time_point<chrono::high_resolution_clock> start, stop;
    if (timer) start = chrono::high_resolution_clock::now();
    
    if (p > 3)
    for (int i = 0; i != 10 && prime; ++i)
    {
        unsigned long long ran = random(2, psub);
        if (NWD(p,ran) != 1 || ModuloPow(ran, psub, p) != 1) 
            prime = false;
    }

    if (prime) 
    {
        const unsigned long long *lp = lowprimes - 1;
        while (*++lp != 1010 && *lp < p) 
            if (!(p%*lp)) prime = false;
        if (prime) cout << "Liczba " << p << " raczej jest liczba pierwsza";
    }
    if (!prime) cout << "Liczba " << p << " nie jest liczba pierwsza";
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
