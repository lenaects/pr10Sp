// pr10.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <Windows.h>
#include <conio.h> 
#include <cstdio> //для работы со строками
using namespace std;

volatile int co;

void thread()
{
    for (;;)
    {
        co++;
        Sleep(500);
        _cprintf("count = %d\n", co);
    }
}
void thread1() {
    const char* messages[] = { "Привет!", "Как дела?", "Что нового?", "Пока!" };
    int index = 0;

    for (;;) {
        co++;
        Sleep(500);
       
        // Выводим сообщение из массива
        cout << messages[index] << endl;
        index = (index + 1) % (sizeof(messages) / sizeof(messages[0]));
    }
}

DWORD WINAPI thread2(LPVOID lpParam) {
    cout << "Поток 1 создан.\n";

    cout << "Поток 1: Массив: " << endl;
        int mas[3][3];
        DWORD threadId = GetCurrentThreadId();
        srand(time(NULL) + threadId);
        for (int i = 0; i < 3; i++) {
            cout << "\n";
            for (int j = 0; j < 3; j++) {
                mas[i][j] = rand() % 10;
                cout << mas[i][j] << " ";
            }
        }
    return 0;
}

DWORD WINAPI thread3(LPVOID lpParam) {
    cout << "Поток 2 создан\n";

    int input;
    cout << "Поток 2: Введите число: ";
    cin >> input ;
    int reversed = 0;
    while (input != 0) {
        reversed = reversed * 10 + input % 10;
        input = input / 10;
    }

    // Выводим перевернутое значение
    cout << "\nПоток 2: Перевернутое значение: " << reversed << std::endl;
    return 0;
}

int main()
{
    setlocale(LC_ALL, "Russian");
    //
    //zd1-2
    //     
    cout << "задание 1 и 2" << endl;
    char lpszAppName[] = "C:\\Program Files\\Microsoft Office\\root\\Office16\\EXCEL.EXE";
    STARTUPINFO si;
    PROCESS_INFORMATION piCom;
    ZeroMemory(&si, sizeof(STARTUPINFO));
    si.cb = sizeof(STARTUPINFO);
    if (!CreateProcess(
        NULL, // имя не задаем
        lpszAppName, // имя программы
        NULL, // атрибуты защиты процесса устанавливаем по умолчанию
        NULL, // атрибуты защиты первичного потока по умолчанию
        FALSE, // дескрипторы текущего процесса не наследуются
        0, // по умолчанию NORMAL_PRIORITY_CLASS
        NULL, // используем среду окружения вызывающего процесса
        NULL, // текущий диск и каталог, как и в вызывающем процессе
        &si, // вид главного окна - по умолчанию
        &piCom // информация о новом процессе
    )
       )
    {
        cout << "The mew process is not created." << endl
            << "Check a name of the process." << endl;
        return 0;
    } 
    cout << "процесс создан и открывается excel.PID:" << piCom.dwProcessId << endl;
    cout << "дескриптор:" << piCom.hProcess << endl;
    Sleep(5000); // немного подождем и закончим свою работу
    // завершаем поток
    TerminateThread(piCom.hThread,0);
    TerminateThread(piCom.hProcess, 0);
    cout << "Процесс завершен!" << endl;
    // закроем дескрипторы запущенного процесса в текущем процессе
    CloseHandle(piCom.hThread);
    CloseHandle(piCom.hProcess);    
     //
    //zd3
    // 
    cout << "Задание 3" << endl;
    int number3 = 12345;
    char lpszComLine3[80]; // для командной строки 
    char stroka3[80];
    STARTUPINFO si3{};
    PROCESS_INFORMATION pi3;
    SECURITY_ATTRIBUTES sa3;
    HANDLE hThread3;
    DWORD IDThread3;
    _cputs("Press any key to start the count-thread.\n");
    _getch();
    //устанавливает атрибуты защиты потока 
    sa3.nLength = sizeof(SECURITY_ATTRIBUTES);
    sa3.lpSecurityDescriptor = NULL; // защита по умолчанию 
    sa3.bInheritHandle = TRUE; // дескриптор потока наследуемый 
    // запускаем поток-счетчик 
    hThread3 = CreateThread(&sa3, 0, (LPTHREAD_START_ROUTINE)thread, NULL, 0,
        &IDThread3);
    if (hThread3 == NULL)
        return GetLastError();
    //устанавливаем атрибуты нового процесса 
    ZeroMemory(&si3, sizeof(STARTUPINFO));
    si3.cb = sizeof(STARTUPINFO);
    //формируем командную строку 
    wsprintf(lpszComLine3, "pr10_2.exe %d %d %d", (int)hThread3, number3);
    //запускаем новый консольный процесс 
    if (!CreateProcess(
        NULL, // имя процесса 
        lpszComLine3, // адрес командной строки 
        NULL, // атрибуты защиты процесса по умолчанию 
        NULL, // атрибуты защиты первичного потока по умолчанию 
        TRUE, // наследуемые дескрипторы текущего процесса 
        // наследуются новым процессом 
        CREATE_NEW_CONSOLE, // новая консоль 
        NULL, // используем среду окружения процесса предка 
        NULL, // текущий диск и каталог, как и в процессе-предке 
        &si3, // вид главного окна - по умолчанию 
        &pi3 // здесь будут дескрипторы и идентификаторы 
        //нового процесса и его первичного потока 
    )        )
    {
        _cputs("The new process is not created.\n");
        _cputs("Press any key to finish.\n");
        _getch();
        return GetLastError();
    }
    // закрываем дескрипторы нового процесса 
    CloseHandle(pi3.hProcess);
    CloseHandle(pi3.hThread);
    // ждем закрытия потока-счетчика 
    WaitForSingleObject(hThread3, INFINITE);
    _cputs("Press any key to exit.\n");
    _getch();
    // закрываем дескриптор потока 
    CloseHandle(hThread3);
    // 
    // zd4
    // 
    cout << "Задание 4.Для завершение нажмите любую кнопку" << endl;
    STARTUPINFO si4;
    PROCESS_INFORMATION pi4;
    HANDLE hThread4, hInheritThread4;
    DWORD IDThread4;
    hThread4 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thread1, &pi4,
        0, &IDThread4);
    char c;
    if (!DuplicateHandle(
        GetCurrentProcess(), // дескриптор текущего процесса 
        hThread4, // исходный дескриптор потока 
        GetCurrentProcess(), // дескриптор текущего процесса 
        &hInheritThread4, // новый дескриптор потока 
        THREAD_TERMINATE, // только завершение потока 
        TRUE, // новый дескриптор наследуемый 
        0)) // не используем 
    {
        _cputs("The handle is not duplicated.\n");
        _cputs("Press any key to finish.\n");
        _getch();
        return GetLastError();
    }
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
    TerminateThread(hThread4, 0);
    CloseHandle(hThread4);
    cout << "Работа завершенна" << endl;
    //
    //zd5
    //
    cout << "Задание 5" << endl;
    int number5 = 12345;
    char lpszComLine5[80]; // для командной строки 
    //char stroka5[80];
    STARTUPINFO si5{};
    PROCESS_INFORMATION pi5;
    SECURITY_ATTRIBUTES sa5;
    HANDLE hThread5, hProcess_dop5;
    DWORD IDThread5;
    _cputs("Press any key to start the count-thread.\n");
    _getch();
    //устанавливает атрибуты защиты потока 
    sa5.nLength = sizeof(SECURITY_ATTRIBUTES);
    sa5.lpSecurityDescriptor = NULL; // защита по умолчанию 
    sa5.bInheritHandle = TRUE; // дескриптор потока наследуемый 
    // запускаем поток-счетчик 
    hThread5 = CreateThread(&sa5, 0, (LPTHREAD_START_ROUTINE)thread, NULL, 0,
        &IDThread5);
    if (hThread5 == NULL)
        return GetLastError();
    //устанавливаем атрибуты нового процесса 
    ZeroMemory(&si5, sizeof(STARTUPINFO));
    si5.cb = sizeof(STARTUPINFO);
    //формируем командную строку 
    wsprintf(lpszComLine5, "pr10_2.exe %d %d %d", (int)hThread5, number5);
    //запускаем новый консольный процесс 
    if (!CreateProcess(
        NULL, // имя процесса 
        lpszComLine5, // адрес командной строки 
        NULL, // атрибуты защиты процесса по умолчанию 
        NULL, // атрибуты защиты первичного потока по умолчанию 
        TRUE, // наследуемые дескрипторы текущего процесса 
        // наследуются новым процессом 
        CREATE_NEW_CONSOLE, // новая консоль 
        NULL, // используем среду окружения процесса предка 
        NULL, // текущий диск и каталог, как и в процессе-предке 
        &si5, // вид главного окна - по умолчанию 
        &pi5 // здесь будут дескрипторы и идентификаторы 
        //нового процесса и его первичного потока 
    )
        )
    {
        _cputs("The new process is not created.\n");
        _cputs("Press any key to finish.\n");
        _getch();
        return GetLastError();
    }
    hProcess_dop5 = GetCurrentProcess();
    // выводим псевдодескриптор на консоль 
    std::cout  << hProcess_dop5 << std::endl;
    wsprintf(lpszComLine5, "pr10_2.exe %d %d %d", (int)hProcess_dop5, number5);
    //запускаем новый консольный процесс 
    if (!CreateProcess(
        NULL, // имя процесса 
        lpszComLine5, // адрес командной строки 
        NULL, // атрибуты защиты процесса по умолчанию 
        NULL, // атрибуты защиты первичного потока по умолчанию 
        TRUE, // наследуемые дескрипторы текущего процесса 
        // наследуются новым процессом 
        CREATE_NEW_CONSOLE, // новая консоль 
        NULL, // используем среду окружения процесса предка 
        NULL, // текущий диск и каталог, как и в процессе-предке 
        &si5, // вид главного окна - по умолчанию 
        &pi5 // здесь будут дескрипторы и идентификаторы 
        //нового процесса и его первичного потока 
    )
        )
    {
        _cputs("The new process is not created.\n");
        _cputs("Press any key to finish.\n");
        _getch();
        return GetLastError();
    }
    // закрываем дескрипторы нового процесса 
    CloseHandle(pi5.hProcess);
    CloseHandle(pi5.hThread);
    // ждем закрытия потока-счетчика 
    WaitForSingleObject(hThread5, INFINITE);
    _cputs("Press any key to exit.\n");
    _getch();
    // закрываем дескриптор потока 
    CloseHandle(hThread5);
    //
    //zd6
    //
    cout << "Задание 6 и 7" << endl;
    HANDLE hThread1 = NULL;
    HANDLE hThread2 = NULL;
    char input;

    while (true) {
        if (hThread1 != NULL) {
            WaitForSingleObject(hThread1, INFINITE);
        }
        if (hThread2 != NULL) {
            WaitForSingleObject(hThread2, INFINITE);
        }

        std::cout << "\nВыберите действие:\n";
        std::cout << "1. Создать поток 1\n";
        std::cout << "2. Создать поток 2\n";
        std::cout << "3. Завершить поток 1\n";
        std::cout << "4. Завершить поток 2\n";
        std::cout << "t. Выйти из программы\n";
        std::cout << "Ваш выбор: ";
        std::cin >> input;

        switch (input) {
        case '1':
            if (hThread1 == NULL) {
                hThread1 = CreateThread(NULL, 0, thread2, NULL, 0, NULL);
                if (hThread1 == NULL) {
                    std::cerr << "Не удалось создать поток 1.\n";
                }
            }
            else {
                std::cerr << "Поток 1 уже создан.\n";
            }
            break;
        case '2':
            if (hThread2 == NULL) {
                hThread2 = CreateThread(NULL, 0, thread3, NULL, 0, NULL);
                if (hThread2 == NULL) {
                    std::cerr << "Не удалось создать поток 2.\n";
                }
            }
            else {
                std::cerr << "Поток 2 уже создан.\n";
            }
            break;
        case '3':
            if (hThread1 != NULL) {
                TerminateThread(hThread1, 0);
                CloseHandle(hThread1);
                hThread1 = NULL;
                std::cout << "Поток 1 завершен.\n";
            }
            else {
                std::cerr << "Поток 1 не был создан.\n";
            }
            break;
        case '4':
            if (hThread2 != NULL) {
                TerminateThread(hThread2, 0);
                CloseHandle(hThread2);
                hThread2 = NULL;
                std::cout << "Поток 2 завершен.\n";
            }
            else {
                std::cerr << "Поток 2 не был создан.\n";
            }
            break;
        case 't':
            std::cout << "Выход из программы.\n";
            if (hThread1 != NULL) {
                TerminateThread(hThread1, 0);
                CloseHandle(hThread1);
            }
            if (hThread2 != NULL) {
                TerminateThread(hThread2, 0);
                CloseHandle(hThread2);
            }
            return 0;
        default:
            std::cerr << "Неверный выбор. Попробуйте снова.\n";
            break;
        }
    }


    _cputs("Press any key to exit.\n");
    _getch();

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
