#include <iostream>

using namespace std;

// Класс для реализации стека
class Stack {
private:
    int* data;        // Массив для хранения элементов
    int capacity;     // Текущая вместимость стека
    int topIndex;     // Индекс верхнего элемента

public:
    // Конструктор и деструктор
    Stack(int initialCapacity = 10);
    ~Stack();

    // Основные операции со стеком
    void Push(int value);     // Добавление элемента
    int Pop();              // Удаление элемента и возврат значения
    int Top() const;         // Получение верхнего элемента
    bool IsEmpty() const;    // Проверка на пустоту
    int Size() const;        // Получение размера стека
};

// Класс для работы с контейнерами
class Container {
private:
    int N;  // Количество стеков
    int k;  // Вспомогательная переменная

public:
    // Основные методы
    int Menu();              // Меню программы
    int ManualInput();       // Ручной ввод данных
    void Welcome();          // Приветствие

    // Методы обработки данных
    int ProcessTempStack(Stack cont[]);    // Обработка временного стека
    int OutputResult(Stack cont[]);        // Вывод результата
    int MainProcessing(Stack cont[]);      // Основная обработка
    int HandleN2();                        // Обработка случая N=2
    int Initialize();                      // Инициализация
    bool VerifySolution(Stack cont[]);     // Проверка решения
};

