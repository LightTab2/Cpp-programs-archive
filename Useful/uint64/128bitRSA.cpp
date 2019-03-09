#include <random>
#include "uint64.h"
#include <thread>
// d*2^r = n-1 d must be odd
bool miillerTest(uint_fast64_t d, uint_fast64_t &n)
{
	const uint_fast64_t buf = n - 1;

	uint_fast64_t x;
	{
		uint_fast64_t a = 2 + rand() % 20;
		uint_fast64_t copy_d = d;
		uint_fast64_t result = 1;
		a %= n; //make sure a <= p
		while (copy_d)
		{
			if (copy_d & 1) {
				result *= a;
				result %= n;
			}

			copy_d >>= 1; //y = y/2
			a *= a;
			a %= n;
		}
		x = result;
	}

	if (x == 1 || x == buf)
		return true;

	//Keep squaring x until one of the following doesn't happen:
	//-d does not reach n-1
	//-(x^2) % n is not 1
	//-(x^2) % n is not n-1
	while (d != buf)
	{
		x *= x;
		x %= n;
		d *= 2;

		if (x == 1) return false;
		else if (x == buf) return true;
	}
	return false;
}

bool isPrime(uint_fast64_t &n)
{
	//if (n <= 1 || n == 4)  return false;
	//if (n <= 3) return true;

	// Find r such that n = 2^d * r + 1 for some r >= 1
	uint_fast64_t d = n - 1;
	while (d % 2 == 0)
		d /= 2;

	for (int i = 0; i < 5; i++)
		if (!miillerTest(d, n))
			return false;

	return true;
}

int main()
{
	std::random_device r;

	std::seed_seq seed2{ r(), r(), r()};
	std::mt19937 e2(seed2);

	uint_fast64_t firstprime = e2(), lastprime = e2();
	while (!isPrime(firstprime)) ++firstprime;
	while (!isPrime(lastprime)) ++lastprime;
    uint64 ree = 40;
    uint64 = ((-1)u);
	return 0;
}   
