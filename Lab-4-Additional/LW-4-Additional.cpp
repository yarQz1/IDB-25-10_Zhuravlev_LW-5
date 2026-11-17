#include <iostream>
#include <string>
#include <stdexcept>
#ifdef _WIN32
#include <windows.h>
#endif
using namespace std;
 

 
class ProgramError {
protected:
    string message;
public:
    ProgramError(string m = "Ошибка в программе") {
        message = m;
    }
    virtual ~ProgramError() {}
 
    virtual string type() const {
        return "Ошибка в программе";
    }
    void print() const {
        cout << "[" << type() << "] " << message << endl;
    }
};
 
class MemoryAccessError : public ProgramError {
public:
    MemoryAccessError(string m = "Нет доступа к памяти") : ProgramError(m) {}
    string type() const {
        return "Ошибка доступа к памяти";
    }
};
 
class MathError : public ProgramError {
public:
    MathError(string m = "Математическая ошибка") : ProgramError(m) {}
    string type() const {
        return "Математическая ошибка";
    }
};
 
class DivisionByZeroError : public MathError {
public:
    DivisionByZeroError(string m = "Деление на ноль") : MathError(m) {}
    string type() const {
        return "Деление на ноль";
    }
};
 
class OverflowError : public MathError {
public:
    OverflowError(string m = "Переполнение") : MathError(m) {}
    string type() const {
        return "Переполнение";
    }
};

template <class T>
class PtrArray {
private:
    T** data;
    int count;
    int capacity;

    PtrArray(const PtrArray&) = delete;
    PtrArray& operator=(const PtrArray&) = delete;
 
public:
    PtrArray(int cap) {
        if (cap <= 0) {

            throw invalid_argument("размер массива должен быть положительным, получено: " + to_string(cap));
        }
        capacity = cap;
        count = 0;
        data = new T*[capacity];
    }
 
    ~PtrArray() {
        for (int i = 0; i < count; i++) {
            delete data[i];
        }
        delete[] data;
    }
 
    void add(T* obj) {
        if (obj == nullptr) {

            throw invalid_argument("нельзя добавить нулевой указатель");
        }
        if (count >= capacity) {
            delete obj;
            throw OverflowError("массив заполнен, размер: " + to_string(capacity));
        }
        data[count] = obj;
        count++;
    }
 
    int size() const {
        return count;
    }

    T& operator[](int index) {
        if (index < 0 || index >= count) {
            throw out_of_range("индекс " + to_string(index) + " вне диапазона [0, " + to_string(count) + ")");
        }
        return *data[index];
    }
};
 

 
int divide(int a, int b) {
    if (b == 0) {
        throw DivisionByZeroError("попытка делить " + to_string(a) + " на 0");
    }
    return a / b;
}
 
int addInts(int a, int b) {
    long long r = (long long)a + b;
    if (r > 2147483647LL || r < -2147483648LL) {
        throw OverflowError("сумма " + to_string(a) + " + " + to_string(b) + " не помещается в int");
    }
    return (int)r;
}
 
int readByPointer(int* p) {
    if (p == nullptr) {
        throw MemoryAccessError("обращение по нулевому указателю");
    }
    return *p;
}
 
void demo() {
    cout << "1. PtrArray<ProgramError>" << endl;
    PtrArray<ProgramError> errors(5);
    errors.add(new ProgramError("общая ошибка"));
    errors.add(new MemoryAccessError());
    errors.add(new MathError());
    errors.add(new DivisionByZeroError());
    errors.add(new OverflowError());
 
    for (int i = 0; i < errors.size(); i++) {
        errors[i].print();
    }
 

    cout << endl << "2. PtrArray<string>" << endl;
    PtrArray<string> words(3);
    words.add(new string("Привет"));
    words.add(new string("шаблонный"));
    words.add(new string("класс"));
    words[1] = "хороший";
    for (int i = 0; i < words.size(); i++) {
        cout << words[i] << " ";
    }
    cout << endl;
 

    cout << endl << "3. PtrArray<int>" << endl;
    PtrArray<int> numbers(3);
    numbers.add(new int(10));
    numbers.add(new int(20));
    numbers.add(new int(30));
    for (int i = 0; i < numbers.size(); i++) {
        cout << numbers[i] << " ";
    }
    cout << endl;
 

    cout << endl << "4. Исключения шаблонного класса" << endl;
 
    try {
        cout << errors[10].type() << endl;
    }
    catch (const out_of_range& e) {
        cout << "out_of_range: " << e.what() << endl;
    }
 
    try {
        cout << numbers[-1] << endl;
    }
    catch (const out_of_range& e) {
        cout << "out_of_range: " << e.what() << endl;
    }
 
    try {
        numbers.add(new int(40));
    }
    catch (const OverflowError& e) {
        e.print();
    }

    cout << endl << "5. invalid_argument" << endl;
 
    try {
        PtrArray<int> bad(-5);
    }
    catch (const invalid_argument& e) {
        cout << "invalid_argument: " << e.what() << endl;
    }
 
    try {
        words.add(nullptr);
    }
    catch (const invalid_argument& e) {
        cout << "invalid_argument: " << e.what() << endl;
    }
 

    cout << endl << "6. Иерархия ошибок в try/catch" << endl;
 
    try {
        cout << divide(10, 2) << endl;
        cout << divide(10, 0) << endl;
    }
    catch (const MathError& e) {
        e.print();
    }
 
    try {
        cout << addInts(2000000000, 2000000000) << endl;
    }
    catch (const ProgramError& e) {
        e.print();
    }
 
    try {
        readByPointer(nullptr);
    }
    catch (const MemoryAccessError& e) {
        e.print();
    }
 
    cout << endl << "Выход из demo(): массивы удаляют свои объекты" << endl;
}
 
int main() {
#ifdef _WIN32
    SetConsoleOutputCP(65001);
#endif
    demo();
    return 0;
}
 
