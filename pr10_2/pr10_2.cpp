// pr10_2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <Windows.h>
#include <conio.h> 
#include <string>
using namespace std;
int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "Rus");
	HANDLE hThread;
	char c;
	// преобразуем символьное представление дескриптора в число 
	hThread = (HANDLE)atoi(argv[1]);
	int num = atoi(argv[2]);
	std::cout << "Исходное значение: " << num << std::endl;
	int reversed = 0;
	while (num != 0) {
		reversed = reversed * 10 + num % 10;
		num = num / 10;
	}

	// Выводим перевернутое значение
	std::cout << "Перевернутое значение: " << reversed << std::endl;


	// ждем команды о завершении потока 
	while (true)
	{
		_cputs("Input 't'");
		c = _getch();
		if (c == 't')
		{
			_cputs("t\n");
			break;
		}

	}
	// завершаем поток 
	TerminateThread(hThread, 0);
	// закрываем дескриптор потока 
	CloseHandle(hThread);
	_cputs("Press any key to exit.\n");
	_getch();
    //// Чтение числа из pipe
    //// Чтение числа из стандартного ввода (STD_INPUT_HANDLE)
    //int num;
    //DWORD dwRead;
    //ReadFile(GetStdHandle(STD_INPUT_HANDLE), &num, sizeof(num), &dwRead, NULL);

    //// Переворот числа
    //int reversed = 0;
    //while (num != 0) {
    //    reversed = reversed * 10 + num % 10;
    //    num = num / 10;
    //}

    //// Отправка результата в стандартный вывод (STD_OUTPUT_HANDLE)
    //DWORD dwWritten;
    //WriteFile(GetStdHandle(STD_OUTPUT_HANDLE), &reversed, sizeof(reversed), &dwWritten, NULL);

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
