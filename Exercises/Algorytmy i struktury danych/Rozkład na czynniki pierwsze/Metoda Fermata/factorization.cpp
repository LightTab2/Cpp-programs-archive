#include <iostream>
#include <cmath>
#include <chrono>
#include <cstring>
using namespace std;

bool nolog = false, nopause = false, timer = false;
bool first = true;

void rozklad(unsigned long long p)
{
    unsigned long long x = ceil(sqrt(p)), y = 0, dx = (x << 1) + 1, dy = 1, copyx = x+1;
    long long b = x*x - p;
    while ((x+y) <= p)
    {
        if (b > 0){
            ++y;
            b -= dy;
            dy += 2;
        }
        else if (b < 0)
        {
            b += dx;
            dx += 2;
            ++x;
        }
        else 
        {
            unsigned long long q1 = x - y, q2 = x + y;
            if (q1 == 1)
            {
                cout << (first ? "" : " * ") << q2;
                first = false;
            }
            else
            {
                rozklad(q1);
                rozklad(q2);
            }
            return;
        }
    }
    cout << (first ? "" : " * ") << p;
    first = false;
}

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
    unsigned long long p, n;
    const int lp[] = {
        2,  3,  5,  7,  11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67,
        71, 73, 79, 83, 89, 97, 101,103,107,109,113,127,131,137,139,149,151,157,163,
        167,173,179,181,191,193,197,199,211,223,227,229,233,239,241,251,257,263,269,
        271,277,281,283,293,307,311,313,317,331,337,347,349,353,359,367,373,379,383,
        389,397,401,409,419,421,431,433,439,443,449,457,461,463,467,479,487,491,499,
        503,509,521,523,541,547,557,563,569,571,577,587,593,599,601,607,613,617,619,
        631,641,643,647,653,659,661,673,677,683,691,701,709,719,727,733,739,743,751,
        757,761,769,773,787,797,809,811,821,823,827,829,839,853,857,859,863,877,881,
        883,887,907,911,919,929,937,941,947,953,967,971,977,983,991,997,1009 };

    if (!nolog) cout << "Tresc zadania, ktore ten program rozwiazuje to:\n"
        "Znajdz rozklad liczby p > 1 na iloczyn czynnikow pierwszych.\n"
        "Rozwiazanie:\n"
        "Naiwnie rozkladam liczbe az do czynnika 1009, w ramach optymalizacji\n"
        "Dopoki y + x <= p, sprawdzam czy y opisane rownaniem y*y = x*x - p, jest liczba calkowita, jezeli tak - rekurencyjnie "
        "rozkladam (x+y) i (x-y) w ten sam sposob, a gdy jest to niemozliwe - czynnik jest liczba pierwsza\n"
        "Stosuje trik przy sprawdzaniu czy y*y jest liczba pierwsza, mianowicie:\n"
        "Poczatkowe x to pierwiastek z badanej liczby (nie ma sensu rozpatrywac wiekszych liczb na tej samej "
        "zasadzie, jak nie ma sensu naiwnie sprawdzac czy jakas liczba jest pierwsza, sprawdzajac "
        "czy jest podzielna przez liczby powyzej jej pierwiastka, bo w procesie liczby zaczna sie powtarzac)\n"
        "Ustanawiam b, tak, by zawsze bylo rowne = x*x - y*y - p\n"
        "Jezeli b jest wieksze od 0, trzeba zmiejszyc x*x, jezeli mniejsze od 0 trzeba zwiekszyc y*y, "
        "Jezeli jest rowne 0, to y jest liczba calkowita\n"
        "Zmniejszanie o x*x i zwiekszanie y*y, gdy zmieniam x i y o jeden moge przeproawdzic tanio, zauwazajac ze:\n"
        "f(x) = x*x\n"
        "f(x+1) = x*x + 2x + 1\n"
        "f(x+1) = f(x) + 2x + 1\n"
        "f(x-1) = f(x) - 2x - 1\n\n";
    if (!nolog) cout << "Podaj liczbe naturalna p:" << endl;
    cin >> p;
    if (!nolog) cout << endl;

    if (!nolog) cout << "Rozklad na czynniki pierwsze liczby " << p << ":" << endl;
    chrono::time_point<chrono::high_resolution_clock> start, stop;
    if (timer) start = chrono::high_resolution_clock::now();

    if (p < 4)
    {
        cout << p;
        system("pause");
        return 0;
    }

    for (int x = 0; x != 169; ++x)
    {
        unsigned long long count = 0;
        while (!(p % lp[x]))
        {
            p /= lp[x];
            ++count;
        }
        if (count) { cout << (first ? "" : " * ") << lp[x]; first = false; }
        if (count > 1) cout << "^" << count; 
    }
    if (p != 1)
    rozklad(p);
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
