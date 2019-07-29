#include <iostream>
#include <random>
#include <chrono>
#include <algorithm>
using namespace std; //I know, don't mention it...

int main()
{
	const int size = (int)pow(10, 8) << 2;
	int *bigarray = new int[size], *end = bigarray + size - 8;
	long long sum = 0;
	chrono::time_point<chrono::high_resolution_clock> start, stop;
	std::chrono::microseconds duration;
	//variables are declared

	fill(bigarray, end, rand() % 20);
	cout << "Filled the array" << endl;
	//array is filled

		start = chrono::high_resolution_clock::now();

		sum = 0;
	for (int i = 0; i != 10; ++i)
	for (int *index = bigarray; index < end; index += 2) //first algorithm
	{
		sum += *index;
		sum += *++index;
		sum += *++index;
	}

		cout << "sum equals " << sum << endl;
		stop = chrono::high_resolution_clock::now();
		duration = chrono::duration_cast<chrono::microseconds>(stop - start);
		cout << "Executing algorithm number 1 took: " << duration.count() << " ms" << endl;

		start = chrono::high_resolution_clock::now();

	sum = 0;
	for (int i = 0; i != 10; ++i)
	for (int *index = bigarray; index < end; index += 4) //second algorithm
	{
		sum += index[0];
		sum += index[1];
		sum += index[2];
	}

		cout << "sum equals " << sum << endl;
		stop = chrono::high_resolution_clock::now();
		duration = chrono::duration_cast<chrono::microseconds>(stop - start);
		cout << "Executing algorithm number 2 took: " << duration.count() << " ms" << endl;

		start = chrono::high_resolution_clock::now();

	sum = 0;
	for (int i = 0; i != 10; ++i)
	for (int *index = bigarray; index < end; index += 4) //third algorithm
	{
		sum += *index;
		sum += index[1];
		sum += index[2];
	}

		cout << "sum equals " << sum << endl;
		stop = chrono::high_resolution_clock::now();
		duration = chrono::duration_cast<chrono::microseconds>(stop - start);
		cout << "Executing algorithm number 3 took: " << duration.count() << " ms" << endl;

	system("pause");
	return 0;
}