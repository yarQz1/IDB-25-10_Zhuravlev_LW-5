#include <iostream>
#include <string>
#include <limits>

enum BookType {
    FICTION = 0,
    TECHNICAL = 1
};

class Book {
private:
    std::string author;
    std::string title;
    BookType type;

public:
    Book(std::string book_author, std::string book_title, BookType book_type) {
        author = book_author;
        title = book_title;
        type = book_type;
    }

    bool isValid() {
        return !author.empty() && !title.empty();
    }

    BookType getType() {
        return type;
    }

    void print() {
        std::cout << author << " - \"" << title << "\" (";

        if (type == FICTION) {
            std::cout << "художественная";
        } else {
            std::cout << "техническая";
        }

        std::cout << ")" << std::endl;
    }
};

class Library {
private:
    static const int max_size = 100;
    Book* books[max_size];
    int size;

public:
    Library() {
        size = 0;
    }

    ~Library() {
        for (int i = 0; i < size; i++) {
            delete books[i];
        }
    }

    bool addBook(Book* book) {
        if (!book->isValid() || size >= max_size) {
            delete book;
            return false;
        }

        books[size] = book;
        size++;

        return true;
    }

    int getSize() {
        return size;
    }

    Book* getBook(int index) {
        return books[index];
    }

    void print() {
        for (int i = 0; i < size; i++) {
            std::cout << i + 1 << ". ";
            books[i]->print();
        }
    }
};

void countWithSwitch(Library& library) {
    int fiction_count = 0;
    int technical_count = 0;

    for (int i = 0; i < library.getSize(); i++) {
        switch (library.getBook(i)->getType()) {
            case FICTION:
                fiction_count++;
                break;

            case TECHNICAL:
                technical_count++;
                break;
        }
    }

    std::cout << "Художественных книг: " << fiction_count << std::endl;
    std::cout << "Технических книг: " << technical_count << std::endl;
}

int main() {
    Library library;

    int book_count;

    std::cout << "Введите количество книг в библиотеке: ";

    while (!(std::cin >> book_count) || book_count < 1 || book_count > 10000) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        std::cout << "Ошибка: введите корректное число: ";
    }

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    while (library.getSize() < book_count) {
        std::string author;
        std::string title;
        std::string type_input;

        std::cout << std::endl;
        std::cout << "Книга " << library.getSize() + 1 << std::endl;

        while (true) {
            std::cout << "Введите автора: ";
            std::getline(std::cin, author);

            if (!author.empty()) {
                break;
            }

            std::cout << "Ошибка: У книги должен быть автор. Попробуйте снова."
                      << std::endl;
        }

        while (true) {
            std::cout << "Введите название: ";
            std::getline(std::cin, title);

            if (!title.empty()) {
                break;
            }

            std::cout << "Ошибка: У книги должно быть название. Попробуйте снова."
                      << std::endl;
        }

        BookType type;

        while (true) {
            std::cout << "Выберите тип книги (1 - художественная, 2 - техническая): ";
            std::getline(std::cin, type_input);

            if (type_input == "1") {
                type = FICTION;
                break;
            } else if (type_input == "2") {
                type = TECHNICAL;
                break;
            } else {
                std::cout << "Ошибка: Есть только два типа книг. Введите 1 или 2." << std::endl;
            }
        }

        library.addBook(new Book(author, title, type));
    }

    std::cout << std::endl;
    std::cout << "Книги в библиотеке:" << std::endl;
    library.print();

    std::cout << std::endl;
    countWithSwitch(library);

    return 0;
}
