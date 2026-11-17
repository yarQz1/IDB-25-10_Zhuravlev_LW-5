#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

class Base {
protected:
    int id;

public:
    Base(int i) {
        id = i;
    }

    virtual ~Base() {
        cout << "  ~Base " << id << endl;
    }

    virtual void show() {
        cout << "Объект " << id << ": тип Base" << endl;
    }

    virtual Base* clone() {
        return new Base(*this);
    }
};

class Derived : public Base {
public:
    Derived(int i) : Base(i) {
    }

    virtual ~Derived() {
        cout << "  ~Derived " << id << endl;
    }

    void show() {
        cout << "Объект " << id << ": тип Derived" << endl;
    }

    Base* clone() {
        return new Derived(*this);
    }
};

void add(vector<Base*>& storage, Base* obj) {
    storage.push_back(obj);
}

int main() {
    srand(time(0));
    vector<Base*> storage;

    cout << "Создание объектов (удаляются оригиналы):" << endl;

    for (int i = 0; i < 8; i++) {
        Base* obj;
        if (rand() % 2 == 0) {
            obj = new Base(i);
        } else {
            obj = new Derived(i);
        }

        add(storage, obj->clone());
        delete obj;
    }

    cout << "Объекты из хранилища:" << endl;
    for (int i = 0; i < storage.size(); i++) {
        storage[i]->show(); 
    }

    cout << endl << "Освобождение ресурсов:" << endl;
    for (int i = 0; i < storage.size(); i++) {
        delete storage[i];
    }
    storage.clear();

    return 0;
}
