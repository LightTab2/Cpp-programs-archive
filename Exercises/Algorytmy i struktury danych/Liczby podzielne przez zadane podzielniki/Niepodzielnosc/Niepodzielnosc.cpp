#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;
struct Interval
{
    long long min = ~(-1ull >> 1), max = -1ull >> 1;
};

const long long maximum = -1ull >> 1;
bool nolog = false, nopause = false;
int main(int argc, char *args[])
{
    for (int x = 0; x != argc; ++x)
    {
        if (args[x] == "-nolog") nolog = true;
        else if (args[x] == "-nopause") nopause = true;
    }
    vector<long long> dzielniki;
	Interval interval;

    if (!nolog) cout << "Tresc zadania, ktore ten program rozwiazuje to:\n"
        "W przedziale <a;b> liczb calkowitych wyszukaj wszystkie liczby niepodzielne "
        "przez ktorakolwiek z liczb z zadanego zbioru P\n\n";

    if (!nolog) cout << "Podaj przedzial liczb <a;b>:\nPodaj a:\n";
	cin >> interval.min;

    if (!nolog) cout << "Podaj b:\n";
    cin >> interval.max;
    while (interval.min < interval.max)
    {
        if (!nolog) cout << "\nPrzedzial nie moze sie konczyc mniejsza liczba niz sie zaczyna, sproboj ponownie:\n";
        cin >> interval.max;
    }

    long long buffer;
    if (!nolog) cout << "Podawaj dzielniki (wpisz dowolny inny niz cyfra znak, by zakonczyc wpisywanie):\n";
    while (cin >> buffer) 
        dzielniki.push_back(buffer);
    sort(dzielniki.begin(), dzielniki.end());
    for (int i = 0; i != dzielniki.size(); ++i)
    {
        int x = 0;
        for (long long e = ceil(sqrt(dzielniki[i])); x != i; ++x)
        {
            if (dzielniki[i] > e) break;
            if (!(dzielniki[i] % dzielniki[x]))
            {
                dzielniki.erase(dzielniki.begin() + i);
                --i;
                break;
            }
        }
    }
    for (buffer = interval.min; buffer != interval.max; ++buffer) 
    {
        long long i = 0;
        for (; i != dzielniki.size(); ++i)
            if (!(buffer % dzielniki[i])) break;
        if (i == dzielniki.size()) cout << buffer << " ";
    }
    cout << endl;
    //Press any key to exit the program
    if (!nopause) system("pause");
    return 0;
}
