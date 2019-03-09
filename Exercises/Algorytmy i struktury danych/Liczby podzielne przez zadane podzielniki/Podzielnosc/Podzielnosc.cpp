#include <iostream>
#include <vector>
#include <algorithm>
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
        "W przedziale <a;b> liczb calkowitych wyszukaj wszystkie liczby podzielne "
        "przez jedna z liczb z zadanego zbioru P\n\n";

    if (!nolog) cout << "Podaj przedzial liczb <a;b>:\nPodaj a:\n";
	cin >> interval.min;

    if (!nolog) cout << "Podaj b:\n";
    cin >> interval.max;
    while (interval.min < interval.max)
    {
        if (!nolog) cout << "\nPrzedzial nie moze sie konczyc mniejsza liczba niz sie zaczyna, sproboj ponownie:\n";
        cin >> interval.max;
    }

    long long temp;
    if (!nolog) cout << "Podawaj dzielniki (wpisz dowolny inny niz cyfra znak, by zakonczyc wpisywanie):\n";
    //Negative numbers need to become positive, because further calculating mins table would fail desperately
    while (cin >> temp) 
        dzielniki.push_back((temp < 0 ? -temp : temp));

    //We need to get maximum values lower than an integer multiply of the current divisor, they will be stored in mins array
    long long *mins = new long long[dzielniki.size()];
    for (int i = 0; i != dzielniki.size(); ++i)
    {
        mins[i] = (interval.min/dzielniki[i]) * dzielniki[i];
        if (mins[i] < interval.min) mins[i] += dzielniki[i];
    }
    long long min = maximum, minnext = maximum;
    if (!nolog) cout << "Liczby w przedziale <" << interval.min << ";" << interval.max << ">" << ", podzielne przez przynajmniej "
    "jeden z podanych dzielnikow to:\n";

    do
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
    } while (true);
    cout << endl;
    //Press any key to exit the program
    if (!nopause) system("pause");
    return 0;
}
