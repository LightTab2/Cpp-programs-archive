//Progam will output all even or odd numbers, that are within given interval <a;b>
#include <iostream>
#include <chrono>
#include <cstring>
using namespace std;

bool nolog = false, nopause = false, timer = false;
struct Interval
{
    long long min = ~(-1ull >> 1), max = -1ull >> 1;
};
enum even_parity
{
    even,
    odd
};

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
    bool parity;
	Interval interval;

    //Progam will output all even or odd numbers, that are within given interval <a;b>
    if (!nolog) cout << "Program wypisze wszystkie parzyste lub nieparzyste liczby znajdujace sie w podanym "
        "przedziale <a;b>\n\n";
    
    //Specify the even parity
    //e (or p) - even
    //o (or n) - odd
    char temp;
    if (!nolog) cout << "Podaj parzystosc:\n"
    "p (lub e) - parzyste\n"
    "n (lub o) - nieparzyste" << endl;
    cin >> temp;
    chose:switch (temp)
    {
        case 'p':
        case 'e':
        parity = even;
        break;
        case 'n':
        case 'o':
        parity = odd;
        break;
        default:
        if (!nolog) cout << "Podano nieprawidlowo parzystosc, wybierz jedna z opcji, wpisujac znak:\n"
        "p (lub e) - parzyste\n"
        "n (lub o) - nieparzyste" << endl;
        goto chose;
        break; //Just to perserve the structure
    }

    //Specify the interval <a;b>
    //Input a:
	if (!nolog) cout << "\nPodaj przedzial <a;b>:\n"
        "Podaj a:" << endl;
	cin >> interval.min;

    //Input b:
    if (!nolog) cout << "Podaj b:" << endl;
    cin >> interval.max;
    while (interval.min > interval.max)
    {
        if (!nolog) cout << "\nPrzedzial nie moze sie konczyc mniejsza liczba niz sie zaczyna, sproboj ponownie:" << endl;
        cin >> interval.max;
    }
    //Odd/Even numbers within interval <a;b> are:
	if (!nolog) cout << '\n' << (parity == even ? "Parzyste" : "Nieparzyste") << " liczby wystepujace w przedziale <" << 
        interval.min << ';' << to_string(interval.max) << ">:" << endl;
        //PL: Musimy sprawdzic parzystosc pierwszej liczby w przedziale jezeli jest to liczba nieparzysta.
        //Jezeli te liczbe mozna opisac jako 2c + 1, gdzie c jest calkowite to dodajemy 1 do liczby otrzymujac
        //2c + 2 = 2(c+1), co dzielone przez dwa daje c+1, calkowita liczbe, wiec 2c+2 jest parzysta
        //---------
        //EN: We need to check whether first number in the interval is odd. If the number can be described as
        //2c + 1, where c is an integer, we add 1 to this number resulting in 2c + 2 = 2(c+1), divided by
        //two gives c+1, an integer, therefore 2c+2 is even
    
    long long number = interval.min;
    chrono::time_point<chrono::high_resolution_clock> start, stop;
    if (timer) start = chrono::high_resolution_clock::now();
    if (parity == even)
	{
        if (number % 2) ++number;
	}
    //PL: Analogicznie do poprzedniego rozumowania, jezeli mozemy przedstawic liczbe jako 2c, to 2c+1 jest
    //nieparzysta, tak samo jezeli dodamy 2, parzystosc sie nie zmienia
    //--------
    //EN: Analogous to previous reasoning, if we're able to express the number as 2c, then 2c+1 is odd,
    //and again if we add 2, parity won't change
    else if (!(number % 2)) ++number; //parity == odd

    //PL: Dopoki nie wyjdziemy poza zakres naszego przedzialu, dodajemy do "number" dzielna,
    //Jest to 2, czyli [number+2] to kolejna liczba parzysta w tym przedziale
    //--------
    //EN: Until we're within interval boundaries, we add to "number" the divider, that will
    //It is 2, so [number+2] is a next number number in this interval
    while (number <= interval.max)
    {
        cout << number << " ";
        number += 2;
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
