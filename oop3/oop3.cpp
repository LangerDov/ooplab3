// oop3.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include "list.h"

#include <windows.h>


double PCFreq = 0.0;
__int64 CounterStart = 0;

void StartCounter()
{
	LARGE_INTEGER li;
	if (!QueryPerformanceFrequency(&li))
		std::cout << "QueryPerformanceFrequency failed!\n";

	PCFreq = double(li.QuadPart) / 1000.0;

	QueryPerformanceCounter(&li);
	CounterStart = li.QuadPart;
}
double GetCounter()
{
	LARGE_INTEGER li;
	QueryPerformanceCounter(&li);
	return double(li.QuadPart - CounterStart) / PCFreq;
}

int main()
{
    List<int> lst;
	time_t tm = std::time(NULL);
	for (size_t i = 0; i < 10000000; i++)
	{
		lst.Add(rand());
	}
	std::cout << "add on 10.000.000 iterations. Time:" << std::time(NULL) - tm << "\n";
	std::cout << "size in memory: " << lst.Bytes() << " bytes\n";
	double add = 0;
	size_t add_count = 0;
	double index = 0;
	size_t index_count = 0;
	double remove = 0;
	size_t remove_count = 0;

	for (size_t i = 0; i < 10000; i++)
	{
		if (rand() > 10000)
		{
			StartCounter();
			lst.Add(rand()%10000000);
			double res = GetCounter();
			add += res;
			add_count++;
			std::cout << "add time: " << res << " millisecond\n";
		}
		else if (rand() > 10000)
		{
			StartCounter();
			try
			{
				std::cout << "get value by index: value " << lst[rand() % 10000000] << "\n";
			}
			catch (const std::exception&)
			{

			}
			double res = GetCounter();
			index += res;
			index_count++;
			std::cout << "get value by index time: " << res << " millisecond\n";
		}
		else
		{
			StartCounter(); 
			lst.Remove(rand() % 10000000);
			double res = GetCounter();
			remove += res;
			remove_count++;
			std::cout << "remove time: " << GetCounter() << " millisecond\n";
		}
	}

    std::cout << "add time ~" << add/add_count << "millisec \n";
	std::cout << "index time ~" << index / index_count << "millisec \n";
	std::cout << "remove time ~" << remove / remove_count << "millisec \n";

}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
