#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Detail {
protected:
    string name;
    float weight;
    
    Detail(string n, float w) {
        name = n;
        weight = w;
    }
    
    template <class T>
    friend void addToStore(vector<Detail*>& store, string n, float w);

public:
    virtual ~Detail() {
        cout << "Удалено: " << name << endl;
    }

    virtual void print() {
        cout << "Деталь: " << name << ", масса: " << weight << " кг" << endl;
    }
};

class Assembly : public Detail {
protected:
    Assembly(string n, float w) : Detail(n, w) {
    }

    template <class T>
    friend void addToStore(vector<Detail*>& store, string n, float w);

public:
    void print() {
        cout << "Сборка: " << name << ", масса: " << weight << " кг" << endl;
    }
};

template <class T>
void addToStore(vector<Detail*>& store, string n, float w) {
    store.push_back(new T(n, w));
}

int main() {
    vector<Detail*> store;

    addToStore<Detail>(store, "Болт", 0.05f);
    addToStore<Detail>(store, "Гайка", 0.02f);
    addToStore<Assembly>(store, "Редуктор", 12.5f);
    addToStore<Detail>(store, "Вал", 3.2f);
    addToStore<Assembly>(store, "Коробка передач", 45.0f);

    cout << "Содержимое хранилища:" << endl;
    for (int i = 0; i < store.size(); i++) {
        store[i]->print(); 
    }

    cout << endl << "Освобождение памяти:" << endl;
    for (int i = 0; i < store.size(); i++) {
        delete store[i];
    }
    store.clear();

    return 0; 
}