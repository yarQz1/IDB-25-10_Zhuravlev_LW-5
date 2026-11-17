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
        cout << "Цена: " << price << endl;
    }

    string getTitle() {
        return title;
    }
};

class book : public Publication {
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
    }

    void putdata() {
        Publication::putdata();
        cout << "Количество страниц: " << pages << endl;
    }
};

class type : public Publication {
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
    }

    void putdata() {
        Publication::putdata();
        cout << "Время записи: " << minutes << " мин" << endl;
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
