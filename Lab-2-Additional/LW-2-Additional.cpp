#include <iostream>
#include <string>
using namespace std;

class Publication {
protected:
    string title;
    float price;

public:
    void getdata() {
        cout << "Введите название: ";
        getline(cin, title);

        while (title.empty()) {
            cout << "Ошибка! Название не может быть пустым." << endl;
            cout << "Введите название: ";
            getline(cin, title);
        }

        inputPrice();
    }

    void inputPrice() {
        cout << "Введите цену: ";
        cin >> price;

        while (cin.fail() || price < 0) {
            cin.clear();
            cin.ignore(1000, '\n');

            cout << "Ошибка! Введите неотрицательное число: ";
            cin >> price;
        }

        cin.ignore(1000, '\n');
    }

    void putdata() {
        cout << "Название: " << title << endl;
        cout << "Цена: " << price << " руб." << endl; // <--- Добавлен руб.
    }

    string getTitle() {
        return title;
    }
};

class sales {
private:
    float month_sales[3];

public:
    void getdata() {
        cout << "Введите стоимость продаж за последние три месяца:"
             << endl;

        for (int i = 0; i < 3; i++) {
            cout << "Месяц " << i + 1 << ": ";
            cin >> month_sales[i]; // <--- ИСПРАВЛЕНО: было [I], стало [i]

            while (cin.fail() || month_sales[i] < 0) {
                cin.clear();
                cin.ignore(1000, '\n');

                cout << "Ошибка! Введите неотрицательное число: ";
                cin >> month_sales[i]; // <--- ИСПРАВЛЕНО: было [I], стало [i]
            }
        }

        cin.ignore(1000, '\n');
    }

    void putdata() {
        cout << "Продажи за последние три месяца:" << endl;

        for (int i = 0; i < 3; i++) {
            cout << "Месяц " << i + 1 << ": "
                 << month_sales[i] << " руб." << endl; // <--- Добавлен руб.
        }
    }
};

class book : public Publication, public sales {
private:
    int pages;

public:
    void getdata() {
        Publication::getdata();

        cout << "Введите количество страниц: ";
        cin >> pages;

        while (cin.fail() || pages <= 0) {
            cin.clear();
            cin.ignore(1000, '\n');

            cout << "Ошибка! Введите положительное целое число: ";
            cin >> pages;
        }

        cin.ignore(1000, '\n');

        sales::getdata();
    }

    void putdata() {
        Publication::putdata();

        cout << "Количество страниц: " << pages << endl;

        sales::putdata();
    }
};

class type : public Publication, public sales {
private:
    int minutes;

public:
    type(string book_title) {
        title = book_title;
        price = 0;
        minutes = 0;
    }

    void getdata() {
        inputPrice();

        cout << "Введите время записи в минутах: ";
        cin >> minutes;

        while (cin.fail() || minutes <= 0) {
            cin.clear();
            cin.ignore(1000, '\n');

            cout << "Ошибка! Введите положительное целое число: ";
            cin >> minutes;
        }

        cin.ignore(1000, '\n');

        sales::getdata();
    }

    void putdata() {
        Publication::putdata();

        cout << "Время записи: " << minutes << " мин" << endl;

        sales::putdata();
    }
};

int main() {
    book printed_book;

    cout << "Ввод данных о книге" << endl;
    printed_book.getdata();

    type audio_book(printed_book.getTitle());

    cout << endl;
    cout << "Ввод данных об аудиозаписи книги" << endl;
    audio_book.getdata();

    cout << endl;
    cout << "Данные о книге" << endl;
    printed_book.putdata();

    cout << endl;
    cout << "Данные об аудиозаписи" << endl;
    audio_book.putdata();

    return 0;
}
