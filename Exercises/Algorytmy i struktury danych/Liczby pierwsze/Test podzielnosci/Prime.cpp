#include <iostream>
#include <cmath>
#include <chrono>
#include <cstring>
#include <list>
using namespace std;

bool nolog = false, nopause = false, timer = false;

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
    unsigned long long n, quantity = 2;
    list<unsigned long long> primes;
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

    if (!nolog) cout << "Podaj liczbe naturalna n:" << endl;
    cin >> n;
    cout << endl;
    
    if (!nolog) cout << n << " kolejnych liczb pierwszych to:" << endl;
    chrono::time_point<chrono::high_resolution_clock> start, stop;
    if (timer) start = chrono::high_resolution_clock::now();

    for (int x = 2; x != n && x != 4; ++x) cout << x << ' ';
    
    unsigned long long checked = 5;
    bool add_mode = false;
    if (quantity < n) while (quantity != n)
    {
        unsigned long long square_root = static_cast<unsigned long long>(sqrt(checked));
        auto it = primes.cbegin();
        while (*it <= square_root) //check if number is prime
        {
            if (it == primes.cend() || !(checked % *it)) break;
            ++it;
        }
        if (it == primes.cend() || *it > square_root) //it is prime
        {
            cout << checked << ' ';
            primes.push_back(checked);
            ++quantity;
        }
        checked += add_mode ? 4 : 2; //if checked is '6k - 1' add 2 and get '6k + 1'; if checked is '6k + 1' add 4 and get '6(k+1) - 1'
        add_mode = !add_mode;
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
