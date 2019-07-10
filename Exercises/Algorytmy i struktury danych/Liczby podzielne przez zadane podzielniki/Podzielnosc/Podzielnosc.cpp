#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <cstring>
using namespace std;
struct Interval
{
    long long min = ~(-1ull >> 1), max = -1ull >> 1;
};

const long long maximum = -1ull >> 1;
bool nolog = false, nopause = false, timer = false;

int main(int argc, char *args[])
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    for (int x = 0; x != argc; ++x)
    {
        if (!strcmp(args[x], "-nolog")) nolog = true;
        else if (!strcmp(args[x], "-nopause")) nopause = true;
        else if (!strcmp(args[x], "-time")) timer = true;
    }
    vector<long long> dzielniki;
	Interval interval;

    if (!nolog) cout << "Tresc zadania, ktore ten program rozwiazuje to:\n"
        "W przedziale <a;b> liczb calkowitych wyszukaj wszystkie liczby podzielne "
        "przez przynajmniej jedna z liczb z zadanego zbioru P\n\n";

    if (!nolog) cout << "Podaj przedzial liczb <a;b>:\nPodaj a:" << endl;
	cin >> interval.min;

    if (!nolog) cout << "Podaj b:" << endl;
    cin >> interval.max;
    while (interval.min > interval.max)
    {
        if (!nolog) cout << "\nPrzedzial nie moze sie konczyc mniejsza liczba niz sie zaczyna, sproboj ponownie:" << endl;
        cin >> interval.max;
    }

    long long temp;
    if (!nolog) cout << "Podawaj dzielniki (wpisz dowolny inny niz cyfra znak, by zakonczyc wpisywanie):" << endl;
    //Negative numbers need to become positive, because further calculating mins table would fail desperately
    while (cin >> temp) 
        dzielniki.push_back((temp < 0 ? -temp : temp));

    chrono::time_point<chrono::high_resolution_clock> start, stop;
    if (timer) start = chrono::high_resolution_clock::now();
    //We need to get maximum values lower than an integer multiply of the current divisor, they will be stored in mins array
    long long *mins = new long long[dzielniki.size()];
    for (int i = 0; i != dzielniki.size(); ++i)
    {
        mins[i] = (interval.min/dzielniki[i]) * dzielniki[i];
        if (mins[i] < interval.min) mins[i] += dzielniki[i];
    }
    long long min = maximum, minnext = maximum;
    if (!nolog) cout << "Liczby w przedziale <" << interval.min << ";" << interval.max << ">" << ", podzielne przez przynajmniej "
    "jeden z podanych dzielnikow to:" << endl;

    for (;;)
    {
        min = maximum;
        for (long long i = 0; i != dzielniki.size(); ++i)
        {
            if (mins[i] == minnext) mins[i] += dzielniki[i];
            if (mins[i] < min) min = mins[i];
        }
        if (min > interval.max) break;
        cout << min << " ";
        minnext = min;
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
