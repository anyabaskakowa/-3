//статический сверхну
#include <iostream>
#include <omp.h>
#include <time.h>
#include <iomanip>
#include <math.h>
#include <stdio.h>
using namespace std;

void First() {

	omp_set_num_threads(5);
#pragma omp parallel
	cout << "Hello World\n" << endl;

}

void Second(int number) {

	int n = number;
	int array[5] = { 1, 2, 4, 16, 32 };
	int static_array[5], dynamic_array[5];
	int num_threads = 1;

	for (int i = 0; i < 5; i++)
	{
		int time = clock();
		int k = 0;
		omp_set_num_threads(num_threads);

#pragma omp parallel
		{
			int counter = 0;
#pragma omp for schedule (static)
			for (int i = 2; i < n + 1; i++)
				for (int j = 2; j * j < i; j++)
					if (i % j == 0) {
						counter++; break;
					}
#pragma omp critical
			{
				k = k + counter; 
			}
		}
		k = n - k - 1;
		num_threads = array[i + 1];
		int endtime = clock();
		static_array[i] = endtime - time;

	}

	num_threads = 1;
	for (int i = 0; i < 5; i++)
	{

		int time = clock();
		int k = 0;
		omp_set_num_threads(num_threads);

#pragma omp parallel
		{
			int counter = 0;
#pragma omp for schedule (dynamic)
			for (int i = 2; i < n + 1; i++)
				for (int j = 2; j * j < i; j++)
					if (i % j == 0) {
						counter++; break;
					}
			///
#pragma omp critical
			{
				k += counter;
			}
		}
		k = n - k - 1;
		num_threads = array[i + 1];
		int endtime = clock();
		int search_time = endtime - time;
		dynamic_array[i] = search_time;
	}
	for (int i = 0; i < 5; i++)
		cout << setw(10) << array[i] << " ";
	cout << endl;
	for (int i = 0; i < 5; i++)
		cout << setw(10) << static_array[i] << " ";
	cout << endl;
	for (int i = 0; i < 5; i++)
		cout << setw(10) << dynamic_array[i] << " ";
	cout << endl;
}


void Third() {
	int N, M, num_threads_all;
	bool flag = false;

	cout << "Введите количество элементов в массиве: " << endl;
	cin >> N;
	int* mass = new int[N];
	for (int i = 0; i < N; i++)
	{
		mass[i] = i;
	}

	cout << "Введите искомое число M: " << endl;
	cin >> M;
	cout << "Введите число потоков: " << endl;
	cin >> num_threads_all;
	int num_threads1 = num_threads_all;
	int index;

	int* k = new int[num_threads1];
	for (int i = 0; i < num_threads1; i++)
	{
		k[i] = 0;
	}
	omp_set_num_threads(num_threads_all);

#pragma omp parallel
	{
		int num_threads_current;
		int num_threads_all = -1;
		num_threads_current = omp_get_thread_num();
#pragma omp barrier
#pragma omp for schedule(static)
		for (int i = 0; i < N; i++)
		{
			if (mass[i] == M) {
				index = i;
				k[num_threads_current] += 1;
				flag = true;
				break;
			}
			else
				k[num_threads_current] += 1;
			if (flag == true)
				break;
		}
	}

	for (int i = 0; i < num_threads1; i++)
		cout << k[i] << " ";
	cout << endl;
	if (index == -1) cout << "Error" << endl;
	else {
		index++;
		cout << index;
	}
}
int main()
{

	setlocale(LC_ALL, "Russian");
	int num = -1;
	while (num != 0)
	{
		cout << " Задание №: " << endl;
		cout << "1)Вывести на экран <<Hello World>>" << endl;
		cout << "2)Сосчитать количество простых чисел от 2 до N" << endl;
		cout << "3)Найти магическое число" << endl;
		cin >> num;

		if (num == 1) {
			First();
		}

		if (num == 2) { cout << "Для N = 1 000 000" << endl; Second(1000000); cout << "Для N = 10 000 000" << endl; Second(10000000); }
		if (num == 3) {
			Third();
		}
		cout << endl;
	}
	return 0;
}