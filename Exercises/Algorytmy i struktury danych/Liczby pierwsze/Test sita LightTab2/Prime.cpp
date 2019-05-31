#include <fstream>

int main()
{
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);
    
    unsigned short *primes;
    unsigned long long z;
    bool onemore = false;
    std::cin >> z;
    ofstream output("p.txt");

    if (!(z%6)) onemore = true;
    for (int x = 2; x <= z && x != 4; ++x) output << x << ' ';
    z /= 6;
    ++z;
    z >>= 1;

    primes = new short[z]; //mimo, ze bool normalnie zajmuje 1 bajt, to w tablicy jest to optymalizowane (1 bit)

    for (unsigned short x = 0; x != z; ) 
        primes[x] = x;
    for (unsigned long long x = 0; x != z; ++x)
    {
        if (primes[x])
            EliminateDuplicates(x);
        ++x;
        if (x == z) break;
        if (!primes[x]) continue;
        EliminateDuplicates(x);
        x+=2;
        unsigned long long add, next[2];
        if (x & 1)
        {
            --x;
            add = x * 6ull + 2ull;
            next[0] = -x + add - 2ull;
            next[1] = x + add - 1ull;
        }
        else
        {
            add = x * 6 - 2;
            next[0] = -x + add - 1ull;
            next[1] = x + add - 2ull;
        }
        cout << (x >> 1) << ' ';

        for (;next[0] < z; next[0]+=add, next[1]+=add)
        {
            primes[next[0]] = false;
            if (next[1] < z) primes[next[1]] = false;
        }

    }

    if (timer) stop = chrono::high_resolution_clock::now();
    cout << endl;
    return 0;
}
