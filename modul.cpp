#include "Header.h"

//==================== Реализация методов класса Stack ====================

// Конструктор
Stack::Stack(int initialCapacity) {
    if (initialCapacity <= 0) {
        throw invalid_argument("Емкость стека должна быть положительным числом");
    }
    capacity = initialCapacity;
    data = new int[capacity];
    topIndex = -1;
}

// Деструктор
Stack::~Stack() {
    delete[] data;
    data = nullptr;
}

// Получение размера стека
int Stack::Size() const {
    return topIndex + 1;
}

// Добавление элемента
void Stack::Push(int value) {
    if (topIndex >= capacity - 1) {
        int newCapacity = capacity * 2;
        if (newCapacity <= capacity) {
            throw overflow_error("Достигнут максимальный размер стека");
        }
        int* newData = new int[newCapacity];
        for (int i = 0; i < capacity; ++i) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
        capacity = newCapacity;
    }
    data[++topIndex] = value;
}

// Удаление элемента
int Stack::Pop() {
    if (IsEmpty()) {
        throw underflow_error("Попытка извлечения из пустого стека");
    }
    return data[topIndex--];
}

// Получение верхнего элемента
int Stack::Top() const {
    if (IsEmpty()) {
        throw underflow_error("Попытка доступа к вершине пустого стека");
    }
    return data[topIndex];
}

// Проверка на пустоту
bool Stack::IsEmpty() const {
    return topIndex == -1;
}

//==================== Реализация методов класса Container ====================

// Инициализация
int Container::Initialize() {
    try {
        auto readInt = [](const string& prompt, int minVal, int maxVal) -> int {
            int value;
            cout << prompt;
            if (!(cin >> value)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                throw runtime_error("Ошибка ввода: требуется целое число");
            }
            if (cin.peek() != '\n') {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                throw runtime_error("Ошибка ввода: введите только число без дополнительных символов");
            }
            if (value < minVal || value > maxVal) {
                throw out_of_range("Ошибка: число вне допустимого диапазона");
            }
            return value;
            };

        N = readInt("Введите число N (1-500): ", 1, 500);
        return 0;
    }
    catch (const exception& e) {
        cerr << "Ошибка инициализации: " << e.what() << endl;
        return -1;
    }
}

// Обработка случая N=2
int Container::HandleN2() {
    try {
        bool ok = true, first = true;
        int tmp, i, j = 0;

        auto readInt = [](const string& prompt, int minVal, int maxVal) -> int {
            int value;
            cout << prompt;
            if (!(cin >> value)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                throw runtime_error("Ошибка ввода: требуется целое число");
            }
            if (cin.peek() != '\n') {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                throw runtime_error("Ошибка ввода: введите только число без дополнительных символов");
            }
            if (value < minVal || value > maxVal) {
                throw out_of_range("Ошибка: число вне допустимого диапазона");
            }
            return value;
            };

        k = readInt("Введите k для первого стека: ", 0, 1000);
        if (k > 0) {
            tmp = readInt("Введите значение элемента: ", 1, 2);
            i = 1;
            while (tmp == 1 && i < k) {
                tmp = readInt("Введите значение элемента: ", 1, 2);
                ++i;
            }
            j = tmp == 2;
            while (i < k) {
                tmp = readInt("Введите значение элемента: ", 1, 2);
                if (tmp == 1) ok = false;
                ++j; ++i;
            }
        }

        k = readInt("Введите k для второго стека: ", 0, 1000);
        if (k > 0) {
            tmp = readInt("Введите значение элемента: ", 1, 2);
            i = 1;
            while (tmp == 2 && i < k) {
                tmp = readInt("Введите значение элемента: ", 1, 2);
                ++i;
            }
            if (j && tmp == 1) ok = false;
            else if (tmp == 1) first = false;
            j += tmp == 1;
            while (i < k) {
                tmp = readInt("Введите значение элемента: ", 1, 2);
                if (tmp == 2) ok = false;
                ++j; ++i;
            }
        }

        if (ok) {
            if (first)
                for (i = 0; i < j; ++i)
                    cout << "1 2 (переносим элемент 2)" << endl;
            else
                for (i = 0; i < j; ++i)
                    cout << "2 1 (переносим элемент 1)" << endl;
        }
        else cout << 0;

        return ok ? 0 : -1;
    }
    catch (const exception& e) {
        cerr << "Ошибка обработки N=2: " << e.what() << endl;
        return -1;
    }
}

// Основная обработка
int Container::MainProcessing(Stack cont[]) {
    try {
        int tmp, i, j;

        auto readInt = [](const string& prompt, int minVal, int maxVal) -> int {
            int value;
            cout << prompt;
            if (!(cin >> value)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                throw runtime_error("Ошибка ввода: требуется целое число");
            }
            if (cin.peek() != '\n') {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                throw runtime_error("Ошибка ввода: введите только число без дополнительных символов");
            }
            if (value < minVal || value > maxVal) {
                throw out_of_range("Ошибка: число вне допустимого диапазона");
            }
            return value;
            };

        auto intToString = [](int num) -> string {
            if (num == 0) return "0";
            bool isNegative = num < 0;
            if (isNegative) num = -num;
            string result;
            while (num > 0) {
                result = static_cast<char>('0' + (num % 10)) + result;
                num /= 10;
            }
            return isNegative ? "-" + result : result;
            };

        for (i = 1; i <= N; ++i) {
            string prompt = "Введите количество элементов для стека ";
            prompt += intToString(i);
            prompt += ": ";
            k = readInt(prompt, 0, 1000);

            if (k > 0) {
                tmp = readInt("Введите значение элемента: ", 1, N);
                j = 1;
                while (tmp == i && j < k) {
                    tmp = readInt("Введите значение элемента: ", 1, N);
                    ++j;
                }
                if (tmp != i)
                    cont[i].Push(tmp);
                while (j < k) {
                    tmp = readInt("Введите значение элемента: ", 1, N);
                    cont[i].Push(tmp);
                    ++j;
                }
            }
        }
        return 0;
    }
    catch (const exception& e) {
        cerr << "Ошибка обработки данных: " << e.what() << endl;
        return -1;
    }
}

// Обработка временного стека
int Container::ProcessTempStack(Stack cont[]) {
    int tmp, i, save = 1, qsave = 0;
    for (i = 1; i < N; ++i) {
        while (!cont[i].IsEmpty()) {
            while (!cont[i].IsEmpty() && cont[cont[i].Top()].IsEmpty()) {
                int val = cont[i].Pop();
                cout << i << " " << val << " (переносим элемент " << val << " из стопки " << i << " в стопку " << val << ")" << endl;
            }
            while (!cont[i].IsEmpty() && !cont[cont[i].Top()].IsEmpty()) {
                int val = cont[i].Pop();
                cout << i << " " << N << " (переносим элемент " << val << " из стопки " << i << " в стопку " << N << ")" << endl;
                cont[N].Push(val);
            }
        }
        while (!cont[i].IsEmpty()) {
            int val = cont[i].Pop();
            cout << i << " " << N << " (переносим элемент " << val << " из стопки " << i << " в стопку " << N << ")" << endl;
            cont[N].Push(val);
        }
    }
    while (!cont[N].IsEmpty()) {
        tmp = cont[N].Pop();
        if (tmp == N) {
            cout << N << " " << save << " (переносим элемент " << tmp << " из стопки " << N << " в стопку " << save << ")" << endl;
            ++qsave;
        }
        else if (tmp == save) {
            save = 1 + save % 2;
            for (i = 0; i < qsave; ++i) {
                cout << tmp << " " << save << " (переносим элемент " << tmp << " из стопки " << tmp << " в стопку " << save << ")" << endl;
            }
            cout << N << " " << tmp << " (переносим элемент " << tmp << " из стопки " << N << " в стопку " << tmp << ")" << endl;
        }
        else {
            cout << N << " " << tmp << " (переносим элемент " << tmp << " из стопки " << N << " в стопку " << tmp << ")" << endl;
        }
    }
    for (i = 0; i < qsave; ++i) {
        cout << save << " " << N << " (переносим элемент " << save << " из стопки " << save << " в стопку " << N << ")" << endl;
    }
    return 0;
}

// Вывод результата
int Container::OutputResult(Stack cont[]) {
    try {
        int tmp, save = 1, qsave = 0;

        while (!cont[N].IsEmpty()) {
            tmp = cont[N].Top();
            cont[N].Pop();
            if (tmp == N) {
                cout << N << " " << save
                    << " (переносим элемент " << tmp
                    << " из стопки " << N
                    << " в стопку " << save << ")" << endl;
                ++qsave;
            }
            else if (tmp == save) {
                save = 1 + save % 2;
                for (int i = 0; i < qsave; ++i) {
                    cout << tmp << " " << save
                        << " (переносим элемент " << tmp
                        << " из стопки " << tmp
                        << " в стопку " << save << ")" << endl;
                }
                cout << N << " " << tmp
                    << " (переносим элемент " << tmp
                    << " из стопки " << N
                    << " в стопку " << tmp << ")" << endl;
            }
            else {
                cout << N << " " << tmp
                    << " (переносим элемент " << tmp
                    << " из стопки " << N
                    << " в стопку " << tmp << ")" << endl;
            }
        }

        for (int i = 0; i < qsave; ++i) {
            cout << save << " " << N
                << " (переносим элемент " << save
                << " из стопки " << save
                << " в стопку " << N << ")" << endl;
        }
        return 0;
    }
    catch (const exception& e) {
        cerr << "Ошибка вывода результата: " << e.what() << endl;
        return -1;
    }
}

// Проверка решения
bool Container::VerifySolution(Stack cont[]) {
    try {
        bool isValid = true;

        for (int i = 1; i <= N; ++i) {
            Stack temp;
            while (!cont[i].IsEmpty()) {
                int element = cont[i].Top();
                cont[i].Pop();
                temp.Push(element);

                if (element != i) {
                    isValid = false;
                    cerr << "Ошибка: в стеке " << i
                        << " найден элемент " << element << endl;
                }
            }

            while (!temp.IsEmpty()) {
                int element = temp.Top();
                temp.Pop();
                cont[i].Push(element);
            }
        }

        if (isValid) {
            cout << "Решение верно: все элементы находятся в своих стеках." << endl;
        }
        else {
            cout << "Ошибка: решение неверно. Имеются посторонние элементы в стеках." << endl;
        }

        return isValid;
    }
    catch (const exception& e) {
        cerr << "Ошибка проверки решения: " << e.what() << endl;
        return false;
    }
}

// Ручной ввод
int Container::ManualInput() {
    try {
        Stack cont[501];

        if (Initialize() != 0) return -1;

        if (N == 2) {
            return HandleN2();
        }

        if (MainProcessing(cont) != 0) return -1;

        if (ProcessTempStack(cont) != 0) return -1;

        if (!VerifySolution(cont)) {
            cerr << "Ошибка: решение не соответствует условиям задачи." << endl;
            return -1;
        }

        if (OutputResult(cont) != 0) return -1;

        return 0;
    }
    catch (const exception& e) {
        cerr << "Критическая ошибка в ManualInput: " << e.what() << endl;
        return -1;
    }
}

//Функцию для Дружелюбного интерфейса
void Container::Welcome() {
    try {
        if (!cout.good()) {
            throw runtime_error("Ошибка: выходной поток не готов");
        }

        cout << "=============================================\n"
            << "         Индивидуальное задание \n"
            << "     Программа управления контейнерами      \n"
            << "=============================================\n\n";

        cout << "На складе хранятся контейнеры с товарами N различных видов.\n"
            << "Все контейнеры составлены в N стопок. В каждой стопке могут находиться\n"
            << "контейнеры с товарами любых видов (стопка может быть изначально пустой).\n\n"

            << "Автопогрузчик может:\n"
            << "- взять верхний контейнер из любой стопки,\n"
            << "- и поставить его сверху в любую другую стопку.\n\n"

            << "Задача программы:\n"
            << "Расставить все контейнеры так, чтобы:\n"
            << "- контейнеры 1-го вида были в 1-й стопке,\n"
            << "- 2-го вида — во 2-й стопке, ..., N-го вида — в N-й стопке.\n\n";

        if (cout.fail()) {
            throw runtime_error("Ошибка вывода информации");
        }

        cout << "Формат входных данных:\n"
            << "- Число N <= 500 (типы товаров и стопок)\n"
            << "- Для каждой стопки: количество k_i и k_i чисел (виды товаров)\n\n"

            << "Формат выходных данных:\n"
            << "- Последовательность действий: откуда взять и куда положить\n"
            << "- 0 если решение невозможно\n"
            << "- Ничего если контейнеры уже на месте\n\n";

        cout << "Нажмите Enter чтобы продолжить...";
        cin.get();

        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            throw runtime_error("Ошибка чтения ввода");
        }

        cout << "\n";
    }
    catch (const exception& e) {
        cerr << "\nОшибка: " << e.what() << endl;
    }
    catch (...) {
        cerr << "\nНеизвестная ошибка при выводе приветствия" << endl;
    }
}

//Функция для реализации основного меню
int Container::Menu() {
    try {
        setlocale(LC_ALL, "RU");
        int choice;
        Welcome();

        do {
            cout << "\nМеню\n";
            cout << "1. Ввести входные данные вручную\n";
            cout << "2. Выход\n";
            cout << "Выберите действие: ";


            try {
                if (!(cin >> choice)) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    throw runtime_error("Ошибка ввода: требуется число");
                }
                
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                switch (choice) {
                case 1:
                    ManualInput();
                    break;
                case 2:
                    cout << "Выход из меню...." << endl;
                    return 0;
                default:
                    throw out_of_range("Неверный выбор пункта меню");
                }
            }
            catch (const exception& e) {
                cerr << "Ошибка: " << e.what() << ". Пожалуйста, попробуйте снова." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        } while (true);
    }
    catch (const exception& e) {
        cerr << "Критическая ошибка в Menu: " << e.what() << endl;
        return -1;
    }
}
